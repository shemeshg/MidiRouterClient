cmake_minimum_required(VERSION 3.16)

project(midiRouterClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # Append -fPIC to the CXXFLAGS only if the system is Linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()




find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)


list(APPEND QML_DIRS CMAKE_CURRENT_SOURCE_DIR}/Design/ ${CMAKE_CURRENT_BINARY_DIR}/Bal)
set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Import paths for Qt Creator's code model" FORCE)



qt_add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)


qt_add_qml_module(${CMAKE_PROJECT_NAME}
    URI Shalom
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appshalom
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

add_subdirectory(Design/Design)
add_subdirectory(Design/DesignContent)
add_subdirectory(Design/Core)
add_subdirectory(Bal)



target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE Qt6::Quick
    Bal
    Coreplugin
    Designplugin
    DesignContentplugin
)

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
