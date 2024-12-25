SET(GEN_HPP TRUE)
if(GEN_HPP)
    file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/hpp/*.hpp")
    add_custom_target(run_script ALL
        COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/parseHpp.py ${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt ${HEADER_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running parseHpp shell script")

    # Run a shell script before everything else
    execute_process(
        COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/parseHpp.py ${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt ${HEADER_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE result
    )

    # Check the result of the script execution
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Script execution failed with result: ${result}")
    endif()

    # Continue with the rest of your CMake configuration
endif()



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
GenHpp/EasyConfig.h
GenHpp/EasyConfigRoute.h
GenHpp/FilterAndTransform.h
GenHpp/FilterMidiDestination.h
GenHpp/FilterNetworkDestination.h
GenHpp/FilterSchedule.h
GenHpp/FilterToConsle.h
GenHpp/MidiClientConnection.h
GenHpp/MidiClientUtil.h
GenHpp/MidiPresetControlEasyConfig.h
GenHpp/MidiRouteInput.h
GenHpp/MidiRoutePreset.h
GenHpp/MidiRouterChain.h
GenHpp/Monitor.h
GenHpp/PresetMidiControl.h
GenHpp/UserConfigGenJson.h
GenHpp/UserConfigParseJson.h
GenHpp/UserControl.h
GenHpp/UserDataConfig.h
GenHpp/EasyConfig.cpp
GenHpp/EasyConfigRoute.cpp
GenHpp/FilterAndTransform.cpp
GenHpp/FilterMidiDestination.cpp
GenHpp/FilterNetworkDestination.cpp
GenHpp/FilterSchedule.cpp
GenHpp/FilterToConsle.cpp
GenHpp/MidiClientConnection.cpp
GenHpp/MidiClientUtil.cpp
GenHpp/MidiRouteInput.cpp
GenHpp/MidiRoutePreset.cpp
GenHpp/MidiRouterChain.cpp
GenHpp/Monitor.cpp
GenHpp/PresetMidiControl.cpp
GenHpp/UserConfigGenJson.cpp
GenHpp/UserConfigParseJson.cpp
GenHpp/UserControl.cpp
GenHpp/UserDataConfig.cpp
)

  target_link_libraries(midiClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::WebChannel
          )

  target_compile_definitions(midiClient PRIVATE MIDICLIENT_LIBRARY)

  if(GEN_HPP)
      add_dependencies(midiClient run_script)
  endif()
