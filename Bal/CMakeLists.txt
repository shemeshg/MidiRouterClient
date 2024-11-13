find_package(Qt6 REQUIRED COMPONENTS Concurrent)
add_subdirectory(RtMidiRouterLib)


qt_add_library(Bal STATIC)
qt6_add_qml_module(Bal
    URI "Bal"
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    SOURCES
      BalData.h
      BalData.cpp
      BalDataPrivate.h
      BalDataPrivate.cpp        
      JsAsync.h
)



target_link_libraries(Bal PRIVATE Qt6::Concurrent RtMidiRouterLib)
