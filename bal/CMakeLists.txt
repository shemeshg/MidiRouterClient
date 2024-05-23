find_package(Qt6 REQUIRED COMPONENTS Concurrent)
add_subdirectory(RtMidiRouterLib)

link_libraries(
     Qt6::Concurrent
     RtMidiRouterLib
)

qt6_add_qml_module(bal
        URI Bal
        VERSION 1.0
        SOURCES
            BalData.h
            BalData.cpp
            BalDataPrivate.h
            BalDataPrivate.cpp        
            JsAsync.h
              )
