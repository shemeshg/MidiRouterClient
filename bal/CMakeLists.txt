find_package(Qt6 REQUIRED COMPONENTS Concurrent)
add_subdirectory(RtMidiRouterLib)


qt6_add_qml_module(Bal
        URI Bal
        VERSION 1.0
        SOURCES
            BalData.h
            BalData.cpp
            BalDataPrivate.h
            BalDataPrivate.cpp        
            JsAsync.h
              )

target_link_libraries(Bal PRIVATE Qt6::Concurrent RtMidiRouterLib)
