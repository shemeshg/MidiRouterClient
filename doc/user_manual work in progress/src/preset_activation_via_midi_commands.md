# Preset Activation via MIDI Commands

Presets can be controlled with MIDI events—**On**, **Off**, **Select** (On and selected), and **Toggle**.

- If `portName` is empty for a command, that trigger is ignored.
- `presetMidiType` codes:
  - `0` = Off
  - `1` = On
  - `2` = Toggle
  - `3` = Select

### MIDI Event Type Mapping

```json
[
  { "value": 0, "text": "[] - -" },
  { "value": 1, "text": "[8, 9] - Note on/off" },
  { "value": 2, "text": "[9] - Note off" },
  { "value": 3, "text": "[8] - Note on" },
  { "value": 4, "text": "[10] - Key Aftertouch" },
  { "value": 5, "text": "[11] - Control Change" },
  { "value": 7, "text": "[100] - NRPN" },
  { "value": 8, "text": "[12] - Program Change" },
  { "value": 9, "text": "[13] - Channel Aftertouch" },
  { "value": 10, "text": "[14] - Pitch Bend" }
]
```