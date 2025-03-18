SET(GEN_HPP TRUE)
if(GEN_HPP)
    make_directory(${CMAKE_CURRENT_BINARY_DIR}/GenHpp)
    make_directory(${CMAKE_CURRENT_BINARY_DIR}/genPrpt)
    
    file(GLOB HPP_GEN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/hpp/*.hpp"  )
    file(GLOB HPP_PRPT_GEN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/genPrpt/*.hpp"  )
    set(HPP_GEN_FILES 
        ${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt 
        ${HPP_GEN_FILES} 
        ${HPP_PRPT_GEN_FILES}
    )
    add_custom_target(run_script01 ALL
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



find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebSockets WebChannel REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebSockets WebChannel REQUIRED)


add_library(midiClient STATIC
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/Dropdownlist.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/EasyConfigPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/EasyConfigRoutePrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterAndTransformPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterMidiDestinationPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterNetworkDestinationPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterSchedulePrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/FilterToConslePrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiClientConnectionPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRouteInputCc14bit.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRouteInputPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutePresetPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRouterChainPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MonitorPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/PresetMidiControlPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/UserControlPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/UserDataConfigPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfig.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfigRoute.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterAndTransform.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterMidiDestination.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterNetworkDestination.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterSchedule.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterToConsle.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientConnection.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientUtil.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouteInput.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRoutePreset.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouterChain.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/Monitor.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/PresetMidiControl.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserConfigParseJson.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserControl.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserDataConfig.h
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfig.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/EasyConfigRoute.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterAndTransform.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterMidiDestination.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterNetworkDestination.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterSchedule.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/FilterToConsle.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientConnection.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiClientUtil.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouteInput.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRoutePreset.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/MidiRouterChain.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/Monitor.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/PresetMidiControl.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserConfigParseJson.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserControl.cpp
${CMAKE_CURRENT_BINARY_DIR}/GenHpp/UserDataConfig.cpp
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutersFilterPrivate.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutersFilter.h
${CMAKE_CURRENT_BINARY_DIR}/genPrpt/MidiRoutersFilter.cpp
)

  target_link_libraries(midiClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::WebChannel
          )

  target_compile_definitions(midiClient PRIVATE MIDICLIENT_LIBRARY)

  if(GEN_HPP)
    add_dependencies(midiClient run_script01)
  endif()
