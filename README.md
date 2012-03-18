#ChangeOutput
## Command-line tool to set the current audio output device in OSX
### Command-line Usage:
    ChangeOutput [DeviceName]
    
    DeviceName: Any part of the device name
      ex) 'hd' (without quotes) will change to HDMI

    If no DeviceName is supplied, the current output device will
    be printed

    If DeviceName is supplied, the output device will be changed
    and the current output device will be printed


### Suggested Usage:
ChangeOutput can be used in combination with an AppleScript to create a keyboard toggle.

An example of this can be found in /Example/KeyboardToggle.scpt

A keyboard toggle can be bound to an AppleScript within System Preferences


*Tested on OSX 1.7.3 (Lion)*
