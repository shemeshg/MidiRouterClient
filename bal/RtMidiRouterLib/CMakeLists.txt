cmake_minimum_required(VERSION 3.14)

project(RtMidiRouterLib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebSockets WebChannel REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebSockets WebChannel REQUIRED)

add_subdirectory(RtMidiWrap)

add_library(RtMidiRouterLib STATIC
  MidiServerClass.cpp
  MidiServerClass.h
  MidiClientClass.cpp
  MidiClientClass.h
  MidiClient/MidiClientConnection.h
  MidiClient/MidiClientConnection.cpp
  libs/QWebchannelCppClient/WebChannelClient.cpp
  libs/websocket/websocketclientwrapper.cpp
  libs/websocket/websockettransport.cpp    
  MidiRoute/filters/FilterMidiChannelMsg.cpp  
  MidiRoute/midiroute.cpp
  MidiRoute/rangemap.cpp
  webchannel/virtualinout.cpp
  webchannel/wcmidiin.cpp
  webchannel/wcmidiout.cpp
  webchannel/wcuserdata.cpp
  libs/QWebchannelCppClient/WebChannelClient.h
  libs/websocket/websocketclientwrapper.h
  libs/websocket/websockettransport.h
  MidiRoute/RoutFiltersChainClass.h
  MidiRoute/filters/FilterMidiChannelMsg.h
  MidiRoute/filters/SendRemoteServer.h
  MidiRoute/filters/defferedevent.h
  MidiRoute/filters/logdata.h
  MidiRoute/filters/sendmidiport.h
  MidiRoute/filters/SignalSlot.h
  MidiRoute/midifilterchain.h
  MidiRoute/midiroute.h
  MidiRoute/rangemap.h
  MidiRoute/routfilter.h
  webchannel/EmitCommand.h
  webchannel/WcRouteFilterChains.h
  webchannel/virtualinout.h
  webchannel/wcmidiin.h
  webchannel/wcmidiinlistener.h
  webchannel/wcmidiout.h
  webchannel/wcuserdata.h
)

target_link_libraries(RtMidiRouterLib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::WebChannel
        RtMidiWrap)

target_compile_definitions(RtMidiRouterLib PRIVATE RTMIDIROUTERLIB_LIBRARY)
