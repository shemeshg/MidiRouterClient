find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebSockets WebChannel REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebSockets WebChannel REQUIRED)


add_library(midiClient STATIC
genPrpt/Dropdownlist.h
genPrpt/EasyConfigPrivate.h
genPrpt/EasyConfigRoutePrivate.h
genPrpt/FilterAndTransformPrivate.h
genPrpt/FilterMidiDestinationPrivate.h
genPrpt/FilterNetworkDestinationPrivate.h
genPrpt/FilterSchedulePrivate.h
genPrpt/FilterToConslePrivate.h
genPrpt/MidiClientConnectionPrivate.h
genPrpt/MidiRouteInputCc14bit.h
genPrpt/MidiRouteInputPrivate.h
genPrpt/MidiRoutePresetPrivate.h
genPrpt/MidiRouterChainPrivate.h
genPrpt/MidiRoutersFilter.h
genPrpt/MonitorPrivate.h
genPrpt/PresetMidiControlPrivate.h
genPrpt/UserControlPrivate.h
genPrpt/UserDataConfigPrivate.h
genPrpt/Dropdownlist.cpp
genPrpt/EasyConfigPrivate.cpp
genPrpt/EasyConfigRoutePrivate.cpp
genPrpt/FilterAndTransformPrivate.cpp
genPrpt/FilterMidiDestinationPrivate.cpp
genPrpt/FilterNetworkDestinationPrivate.cpp
genPrpt/FilterSchedulePrivate.cpp
genPrpt/FilterToConslePrivate.cpp
genPrpt/MidiClientConnectionPrivate.cpp
genPrpt/MidiRouteInputCc14bit.cpp
genPrpt/MidiRouteInputPrivate.cpp
genPrpt/MidiRoutePresetPrivate.cpp
genPrpt/MidiRouterChainPrivate.cpp
genPrpt/MidiRoutersFilter.cpp
genPrpt/MonitorPrivate.cpp
genPrpt/PresetMidiControlPrivate.cpp
genPrpt/UserControlPrivate.cpp
genPrpt/UserDataConfigPrivate.cpp
EasyConfig.h
EasyConfigRoute.h
FilterAndTransform.h
FilterMidiDestination.h
FilterNetworkDestination.h
FilterSchedule.h
FilterToConsle.h
MidiClientConnection.h
MidiClientUtil.h
MidiPresetControlEasyConfig.h
MidiRouteInput.h
MidiRoutePreset.h
MidiRouterChain.h
Monitor.h
PresetMidiControl.h
UserConfigGenJson.h
UserConfigParseJson.h
UserControl.h
UserDataConfig.h
EasyConfig.cpp
EasyConfigRoute.cpp
FilterAndTransform.cpp
FilterMidiDestination.cpp
FilterNetworkDestination.cpp
FilterSchedule.cpp
FilterToConsle.cpp
MidiClientConnection.cpp
MidiClientUtil.cpp
MidiRouteInput.cpp
MidiRoutePreset.cpp
MidiRouterChain.cpp
Monitor.cpp
PresetMidiControl.cpp
UserConfigGenJson.cpp
UserConfigParseJson.cpp
UserControl.cpp
UserDataConfig.cpp
)

  target_link_libraries(midiClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::WebChannel
          )

  target_compile_definitions(midiClient PRIVATE MIDICLIENT_LIBRARY)

