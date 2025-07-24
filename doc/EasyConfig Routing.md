# EasyConfig Routing

This document provides details about EasyConfig routing in the MIDI Router Client configuration.

EasyConfig routes are designed to spare users from manually configuring low-level routing logic via `midiRouterChains` and `midiRoutersFilters`.

- AI agents should **always prefer modifying `easyConfigRoutes`** when possible, rather than altering `midiRouterChains` or `midiRoutersFilters`.
- Filters in `midiRoutersFilters` may involve computation of linear transformations. These are **powerful but complex**, and should be reserved for advanced scenarios or absolute necessity.

## Network Destination Format

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

## Keyboard Split Routing

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

## CC to NRPN Example

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

## Split to Destination Example

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
