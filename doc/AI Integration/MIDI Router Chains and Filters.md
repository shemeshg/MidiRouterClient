# MIDI Router Chains and Filters

This document provides detailed information about the `midiRouterChains` and `midiRoutersFilters` configuration sections for the MIDI Router Client.

## midiRouterChains

`midiRouterChains` define the routing logic for MIDI events. Each chain consists of a sequence of `midiRoutersFilters` that process and transform MIDI data as it passes through.

## midiRoutersFilters

`midiRoutersFilters` apply conditions and transformations to MIDI events. Below are details for the two main filter types found in the configuration:

### Filter Type 4: FILTER_AND_TRANSFORM

This filter type allows for both filtering and transforming MIDI event data. The transformation notation is:

- `[[fromStart, fromEnd, toStart, toEnd]]` — maps the range `fromStart` to `fromEnd` onto `toStart` to `toEnd`.
- `[[fromStart, fromEnd, toStart]]` — short form, where `toEnd = toStart + (fromEnd - fromStart)`.
- `[[value1, value2]]` — maps `value1` to `value2`.
- `[[value]]` — equivalent to `[[value, value]]`, a single value mapping.

**Parameters:**
- `conditionAction`: Controls event deletion:
  - `0` (DO_NOT_DELETE): Always pass the event.
  - `1` (DELETE_IF_NOT_MET_CONDITION): Delete if filter conditions are not met.
  - `2` (DELETE_IF_MET_CONDITION): Delete if filter conditions are met.
- `filterChannel`: MIDI channel(s) to filter, using the notation above.
- `filterData1`: Data1 byte filter and transformation, using the notation above.
- `filterData2`: Data2 byte filter and transformation, using the notation above.
- `filterEvents`: List of MIDI event types to filter (e.g., `[8]` for Note On).
- `filterType`: Set to `4` for this filter.
- `name`: Filter name.
- `uuid`: Unique identifier.

**Example:**
```json
{
  "conditionAction": 1,
  "filterChannel": "[[6, 6]]",
  "filterData1": "[[19, 74, 19]]",
  "filterData2": "[[0, 127, 0, 255]]",
  "filterEvents": "[[8], [9]]",
  "filterType": 4,
  "name": "EasyConfig",
  "uuid": "a0ceaa75-1273-46b5-8159-30f41e0e1251"
}
```
This filter applies to channel 6, transforms data1 from 19–74 to 19–(19+55), and data2 from 0–127 to 0–255, for Note On (8) and Note Off (9) events. If the condition is not met, the event is deleted.

### Filter Type 0: TO_MIDI_DESTINATION

This filter type routes MIDI events to a specific MIDI destination.

**Parameters:**
- `filterType`: Set to `0` for this filter.
- `midiInputName`: Name of the MIDI input port.
- `uuid`: Unique identifier.

**Example:**
```json
{
  "filterType": 0,
  "midiInputName": "0_Scarlett 2i4 USB",
  "uuid": "ae0a5872-a825-43f4-bb0e-ed4fa1700112"
}
```
This filter routes events from the specified input port to the MIDI destination.
