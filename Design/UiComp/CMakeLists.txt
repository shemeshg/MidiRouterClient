qt_add_library(UiComp STATIC)
qt6_add_qml_module(UiComp
    URI "UiComp"
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        "UiTitleAdd.qml"
        "UiTitle.qml"
        "UiBtnAdd.qml"
        "UiBtnDel.qml"
        "UiBtnEdit.qml"
        "UiBtnBack.qml"
    )



