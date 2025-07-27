# Preset Controls

This document describes the configuration and behavior of preset user controls in the MIDI Router Client.

## User Controls

Each preset may include interactive controls such as sliders, optionally paired with dropdowns if `isShowDropdown` is true.

Only the controls from the currently selected preset (`_activePresetID`) are presented in the UI—controls from other enabled presets are not shown.

```json
"userControls": [
  {
    "ccId": 0,
    "channelId": 1,
    "description": "Description",
    "dropdownListUuid": "50fda87a-6c8b-46b2-a104-1c2026b2dd58",
    "eventType": 0,
    "inputVal": 1,
    "is64Mode": false,
    "isSendOnPresetChange": false,
    "isShowDropdown": true,
    "maxVal": 127,
    "minVal": 0,
    "nrpnControl": 0,
    "outputPortnName": "",
    "uuid": "cc12cc7a-e1f1-4066-ad7c-66e76f6798b1"
  }
]
```

- `userControls` are interactive UI sliders.
- If `isShowDropdown` is true, a dropdown is shown **in addition to** the slider.
- `eventType` behavior:
  - `0` = CC → uses `ccId`
  - `1` = Program Change → ignores `ccId` and `nrpnControl`
  - `2` = NRPN → uses `nrpnControl`
- `channelId` is the MIDI channel for output.
- If `outputPortnName` is empty or disconnected, the control is not effective.
- `is64Mode` represents value `64` as center/zero (used in bipolar ranges).
- Dropdowns:
  - Values from `minVal` to `maxVal` are mapped to list items based on `dropdownListUuid`.
  - If the list is too short, missing entries are shown as numeric values starting from `minVal`.
  - Dropdown entries are stored as `\n`-separated text.

## Shared Dropdown Lists

Dropdown lists are globally defined and shared across all presets—there is no need to duplicate them for each preset.

```json
{
  "dropdownlists": [
    {
      "data": "line 1\nline 2",
      "name": "DM",
      "uuid": "4f10dc21-e30c-4d59-bd1b-3e4c575f10c8"
    }
  ]
}
```

- When explaining what the `MidiRouterConfig.json` file does, **only list the names of available dropdown lists**.
- Do **not** display the actual contents of dropdown lists unless the user explicitly requests them.
- If a user control uses a dropdown, mention the dropdown's name, but do not show its values by default.
- Dropdown list values are stored as entries separated by newline characters (`\n`).
