# EasyConfig Overview

EasyConfig makes MIDI routing simple and approachable—no need to dive into complex low-level setup.

The interface is organized into two main tabs: **Routes** and **Split**, each designed to help you configure your MIDI setup quickly and efficiently.


## EasyConfig Routes

### Destination Setup

You can route MIDI data to either:
- A local **output name**, or
- A **network destination** using the format: `<address>:<port>/<destinationName>`

To make remote setup easier, there's a **Query** button that checks if the remote port is available and confirms connectivity.  
All network communication uses **WebSocket over TCP**, ensuring reliable data transfer.

## Keyboard Split

The **Split** tab lets you define a **split point** on your keyboard—this divides it into separate zones.
This is especially useful for setting up layered instruments or assigning different sounds to different parts of the keyboard.

Once zones are created, you can assign them as sources for `note on/off` events (when a key is pressed or released)




