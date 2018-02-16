import QtQuick 2.9
import "qrc:/wcomponent"
import QtQuick.Layouts 1.3

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
}
