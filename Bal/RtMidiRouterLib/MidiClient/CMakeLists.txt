find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebSockets WebChannel REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebSockets WebChannel REQUIRED)


add_library(midiClient STATIC
    MidiClientConnection.h
    MidiClientConnection.cpp
    MidiClientConnectionPrivate.h
    MidiClientConnectionPrivate.cpp
    UserDataConfig.h
    UserDataConfig.cpp
    UserDataConfigPrivate.h
    UserDataConfigPrivate.cpp
    Dropdownlist.h
    Dropdownlist.cpp
    MidiClientUtil.h
    MidiClientUtil.cpp
    PresetMidiControlPrivate.h
    PresetMidiControlPrivate.cpp
    PresetMidiControl.cpp
    PresetMidiControl.h
    MidiRoutePresetPrivate.h
    MidiRoutePresetPrivate.cpp
    MidiRoutePreset.cpp
    MidiRoutePreset.h
    MidiRouteInputPrivate.cpp
    MidiRouteInputPrivate.h
    MidiRouteInput.h
    MidiRouteInput.cpp
    EasyConfigPrivate.h
    EasyConfigPrivate.cpp
    EasyConfig.h
    EasyConfig.cpp
    EasyConfigRoutePrivate.h
    EasyConfigRoutePrivate.cpp
    EasyConfigRoute.h
    EasyConfigRoute.cpp
    UserControl.cpp
    UserControl.h
    UserControlPrivate.cpp
    UserControlPrivate.h
)

  target_link_libraries(midiClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::WebChannel
          )

  target_compile_definitions(midiClient PRIVATE MIDICLIENT_LIBRARY)
