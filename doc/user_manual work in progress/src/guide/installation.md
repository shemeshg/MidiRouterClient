# Installation Guide

## Windows

Install via [winget](https://learn.microsoft.com/en-us/windows/package-manager/winget/):

```cmd
winget install Shemeshg.MidiRouterClient
```

## macOS

Install via [Homebrew](https://brew.sh/):

```bash
brew install --cask midi-router-client
codesign --force --deep --sign - /Applications/midi-router-client.app/
xattr -c /Applications/midi-router-client.app/
```

> **Note:** macOS requires manual code signing and removal of extended attributes to ensure proper execution.

## Linux

Prebuilt `.zip` and `.deb` packages are available, targeting the oldest supported Ubuntu LTS at the time of release.

## ⚠️ Additional Notes

- Distributed binaries are **not code-signed**.
- The macOS cask may be relocated to a different tap in the future due to a `deleted <date>: unsigned` tag.
