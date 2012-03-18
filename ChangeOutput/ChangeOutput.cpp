//
//  ChangeOutput.cpp
//  ChangeOutput
//
//  Copyright 2012 Chris Kant
//

#include "AudioDevice.h"
#include "AudioDeviceList.h"

#include <cstdio>
#include <string>
#include <algorithm>

OSErr printCurrentOutputDevice();
OSErr setCurrentOutputDevice(const char* newOutputDevice);

/**
 * Prints the current audio output device
 */
OSErr printCurrentOutputDevice() {
    
    OSErr err;
    
    UInt32 size = sizeof(AudioDeviceID);
    AudioDeviceID defaultDev;
    char devName[64];
    UInt32 maxLen = sizeof(devName);
    
    err = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice,
                                   &size,  
                                   &defaultDev);
    
    if (err == noErr) {
        
        err = AudioDeviceGetProperty(defaultDev, 0, false, 
                                     kAudioDevicePropertyDeviceName, 
                                     &maxLen, devName);   
        printf("%s\n", devName);
    }

    return err;
}

/**
 * Sets the current audio output device
 */
OSErr setCurrentOutputDevice(const char* newOutputDevice) {
    
    OSErr err = noErr;
    
    // Get device name to set output to
    std::string setName(newOutputDevice);
    std::transform(setName.begin(), setName.end(), setName.begin(), ::toupper);
    
    // Get output device list
    AudioDeviceList* outputAudioDevList = new AudioDeviceList(false);
    AudioDeviceList::DeviceList &outDevList = outputAudioDevList->GetList();
    
    
    // Loop through device list looking for an appropriate device name
    for (auto devIt = outDevList.begin(); devIt != outDevList.end(); ++devIt) {
        
        std::string devName((*devIt).mName);
        std::transform(devName.begin(), devName.end(), devName.begin(), ::toupper);
        
        if (devName.find(setName) != std::string::npos) {
            
            // Set the output device (and system output) to the requested one
            err = AudioHardwareSetProperty(kAudioHardwarePropertyDefaultOutputDevice, 
                                           sizeof(AudioDeviceID), 
                                           &(*devIt).mID);
            
            if (err == noErr) {
                
                err = AudioHardwareSetProperty(kAudioHardwarePropertyDefaultSystemOutputDevice, 
                                               sizeof(AudioDeviceID), 
                                               &(*devIt).mID);
                
            }
            
            break;
        }
        
    }
    
    delete outputAudioDevList;

    return err;
    
}


/**
 * Usage: ChangeOutput <DeviceNameToChangeTo>: 
 *          Sets to the supplied device name
 *          Prints the currently set device
 *
 *        ChangeOutput: Prints the currently set device
 */
int main(int argc, const char * argv[]) {
    OSStatus err = noErr;
    
    bool settingAudioDevice = (argc == 2);
    
    if (settingAudioDevice)  {
        err = setCurrentOutputDevice(argv[1]);
    }
    
    err |= printCurrentOutputDevice();
    
    return err;
    
}

