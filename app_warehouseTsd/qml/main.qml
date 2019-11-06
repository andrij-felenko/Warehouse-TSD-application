import QtQuick 2.9
import "qrc:/wcomponent"
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0

Item {
    anchors.fill: parent

    StackLayout {
        id: mainPage
        anchors.fill: parent

        Stack {
            anchors.fill: parent
        }

        Setting {
            anchors.fill: parent
        }
    }

    Additional {
        id: additional
        anchors.fill: parent
        z: 1
    }

    WMsg {
        anchors.fill: parent
        z: 2
    }

    SystemTrayIcon {
        visible: true
        iconSource: "qrc:/icon/cheese.png"

        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }
}
