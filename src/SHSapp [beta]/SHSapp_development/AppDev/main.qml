import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import SHSengine 1.0
import QtQuick.Controls.Styles 1.4


//import QtCharts 2.0


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Material.theme: Material.Dark



    //Material.accent: Material.Purple



    ListView {

        anchors.centerIn: parent

        Load {
            id: toggleSwitch
        }

        Text {
            id: sensor
            text: "0.0";
        }

        SHSengine {
               id: shs_engine
               onSensorUpdated: sensor.text = "Sensor value:  " + sensorValue
           }

    }
}

