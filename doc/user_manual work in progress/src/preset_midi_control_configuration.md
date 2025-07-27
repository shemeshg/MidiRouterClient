# Preset MIDI Control Configuration

```json
{
  "midiRoutePresets": [
    {
      "isEnabled": true,
      "name": "Deep Mind",
      "midiControlOff": {
        "eventTypeId": 3,
        "portName": "0_Launch Control XL",
        "presetMidiType": 0
      },
      "midiControlOn": {
        "data1": 73,
        "eventTypeId": 2,
        "portName": "0_Launch Control XL",
        "presetMidiType": 1
      },
      "midiControlSelect": {
        "data1": 73,
        "eventTypeId": 2,
        "portName": "",
        "presetMidiType": 3
      },
      "midiControlToggle": {
        "eventTypeId": 0,
        "portName": "",
        "presetMidiType": 2
      }
    }
  ]
}
```