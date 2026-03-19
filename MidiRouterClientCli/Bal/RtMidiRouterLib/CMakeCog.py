import ImportScript
from CMakeCogLib import * 

def getCmake():   
    s = [] 
    cmc = CMakeCog("RtMidiRouterLib")
    s.append(cmc.cmake_minimum_required())
    s.append(cmc.project())
    s.append(cmc.CMAKE_CXX_STANDARD())

    cmc.find_package_qt_components = ["Widgets", "WebSockets", "WebChannel" ]
    s.append(cmc.find_package_qt())

    cmc.subdirectoryItem = [SubdirectoryItem("RtMidiWrap"), SubdirectoryItem("MidiClient")]
    s.append(cmc.add_subdirectory())

    genApp = GenHpp(cmc.exeName)
    genApp.makeDirectories = ["${CMAKE_CURRENT_BINARY_DIR}/webchannel"]
    genApp.hppGenFilesTemplates = ["${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt"]
    genApp.hppGenFilesGlobes = ['webchannel/*.hpp']
    genApp.parseHppPyPath = "${CMAKE_SOURCE_DIR}/scripts/parseHpp.py"

    s.append(genApp.getStr())

    cmc.libFilesExtendCppAndH([
        '',
        'libs/QWebchannelCppClient',
        'libs/websocket',
        'MidiRoute/filters',
        'MidiRoute',
        'webchannel'])

    cmc.libFiles.extend(genApp.getDefineFiles("${CMAKE_CURRENT_BINARY_DIR}/"))
    s.append(cmc.add_library())
    s.append(cmc.target_link_libraries())
    s.append(cmc.target_compile_definitions())
    cmc.targetIncludeDirs = [
        '${CMAKE_CURRENT_BINARY_DIR}/MidiClient/GenHpp',
        '${CMAKE_CURRENT_BINARY_DIR}/webchannel',
        'webchannel'
                            ]

    s.append(cmc.target_include_directories())
    s.append(genApp.add_dependencies())
    return "\n".join(s)

#print(getCmake())
