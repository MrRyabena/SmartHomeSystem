import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

WidgetBase {
    id: sensor
    width: 200
    height: 100
    moduleName: "Sensor Module"
       isConnected: false

    Material.accent: Material.Blue

    property real value: 0.0

        Text {
            id: sensorDisplay
            anchors.centerIn: parent
            text: "Temperature: " + value.toFixed(2) + " °C"
            font.pixelSize: 20
            color: "white"
        }

}
