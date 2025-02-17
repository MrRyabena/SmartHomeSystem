import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import SHSengine 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12


import "./SHSbuild/SHSqt_core/SHSqml_core"


ApplicationWindow {
    visible: true

    width: 640
    height: 480
    property int defMargin: 20
    minimumWidth: columnLayout.implicitWidth + 2*defMargin
    minimumHeight: columnLayout.implicitHeight + 2*defMargin

    title: qsTr("Smart Home System")
    Material.theme: Material.Dark


    ColumnLayout {
        id: columnLayout
        anchors.centerIn: parent
        anchors.fill: parent
        spacing: defMargin / 2


        Load {
            id: load
            Layout.fillWidth: true
            Layout.margins: defMargin

            onChanged: shs_engine.onSwitchToggled(checked)
        }

        Sensor {
            id: sensor
            Layout.fillWidth: true
            Layout.margins: defMargin
        }

        Item {
            Layout.fillHeight: true
            //Layout.minimumHeight: 100
            Layout.minimumWidth: 280
        }
    }

    SHSengine {
        id: shs_engine
        onSensorUpdated: sensor.value = sensorValue
        onSensorConnectionSignal: sensor.isConnected = sensorConnected
        onLoadConnectionSignal: load.isConnected = loadConnected
    }
}

