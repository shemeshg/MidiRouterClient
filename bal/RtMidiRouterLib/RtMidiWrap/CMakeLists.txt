set(RtMidiWrap_SRCS
      RtMidiWrap.cpp
      common.cpp
      midievent.cpp
      playmidi.cpp
      playmidiin.cpp
      playmidiout.cpp
      RtMidiWrap.h
      common.h
      midievent.h
      playmidi.h
      playmidiin.h
      playmidiout.h
      songposition.h
)

add_subdirectory(RtMidiLib)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()
if(WIN32 OR MSVC OR MSYS OR MINGW)
    set(WINDOWS TRUE)
endif()

# Declare the library
add_library(RtMidiWrap STATIC
    ${RtMidiWrap_SRCS}
)

# Specify here the include directories exported
# by this library

target_include_directories(RtMidiWrap
    PRIVATE ${INCDIRS}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/RtMidiWrap"    
)

target_link_libraries(RtMidiWrap PUBLIC RtMidiLib)
