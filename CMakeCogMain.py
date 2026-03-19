from jinja2 import Environment, FileSystemLoader
import os

template_dict = {
           "APP_VER": "2.21.0",
           "APP_NAME": "midi-router-client",
           "APP_DESCRIPTION": "Midi router client",
           "APP_VENDOR": "shemeshg",
           "APP_IDENTIFIER": "com.shemeshg.midirouterclient",
           "APP_CONTACT":"https://github.com/shemeshg",           
           "MAIN_QML_URI": "MainQml",

           "CPACK_DEBIAN_PACKAGE_DEPENDS": ["libasound2-dev"],

           "QML_DIRS": ["Design","MidiRouterClientCli/Bal"],

           "QT_COMPONENTS": [ "Quick","Widgets","WebSockets","WebChannel","Svg","Concurrent", "QuickControls2", "QuickWidgets"],
           "add_subdirectory_lib": ["MidiRouterClientCli/Bal"],
           "add_subdirectory_qt": ["Design/Design", "Design/DesignContent", "Design/Core","Design/UiComp"]
           }

template_dict["add_subdirectory_lib_target"] = [os.path.basename(path) for path in template_dict["add_subdirectory_lib"]]
template_dict["add_subdirectory_qt_target"] = [os.path.basename(path) + "plugin" for path in template_dict["add_subdirectory_qt"]]
template_dict["add_subdirectory_qt_target"].append("Balplugin")

environment = Environment(loader=FileSystemLoader("."))
template = environment.get_template("CMakeCogMain.j2")


content = template.render(
    template_dict
)

def getCmake():   
    return content
#print(getCmake())
