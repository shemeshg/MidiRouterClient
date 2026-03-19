from jinja2 import Environment, FileSystemLoader
import os
import importlib.util

def get_parent_ver(relative_path=".."):
    # Build absolute path to the parent CMakeCogMain.py
    parent_file = os.path.abspath(
        os.path.join(os.path.dirname(__file__), relative_path, "CMakeCogMain.py")
    )

    if not os.path.isfile(parent_file):
        raise FileNotFoundError(f"Parent CMakeCogMain.py not found at: {parent_file}")

    # Dynamically load the parent module
    spec = importlib.util.spec_from_file_location("parent_cmake", parent_file)
    parent_module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(parent_module)

    # Return only the version string
    return parent_module.template_dict["APP_VER"]



template_dict = {
           "APP_VER": get_parent_ver(),
           "APP_NAME": "midi-router-client-cli",
           "APP_DESCRIPTION": "Midi router client cli",
           "APP_VENDOR": "shemeshg",
           "APP_IDENTIFIER": "com.shemeshg.midirouterclientcli",
           "APP_CONTACT":"https://github.com/shemeshg",           
           "MAIN_QML_URI": "MainQml",

           "CPACK_DEBIAN_PACKAGE_DEPENDS": ["libasound2-dev"],

           "QML_DIRS": ["Bal"],

           "QT_COMPONENTS": [ "Quick","Widgets","WebSockets","WebChannel","Svg","Concurrent", "QuickControls2", "QuickWidgets"],
           "add_subdirectory_lib": ["Bal"],
           "add_subdirectory_qt": []
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
