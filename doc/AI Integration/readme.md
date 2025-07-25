# MIDI Router Configuration (AI integration)

This document provides a human-readable configuration reference for the [MIDI Router Client](https://sourceforge.net/projects/midi-router-client/). It is designed to assist AI agents—like Copilot—in understanding the current configuration and helping users make updates to the `MidiRouterClient.json` file added to context.

---

## Table of Contents

- [Presets Overview](#presets-overview)
- [Port Connectivity Requirements](#port-connectivity-requirements)
- [MIDI Router Chains and Filters](#midi-router-chains-and-filters)
- [Preset Activation via MIDI Commands](#preset-activation-via-midi-commands)
  - [MIDI Event Type Mapping](#midi-event-type-mapping)
- [Preset MIDI Control Configuration](#preset-midi-control-configuration)
- [Preset User Controls](Preset%20Controls.md)
- [Shared Dropdown Lists](#shared-dropdown-lists)
- [EasyConfig Routing](#easyconfig-routing)
- [Input Settings](#input-settings)
- [Notes](#notes)
  - [🧼 Filter Simplification Rule](#%f0%9f%a7%bc-filter-simplification-rule)
  - [🔗 Auto-Generated Routing Chains](#%f0%9f%94%97-auto-generated-routing-chains)
  - [🔌 Port Connectivity Note](#%f0%9f%94%8c-port-connectivity-note)
  - [📝 Dropdown Explanation Policy](#%f0%9f%93%9d-dropdown-explanation-policy)
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

## MIDI Router Chains and Filters

The content for this section has been moved to [MIDI Router Chains and Filters](MIDI%20Router%20Chains%20and%20Filters.md).

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

The content for this section has been moved to [Preset Controls](Preset%20Controls.md).

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

The content for this section has been moved to [EasyConfig Routing](EasyConfig%20Routing.md).

## Input Settings

The content for this section has been moved to [Input Settings](InputSettings.md).

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
| v1.0    | 2025-07-23 | ⚠️ Application version 2.3.0 introduces changes that break compatibility with previous user controls.  |