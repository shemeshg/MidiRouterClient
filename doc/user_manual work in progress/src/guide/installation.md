# Installation

## Windows

Using winget

```cmd
winget install Shemeshg.MidiRouterClient
```

## Macos

Using homebrew

```
brew install --cask midi-router-client
codesign --force --deep --sign - /Applications/midi-router-client.app/
xattr -c /Applications/midi-router-client.app/
```

## Linux

Deployed `zip` and `deb`  available, based on oldest `Ubuntu LTS` supported at time of packaging.

## Notes

- Deployed code is not codesigned
- macos cask might be moved in the future to a different tap due to `deleted <date> :unsinged` tag.
