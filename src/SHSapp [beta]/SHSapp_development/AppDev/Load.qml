import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import SHSengine 1.0
import QtQuick.Controls.Styles 1.4





Item {
    
    id: toggleSwitch
    text: "load"
    Material.accent: Material.Orange
    
    onCheckedChanged: {
        shs_engine.onSwitchToggled(checked);
    }
}
