### This file is automatically generated by Qt Design Studio.
### Do not change

add_subdirectory(Core)
add_subdirectory(Design)
add_subdirectory(Bal)
add_subdirectory(DesignContent)
add_subdirectory(App)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Coreplugin
    Designplugin
    Balplugin
    DesignContentplugin)