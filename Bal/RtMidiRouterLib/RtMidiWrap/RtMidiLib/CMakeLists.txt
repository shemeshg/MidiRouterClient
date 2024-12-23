cmake_minimum_required(VERSION 3.10)
project(RtMidiLib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


set(RtMidiLib_SRCS
RtMidi.h
RtMidi.cpp
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()
if(WIN32 OR MSVC OR MSYS OR MINGW)
    set(WINDOWS TRUE)
endif()

if(MACOSX)
    # https://stackoverflow.com/questions/4929255/building-static-libraries-on-mac-using-cmake-and-gcc
    SET(CMAKE_C_ARCHIVE_CREATE   "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
    SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
    SET(CMAKE_C_ARCHIVE_FINISH   "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
    SET(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")

    #RtMidi lib dependencies
    find_library(COREMIDI_LIBRARY CoreMIDI)
    find_library(COREAUDIO_LIBRARY CoreAudio)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)

    list(APPEND OsSpecificLibs
        ${COREFOUNDATION_LIBRARY}
        ${COREAUDIO_LIBRARY}
        ${COREMIDI_LIBRARY}
        )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__MACOSX_CORE__")
endif()

if(LINUX)
    option(RTMIDI_API_ALSA "Compile with ALSA support." ON)
    set(NEED_PTHREAD ON)
    find_package(ALSA)
    if (NOT ALSA_FOUND)
      message(FATAL_ERROR "ALSA API requested but no ALSA dev libraries found")
    endif()
    list(APPEND INCDIRS ${ALSA_INCLUDE_DIR})
    list(APPEND LINKLIBS ${ALSA_LIBRARY})

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__LINUX_ALSA__")

 endif()

 if(WINDOWS)
     list(APPEND OsSpecificLibs
         winmm
         )
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__WINDOWS_MM__")
 endif()

# Declare the library
add_library(RtMidiLib STATIC
    ${RtMidiLib_SRCS}
)

# Specify here the include directories exported
# by this library

target_include_directories(RtMidiLib
    PRIVATE ${INCDIRS}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(RtMidiLib PRIVATE
    ${OsSpecificLibs}
    ${LINKLIBS}
    )



