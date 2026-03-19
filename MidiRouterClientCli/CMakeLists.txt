# [[[cog
# import cog
# from CMakeCogMain import getCmake
# cog.outl(getCmake())
# ]]]
cmake_minimum_required(VERSION 3.16)

project(midi-router-client-cli VERSION 2.22.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # Append -fPIC to the CXXFLAGS only if the system is Linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()


find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Widgets WebSockets WebChannel Svg Concurrent QuickControls2 QuickWidgets)

qt_standard_project_setup(REQUIRES 6.5)


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    set(MACOSX TRUE)
    set(PROJECT_OS "MACOSX")
endif()
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
    set(PROJECT_OS "LINUX")
endif()
if(WIN32 OR MSVC OR MSYS OR MINGW)
    set(WINDOWS TRUE)
    set(PROJECT_OS "WINDOWS")
endif()
if(MACOSX)
    # Application icon
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set(CPACK_PACKAGE_NAME midi-router-client-cli)
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Midi router client cli")
    set(CPACK_PACKAGE_VENDOR "shemeshg")    
endif()

    
    

list(APPEND QML_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/Bal )
set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Import paths for Qt Creator's code model" FORCE)



qt_add_executable(${CMAKE_PROJECT_NAME}
    cli/main.cpp
    MANUAL_FINALIZATION
    ${APP_ICON_MACOSX}
)

if(WINDOWS)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE cli/CliWinService.cpp)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.shemeshg.midirouterclientcli
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
    OUTPUT_NAME "midi-router-client-cli"
)


if(LINUX)
    set(CPACK_PACKAGE_NAME midi-router-client-cli)
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Midi router client cli")
    set(CPACK_PACKAGE_VENDOR "shemeshg")   
    set(CPACK_PACKAGE_CONTACT "https://github.com/shemeshg") 
    set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
    set(CPACK_VERBATIM_VARIABLES ON)
    set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/midi-router-client-cli")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "shemeshg <https://github.com/shemeshg>")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libasound2-dev")
    INSTALL(FILES midi-router-client-cli.desktop DESTINATION share/applications)
    install(FILES midi-router-client-cli.png DESTINATION share/icons/hicolor/256x256/apps)
    install(FILES deployScript/midi-router-client-cli.sh DESTINATION bin)

    # dynamically configured debian control scripts
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deployScript/postinst
        ${CMAKE_CURRENT_BINARY_DIR}/deployScript/postinst)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deployScript/prerm
        ${CMAKE_CURRENT_BINARY_DIR}/deployScript/prerm)


    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_BINARY_DIR}/deployScript/postinst;${CMAKE_CURRENT_BINARY_DIR}/deployScript/prerm;")


    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA, ./deployScript/postinst)
    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA, ./deployScript/prerm)

endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET midi-router-client-cli PROPERTY WIN32_EXECUTABLE FALSE)

    if(WINDOWS)
      install(FILES
            ${CMAKE_SOURCE_DIR}/icon.ico
            DESTINATION bin)
    endif()

    # set the install/uninstall icon used for the installer itself
    set (CPACK_NSIS_MUI_ICON
        "${CMAKE_SOURCE_DIR}/icon.ico")
    set (CPACK_NSIS_MUI_UNIICON
        "${CMAKE_SOURCE_DIR}/icon.ico")

    # set the add/remove programs icon using an installed executable
    SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\midi-router-client-cli.exe")

    set (CPACK_NSIS_PACKAGE_NAME "midi-router-client-cli")

    set (CPACK_RESOURCE_FILE_LICENSE
        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

    set (CPACK_CREATE_DESKTOP_LINKS midi-router-client-cli)

    set (CPACK_PACKAGE_INSTALL_DIRECTORY "midi-router-client-cli")
    set (CPACK_PACKAGE_INSTALL_REGISTRY_KEY "midi-router-client-cli")
    set (CPACK_PACKAGE_EXECUTABLES "midi-router-client-cli" "midi-router-client-cli")

    #cpack_add_component(development DISPLAY_NAME
    #    "midi-router-client-cli" )

    set (CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_CREATE_ICONS_EXTRA
        "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\midi-router-client-cli.lnk' '$INSTDIR\\\\bin\\\\midi-router-client-cli.exe' '' '$INSTDIR\\\\bin\\\\icon.ico'"
    )

endif()


add_subdirectory(Bal)
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE 
    Qt6::Quick
    Qt6::Widgets
    Qt6::WebSockets
    Qt6::WebChannel
    Qt6::Svg
    Qt6::Concurrent
    Qt6::QuickControls2
    Qt6::QuickWidgets
    Bal
    Balplugin
    )
include(CPack)
include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(midi-router-client-cli)
# Generate the deployment script for the target midi-router-client-cli.
qt_generate_deploy_qml_app_script(
    TARGET midi-router-client-cli
    OUTPUT_SCRIPT deploy_script
    # NO_UNSUPPORTED_PLATFORM_ERROR
)

# Call the deployment script on "cmake --install".
install(SCRIPT ${deploy_script})

configure_file("${PROJECT_SOURCE_DIR}/config.h.in" "${CMAKE_BINARY_DIR}/config.h")
# [[[end]]]
