
        set_source_files_properties(CoreSystemPalette.qml
            PROPERTIES
                QT_QML_SINGLETON_TYPE true
        )
            
    qt_add_library(Core STATIC)
    qt6_add_qml_module(Core
        URI "Core"
        VERSION 1.0
        RESOURCE_PREFIX "/qt/qml"
        QML_FILES
            CoreButton.qml
CoreCheckBox.qml
CoreComboBox.qml
CoreGroupBox.qml
CoreLabel.qml
CoreLabelSelect.qml
CoreSlider.qml
CoreSwitch.qml
CoreSystemPalette.qml
CoreTextArea.qml
CoreTextField.qml
CoreToolTip.qml
        RESOURCES
            
        )
    