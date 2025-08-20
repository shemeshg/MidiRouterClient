# Software Bill of Materials (SBOM)

## Core Dependencies
- [Qt Quick and QT6 Open Source](https://www.qt.io/)
- [Qt Web Channel](https://doc.qt.io/qt-6/qtwebchannel-index.html)  
  _Included in full Qt open source install._

## Multimedia
- [RtMidi](https://www.music.mcgill.ca/~gary/rtmidi/)  
  _C++ MIDI access, version 6.0.0. Already bundled._

## Icons & Visuals
- Icons by Freepik from [flaticon.com](https://www.flaticon.com)
- [Google Icons](https://fonts.google.com/icons)

## Utilities
- [Cog](https://nedbatchelder.com/code/cog) – Code generation tool

## Embedded Code
- [QWebchannelCppClient/main.cpp](https://github.com/P1eaz/QWebchannelCppClient/blob/master/main.cpp)  
  _Used for server-to-server QtWebChannel. Already included._

---
```Spdx
SPDXVersion: SPDX-2.2
DataLicense: CC0-1.0
DocumentName: SBOM-SPDX
DocumentNamespace: http://example.com/spdxdocs/sbom-002
Creator: Tool: Microsoft Copilot
Created: 2025-08-20T11:47:00Z

##### Packages #####

PackageName: Qt Quick and QT6
PackageDownloadLocation: https://www.qt.io/
PackageLicenseDeclared: GPL-3.0-or-later

PackageName: Qt Web Channel
PackageDownloadLocation: https://doc.qt.io/qt-6/qtwebchannel-index.html
PackageLicenseDeclared: GPL-3.0-or-later

PackageName: RtMidi
PackageDownloadLocation: https://www.music.mcgill.ca/~gary/rtmidi/
PackageLicenseDeclared: MIT
PackageVersion: 6.0.0

PackageName: Flaticon Icons (Freepik)
PackageDownloadLocation: https://www.flaticon.com
PackageLicenseDeclared: NOASSERTION

PackageName: Google Icons
PackageDownloadLocation: https://fonts.google.com/icons
PackageLicenseDeclared: Apache-2.0

PackageName: Cog
PackageDownloadLocation: https://nedbatchelder.com/code/cog
PackageLicenseDeclared: MIT

PackageName: QWebchannelCppClient
PackageDownloadLocation: https://github.com/P1eaz/QWebchannelCppClient/blob/master/main.cpp
PackageLicenseDeclared: NOASSERTION
```