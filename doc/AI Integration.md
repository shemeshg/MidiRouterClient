# MIDI Router Configuration (Markdown Format)

This document provides a human-readable configuration for the [MIDI Router Client](https://sourceforge.net/projects/midi-router-client/). It is designed to assist AI agents—like Copilot—in understanding the current configuration and helping users make updates to the [`MidiRouterClient.json`](./MidiRouterClient.json) file located in this folder.

---

## Table of Contents

- [Presets Overview](#presets-overview)
- [Port Connectivity Requirements](#port-connectivity-requirements)
- [Preset Activation via MIDI Commands](#preset-activation-via-midi-commands)
  - [MIDI Event Type Mapping](#midi-event-type-mapping)
- [Preset MIDI Control Configuration](#preset-midi-control-configuration)
- [Preset User Controls](#preset-user-controls)
- [Shared Dropdown Lists](#shared-dropdown-lists)
- [EasyConfig Routing](#easyconfig-routing)
  - [Network Destination Format](#network-destination-format)
  - [Keyboard Split Routing](#keyboard-split-routing)
  - [CC to NRPN Example](#cc-to-nrpn-example)
  - [Split to Destination Example](#split-to-destination-example)
- [Notes](#notes)
  - [🧼 Filter Simplification Rule](#-filter-simplification-rule)
  - [🔗 Auto-Generated Routing Chains](#-auto-generated-routing-chains)
  - [🔌 Port Connectivity Note](#-port-connectivity-note)
- [Version Tag](#version-tag)
- [Change Log](#change-log)

---

## Presets Overview

Only presets marked as **enabled** are active. The preset marked as **selected** is currently chosen for editing, determined by `_activePresetID`.

```json
{
  "_activePresetID": 0,
  "midiRoutePresets": [
    { "isEnabled": true, "name": "1st" },
    { "isEnabled": false, "name": "second" }
  ]
}
```

---

## Port Connectivity Requirements

For routing to function correctly, the specified input and output ports must exist and be connected.

```json
{
  "connectedInPorts": [
    "0_Scarlett 2i4 USB",
    "0_Launch Control XL",
    "0_Launch Control XL HUI"
  ],
  "connectedOutPorts": [
    "0_Scarlett 2i4 USB",
    "0_Launch Control XL",
    "0_Launch Control XL HUI"
  ]
}
```

---

## Preset Activation via MIDI Commands

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

---

## Preset MIDI Control Configuration

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

---

## Preset User Controls

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

---

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

---

## EasyConfig Routing

EasyConfig routes are designed to spare users from manually configuring low-level routing logic via `midiRouterChains` and `midiRoutersFilters`.

- 🧠 AI agents should **always prefer modifying `easyConfigRoutes`** when possible, rather than altering `midiRouterChains` or `midiRoutersFilters`.
- 🧮 Filters in `midiRoutersFilters` may involve computation of linear transformations. These are **powerful but complex**, and should be reserved for advanced scenarios or absolute necessity.

### Network Destination Format

Routing destinations may include **network port addresses**, formatted as:

```
<address>:<port>/<destinationName>
```

Example:

```json
"toDestinationName": "localhost:12345/0_Scarlett 2i4 USB"
```

- This defines a network-based output port.
- AI agents **cannot determine** whether these network ports exist or are reachable.
- When assisting users, the agent should clarify that such ports might be available—depending on network configuration—but cannot verify their existence.

### Keyboard Split Routing

`easyConfigRoutes` may use `splitRangeId` to route **from** a keyboard split zone:

```json
"splitRangeId": 1
```

Keyboard splits are defined with:

```json
"keyboardSplits": [34, 74],
"zoneNames": ["Split 0", "Split 1", "Split 2"]
```

These define three split zones:

| Split ID | Range     |
|----------|-----------|
| 0        | 0–34      |
| 1        | 35–74     |
| 2        | 75–127    |

- `splitRangeId` is **from** a split zone.

### CC to NRPN Example

Here's a real-world example of routing a **Control Change (CC)** event to **NRPN**, using channel 6 for both, and mapping a value range from 0–127 to 0–255:

```json
{
  "midiRoutePresets": [
    {
      "midiRouteInputs": [
        {
          "midiInputName": "0_Launch Control XL",
          "easyConfig": {
            "easyConfigRoutes": [
              {
                "fromCcOrNrpnEnd": 127,
                "fromCcOrNrpnStart": 0,
                "fromChannel": 6,
                "fromData1": -1,
                "fromSelectedMidiEventTypeId": 5,
                "splitRangeId": -1,
                "toCcOrNrpnEnd": 255,
                "toCcOrNrpnStart": 0,
                "toChannel": 6,
                "toData1": 8,
                "toDestinationName": "localhost:12345/0_Scarlett 2i4 USB",
                "toSelectedMidiEventTypeId": 7,
                "transpose": 0,
                "uuid": "d3bc0cb8-0de6-43ec-94c5-91b4a6ed7c6d"
              }
            ],
            "keyboardSplits": [],
            "zoneNames": []
          }
        }
      ]
    }
  ]
}
```

This transformation reflects a common pattern where NRPN values accommodate extended 8-bit ranges (0–255), exceeding standard CC ranges (0–127).

### Split to Destination Example

```json
{
  "midiRoutePresets": [
    {
      "midiRouteInputs": [
        {
          "midiInputName": "0_Launch Control XL",
          "easyConfig": {
            "easyConfigRoutes": [
              {
                "fromCcOrNrpnEnd": 127,
                "fromCcOrNrpnStart": 0,
                "fromChannel": 6,
                "fromData1": -1,
                "fromSelectedMidiEventTypeId": 5,
                "splitRangeId": -1,
                "toCcOrNrpnEnd": 255,
                "toCcOrNrpnStart": 0,
                "toChannel": 6,
                "toData1": 8,
                "toDestinationName": "localhost:12345/0_Scarlett 2i4 USB",
                "toSelectedMidiEventTypeId": 7,
                "transpose": 0,
                "uuid": "d3bc0cb8-0de6-43ec-94c5-91b4a6ed7c6d"
              }
            ],
            "keyboardSplits": [],
            "zoneNames": []
          }
        }
      ]
    }
  ]
}
```

---

## Notes

### 🧼 Filter Simplification Rule

When explaining configurations to users, any filters using the value `-1` (such as `channel`, `data1`, `data2`) indicate no filtering—they allow all values to pass.  
These should be **omitted** in descriptions to improve clarity, since they have no practical effect on routing.

This rule applies across:
- `userControls`
- `midiControlOn`, `midiControlOff`, `midiControlSelect`, `midiControlToggle`
- Any other filter settings present elsewhere in the configuration

### 🔗 Auto-Generated Routing Chains

Entries in `midiRouterChains` with `"isEasyConfig": true` are automatically generated by the system—either for MIDI-triggered preset switching or for simplified routing logic via the EasyConfig UI.

These chains are considered **redundant for documentation and user editing**.  
- 🛑 Do not manually edit these chains.  
- 🧠 AI agents and users should ignore them when reviewing or discussing routing logic.  
- ✏️ Focus only on custom-defined chains or EasyConfig setups explicitly created by the user.

### 🔌 Port Connectivity Note

The entries in `connectedInPorts` and `connectedOutPorts` are **automatically generated by the MIDI Router server** to reflect real-time port connections.  
- 🚫 These values should **never be edited manually** or by AI agents.  
- ⚙️ Any changes to port connectivity should be made by updating physical connections not by modifying the config file.


### 📝 Dropdown Explanation Policy

When explaining what the `MidiRouterConfig.json` file does, **only list the names of available dropdown lists** (as shown in the "Shared Dropdown Lists" section).  
Do **not** display the actual contents of dropdown lists unless the user explicitly requests them.  
If a user control uses a dropdown, mention the dropdown's name, but do not show its values by default.  
Dropdown list values are stored as entries separated by newline characters (`\n`).



---

## 🏷️ Version Tag

**Document Version**: `v1.0`  
**Last Updated**: `2025-07-23`  
**Maintainer**: shemeshg

---


## 📝 Change Log

| Version | Date       | Changes Made                                                                                                   |
|---------|------------|---------------------------------------------------------------------------------------------------------------|
| v1.0    | 2025-07-23 | ⚠️ Application version 2.3.0 introduces changes that break compatibility with previous user controls. This may result in JSON configuration errors or data loss. AI agents should be able to repair configurations using guidance from this