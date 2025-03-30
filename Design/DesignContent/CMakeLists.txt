
qt_add_library(DesignContent STATIC)
qt6_add_qml_module(DesignContent
    URI "DesignContent"
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        About.qml
App.qml
ComboSilder.qml
EditPreset.qml
EditPresetControl.qml
FormGroupBox.qml
HeaderBar.qml
InPortEasyConfig.qml
InPortEasyConfigRoutes.qml
InPortEasyConfigSplits.qml
InPortMonitor.qml
InPortRoutes.qml
InPortSettings.qml
InPorts.qml
InPortsList.qml
InPortsRoutesFilterFnt.qml
InPortsRoutesFilterSchedule.qml
InPortsRoutesFilterToConsole.qml
InPortsRoutesFilterToMidi.qml
InPortsRoutesFilterToNetwork.qml
InPortsRoutesListFilters.qml
InPortsSettings14Bit.qml
InPortsSettingsProperate.qml
ListPresets.qml
LocalNetMidiOut.qml
Login.qml
MidiControlChannel.qml
MidiControlData.qml
MidiControlEventType.qml
Presets.qml
UserControls.qml
UserControlsDropdowns.qml
UserControlsEditControl.qml
UserControlsList.qml
VirtualPorts.qml
    RESOURCES
        icons/download_2_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
icons/ink_selection_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
icons/mop_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
icons/upload_2_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg
    )
