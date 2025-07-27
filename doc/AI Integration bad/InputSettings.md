# Input Settings

The `midiRouteInputs` section defines settings for each MIDI input port. These settings include monitoring, ignored MIDI message types, clock routing, and 14-bit CC configurations.

### Parameters:
- `monitor`: Controls monitoring of the input port.
  - `isMonitored`: Boolean indicating if the input is monitored.
  - `logLen`: Number of recent events to log.
- `ignoreTypes`: Specifies which MIDI message types to ignore.
  - `midiSense`: Ignore Active Sensing messages.
  - `midiSysex`: Ignore System Exclusive (SysEx) messages.
  - `midiTime`: Ignore MIDI Time Code messages.
- `midiInputName`: Name of the MIDI input port.
- `midiRouteClock`: Configures clock routing for the input port.
  - `fromSppPos`: Starting Song Position Pointer (SPP) position.
  - `propegateInputs`: List of input ports to propagate clock events to.
    - `midiInputName`: Name of the propagated input port.
  - `timeSig`: Time signature numerator.
  - `timeSigDivBy`: Time signature denominator.
- `cc14bitAry`: Configures 14-bit CC messages.
  - `cc`: Control Change number.
  - `channel`: MIDI channel.

### Example:
```json
{
  "midiRouteInputs": [
    {
      "monitor": {
        "isMonitored": false,
        "logLen": 2
      },
      "ignoreTypes": {
        "midiSense": true,
        "midiSysex": true,
        "midiTime": true
      },
      "midiInputName": "0_Launch Control XL",
      "midiRouteClock": {
        "fromSppPos": 0,
        "propegateInputs": [
          {
            "midiInputName": "0_Launch Control XL HUI"
          }
        ],
        "timeSig": 4,
        "timeSigDivBy": 4
      },
      "cc14bitAry": [
        {
          "cc": 5,
          "channel": 1
        }
      ]
    }
  ]
}
```
