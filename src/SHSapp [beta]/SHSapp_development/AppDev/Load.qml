import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

WidgetBase {
    id: toggleSwitch
        moduleName: "Load Module"
        isConnected: false

    Material.accent: Material.Orange
    signal changed(bool checked)

    Switch {
        id: loadSwitch
        anchors.centerIn: parent
        text: "Load Control"

        onCheckedChanged: changed(checked)


    }

}
