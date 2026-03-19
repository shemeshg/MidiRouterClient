import ImportScript
from CMakeCogLib import * 

def getCmake():   
    s = [] 
    cmc = CMakeCog("MidiClient")

    cmc.find_package_qt_components = ["Widgets", "WebSockets", "WebChannel" ]
    s.append(cmc.find_package_qt())



    genApp = GenHpp(cmc.exeName)
    genApp.makeDirectories = ["${CMAKE_CURRENT_BINARY_DIR}/GenHpp",
                              "${CMAKE_CURRENT_BINARY_DIR}/genPrpt"]
    genApp.hppGenFilesTemplates = ["${CMAKE_SOURCE_DIR}/scripts/hppTemplates.txt"]
    genApp.hppGenFilesGlobes = ['hpp/*.hpp', 'genPrpt/*.hpp']
    genApp.parseHppPyPath = "${CMAKE_SOURCE_DIR}/scripts/parseHpp.py"

    s.append(genApp.getStr())

    cmc.libFiles.extend(genApp.getDefineFiles("${CMAKE_CURRENT_BINARY_DIR}/"))

    s.append(cmc.add_library())
    s.append(cmc.target_link_libraries())
    s.append(cmc.target_compile_definitions())

    s.append(genApp.add_dependencies())
    return "\n".join(s)

#print(getCmake())
