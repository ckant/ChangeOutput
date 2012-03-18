ChangeOutput
============

# Command-line tool to set the current audio output device in OSX
## Command-line Usage:
    ChangeOutput [deviceName]
    
    deviceName: Any part of the device name
      ex) 'hd' without quotes will trigger HDMI

    If no deviceName is supplied, the current output device will
    be printed

    If deviceName is supplied, the output device will be changed
    and the current output device will be printed


# Suggested Usage:
In combination with an AppleScript to create a keyboard toggle
Example in /Example/KeyboardToggle.scpt
A keyboard toggle can be bound to an applescript within System Preferences

*Note: Tested on OSX 1.7.3 (Lion)
