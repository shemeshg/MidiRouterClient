# [[[cog
# import cog
# from CMakeCog import getCmake
# cog.outl(getCmake())
# ]]]
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
add_subdirectory(MidiClient)

SET(GEN_HPP TRUE)
if(GEN_HPP)
    make_directory(${CMAKE_CURRENT_BINARY_DIR}/webchannel)


    file(GLOB HPP_GEN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/webchannel/*.hpp"  )

    set(HPP_GEN_FILES
        ${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt
        ${HPP_GEN_FILES}
    )
    add_custom_target(runScript_7yV8Csks ALL
        COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/parseHpp.py ${HPP_GEN_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running parseHpp shell script")

    # Run a shell script before everything else
    execute_process(
        COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/parseHpp.py ${HPP_GEN_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        RESULT_VARIABLE result
    )

    # Check the result of the script execution
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Script execution failed with result: ${result}")
    endif()

    # Continue with the rest of your CMake configuration
endif()
                     

add_library(RtMidiRouterLib STATIC
  MidiClientClass.h
MidiServerClass.h
MidiClientClass.cpp
MidiServerClass.cpp
libs/QWebchannelCppClient/WebChannelClient.h
libs/QWebchannelCppClient/WebChannelClient.cpp
libs/websocket/websocketclientwrapper.h
libs/websocket/websockettransport.h
libs/websocket/websocketclientwrapper.cpp
libs/websocket/websockettransport.cpp
MidiRoute/filters/FilterMidiChannelMsg.h
MidiRoute/filters/SendRemoteServer.h
MidiRoute/filters/SignalSlot.h
MidiRoute/filters/defferedevent.h
MidiRoute/filters/logdata.h
MidiRoute/filters/sendmidiport.h
MidiRoute/filters/FilterMidiChannelMsg.cpp
MidiRoute/RoutFiltersChainClass.h
MidiRoute/midifilterchain.h
MidiRoute/midiroute.h
MidiRoute/rangemap.h
MidiRoute/routefilterchain.h
MidiRoute/routfilter.h
MidiRoute/RouteFilterChain.cpp
MidiRoute/midiroute.cpp
MidiRoute/rangemap.cpp
webchannel/EmitCommand.h
webchannel/WcRouteFilterChains.h
webchannel/virtualinout.h
webchannel/wcmidiin.h
webchannel/wcmidiinlistener.h
webchannel/wcmidiout.h
webchannel/virtualinout.cpp
webchannel/wcmidiin.cpp
webchannel/wcmidiout.cpp
${CMAKE_CURRENT_BINARY_DIR}/webchannel/ApplyConfig.cpp
${CMAKE_CURRENT_BINARY_DIR}/webchannel/ApplyConfig.h
${CMAKE_CURRENT_BINARY_DIR}/webchannel/wcuserdata.cpp
${CMAKE_CURRENT_BINARY_DIR}/webchannel/wcuserdata.h
)        
                     
target_link_libraries(RtMidiRouterLib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
Qt${QT_VERSION_MAJOR}::WebSockets
Qt${QT_VERSION_MAJOR}::WebChannel
RtMidiWrap
midiClient) 
target_compile_definitions(RtMidiRouterLib PRIVATE RTMIDIROUTERLIB_LIBRARY) 

target_include_directories(RtMidiRouterLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/MidiClient/GenHpp
${CMAKE_CURRENT_BINARY_DIR}/webchannel
webchannel)                     
        

if(GEN_HPP)
  add_dependencies(RtMidiRouterLib runScript_7yV8Csks)
endif()
        
# [[[end]]]
