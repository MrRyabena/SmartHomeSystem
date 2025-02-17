import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: widgetBase
    implicitWidth: 200
    implicitHeight: 100
    property int defMargin: 10
    property string moduleName: "Module"
    property bool isConnected: false


    Rectangle {
        anchors.fill: parent
        color: "#0f0A9396"
        //Material.color: Material.BlueGrey
        //border.color: Material.Blue
        //Material.background: Material.BlueGrey
        radius: 20
        border.width: 2.5
        border.color:  "#ABBE40"


//            anchors.fill: parent
//            anchors.margins: defMargin
//            spacing: defMargin

            Text {
                text: moduleName
                font.pixelSize: 16
                color: "white"

                horizontalAlignment: Text.AlignHCenter
                anchors.margins: 10
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Text {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 10
                text: isConnected ? "Connected" : "Disconnected"
                font.pixelSize: 12
                color: isConnected ? "green" : "red"
                horizontalAlignment: Text.AlignHCenter
            }

            Item {
                id: content
                anchors.fill: parent
            }
        }
    //}
}
