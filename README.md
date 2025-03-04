# Midi Router Client (Ver 2)

<a href="https://sourceforge.net/projects/midi-router-client"><img alt="Midi router Reviews" src="https://sourceforge.net/cdn/syndication/badge_img/3211406/oss-rising-star-white?achievement=oss-rising-star&amp;r=https://sourceforge.net/p/midi-router-client/admin/files/badges"  style="width: 200px;"></a>

Create routes from anywhere to anywhere

## Install

### MacOs

* install using:
  
```bash
brew install --cask midi-router-client/
```

* *Must* fix signature:
  
```bash
codesign --force --deep --sign - /Applications/midi-router-client.app/
```

* *Must* fix authorizations:

```bash  
xattr -c /Applications/midi-router-client.app/
```

### Windows

Run NSIS installer

### Linux

Run deb installer

## Project setup

### Ubuntu

requires `libasound2-dev`


### Compiles for production

See `deploy<os>` scripts on root.

## Built With

<https://github.com/shemeshg/MidiRouterClient/blob/main/SBOM.md>

## Authors

* **shemeshg**

## License

<https://github.com/shemeshg/MidiRouterClient/blob/main/LICENSE>
