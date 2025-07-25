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

### Filter Type 1: TO_CONSOLE

This filter type logs MIDI events to the console.

**Parameters:**
- `filterType`: Set to `1` for this filter.
- `logTo`: Specifies the logging destination:
  - `0` (CLIENT): Log to the client console.
  - `1` (SERVER): Log to the server console.
- `userdata`: Additional user-defined data in JSON format.
- `uuid`: Unique identifier.

**Example:**
```json
{
  "filterType": 1,
  "logTo": 0,
  "userdata": "{}",
  "uuid": "5cdfecdb-901f-4c33-aead-4162df83d43d"
}
```

### Filter Type 2: TO_NETWORK

This filter type routes MIDI events to a network destination.

**Parameters:**
- `filterType`: Set to `2` for this filter.
- `midiInputName`: Name of the MIDI input port.
- `serverName`: Name of the target server.
- `serverPort`: Port number of the target server.
- `uuid`: Unique identifier.

**Example:**
```json
{
  "filterType": 2,
  "midiInputName": "midiportname",
  "serverName": "localhost",
  "serverPort": 12345,
  "uuid": "cfa306c0-84c8-4071-b68d-9f6e109cca2c"
}
```

### Filter Type 3: SCHEDULE_TO

This filter type holds MIDI events and schedules them to be sent at a specific time based on the `DefferedType` and `defferedTo` parameters. It requires MIDI clock events to function correctly.

**Parameters:**
- `filterType`: Set to `3` for this filter.
- `defferedType`: Specifies the scheduling type:
  - `0` (IN_SPP): Schedule relative to the current Song Position Pointer (SPP).
  - `1` (IN_BAR): Schedule relative to the current bar.
  - `2` (AT_SPP): Schedule at a specific SPP.
  - `3` (AT_BAR): Schedule at a specific bar.
  - `4` (QUANTIZE_SPP): Quantize to the nearest SPP.
  - `5` (QUANTIZE_BAR): Quantize to the nearest bar.
- `defferedTo`: Number of units to defer the event.
- `uuid`: Unique identifier.

**Example:**
```json
{
  "defferedTo": 0,
  "defferedType": 0,
  "filterType": 3,
  "uuid": "e557fe19-a75d-4ad1-89eb-e3f9e683cfb8"
}
```
