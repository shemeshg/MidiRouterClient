find_package(Qt6 REQUIRED COMPONENTS Concurrent Gui)
add_subdirectory(RtMidiRouterLib)


qt6_add_qml_module(Bal
    URI "Bal"
    VERSION 1.0
    STATIC
    RESOURCE_PREFIX "/qt/qml"
    SOURCES
      BalData.h
      BalData.cpp
      BalDataPrivate.h
      BalDataPrivate.cpp        
      JsAsync.h
      ${CMAKE_BINARY_DIR}/config.h
)



target_link_libraries(Bal PRIVATE Qt6::Concurrent Qt6::Gui RtMidiRouterLib)
target_include_directories(Bal PRIVATE
${CMAKE_BINARY_DIR}
    )
