
qt_add_library(UiComp STATIC)
qt6_add_qml_module(UiComp
    URI "UiComp"
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        UiBtnAdd.qml
UiBtnBack.qml
UiBtnDel.qml
UiBtnEdit.qml
UiBtnUp.qml
UiTitle.qml
UiTitleAdd.qml
    RESOURCES
        icons/add_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
icons/arrow_back_ios_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
icons/close_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
icons/edit_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
    )
