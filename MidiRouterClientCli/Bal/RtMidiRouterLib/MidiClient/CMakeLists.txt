# [[[cog
# import cog
# from CMakeCog import getCmake
# cog.outl(getCmake())
# ]]]

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebSockets WebChannel REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebSockets WebChannel REQUIRED)


SET(GEN_HPP TRUE)
if(GEN_HPP)
    make_directory(${CMAKE_CURRENT_BINARY_DIR}/GenHpp)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/genPrpt)


    set(HPP_GEN_FILES
        ${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/hpp/EasyConfig.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/EasyConfigRoute.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/FilterAndTransform.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/FilterMidiDestination.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/FilterNetworkDestination.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/FilterSchedule.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/FilterSwitchData1Data2.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/FilterToConsle.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/MidiClientConnection.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/MidiClientUtil.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/MidiRouteInput.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/MidiRoutePreset.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/MidiRouterChain.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/Monitor.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/PresetMidiControl.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/UserConfigParseJson.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/UserControl.hpp
${CMAKE_CURRENT_SOURCE_DIR}/hpp/UserDataConfig.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/Dropdownlist.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/EasyConfigPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/EasyConfigRoutePrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/FilterAndTransformPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/FilterMidiDestinationPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/FilterNetworkDestinationPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/FilterSchedulePrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/FilterSwitchData1Data2Private.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/FilterToConslePrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MidiClientConnectionPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MidiRouteInputCc14bit.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MidiRouteInputPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MidiRoutePresetPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MidiRouterChainPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MidiRoutersFilter.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MidiRoutersFilterPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/MonitorPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/PresetMidiControlPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/UserControlPrivate.hpp
${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/UserDataConfigPrivate.hpp
    )
    add_custom_target(runScript_44d52af4e734681c7021c555be98190b6a43c0d85c41685e19006fc8819138f8 ALL
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
                     

add_library(MidiClient STATIC
  ${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfig.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfig.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfigRoute.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfigRoute.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterAndTransform.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterAndTransform.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterMidiDestination.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterMidiDestination.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterNetworkDestination.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterNetworkDestination.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterSchedule.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterSchedule.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterSwitchData1Data2.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterSwitchData1Data2.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterToConsle.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterToConsle.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientConnection.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientConnection.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientUtil.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientUtil.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouteInput.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouteInput.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRoutePreset.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRoutePreset.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouterChain.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouterChain.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/Monitor.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/Monitor.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/PresetMidiControl.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/PresetMidiControl.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserConfigParseJson.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserConfigParseJson.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserControl.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserControl.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserDataConfig.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserDataConfig.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/Dropdownlist.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/EasyConfigPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/EasyConfigRoutePrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterAndTransformPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterMidiDestinationPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterNetworkDestinationPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterSchedulePrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterSwitchData1Data2Private.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterToConslePrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiClientConnectionPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRouteInputCc14bit.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRouteInputPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutePresetPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRouterChainPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutersFilter.cpp
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutersFilter.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutersFilterPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MonitorPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/PresetMidiControlPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/UserControlPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/UserDataConfigPrivate.h
)        
                     
target_link_libraries(MidiClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
Qt${QT_VERSION_MAJOR}::WebSockets
Qt${QT_VERSION_MAJOR}::WebChannel) 
target_compile_definitions(MidiClient PRIVATE MIDICLIENT_LIBRARY) 

if(GEN_HPP)
  add_dependencies(MidiClient runScript_44d52af4e734681c7021c555be98190b6a43c0d85c41685e19006fc8819138f8)
endif()
        
# [[[end]]]
