import QtQuick 2.9
import "qrc:/wcomponent"

Rectangle {
    color: "#504d4a"
    anchors.fill: parent

    signal addUser()
    signal forgetPassword(string login)

    Image {
        id: logo_item
        width: parent.width * 0.6
        fillMode: Image.PreserveAspectFit
        x: parent.width * 0.2
        y: 20
        source: "qrc:/icon/haiku.png"

        MouseArea {
            anchors.fill: parent
            onClicked: WApp.quit()
        }
    }

    WIcon {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: height / 4
        anchors.rightMargin: height / 4
        anchors.topMargin: height / 4
        anchors.bottomMargin: height / 4
        height: width
        width: parent.width / 6
        source: "power_2"
    }

    WTextInput {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: password_input.top
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        height: parent.height / 13

        iconLeftSource: "businessman"
        iconLeftVisible: true
        onAccepted: password_input.input.focus = true
    }

    WTextInput {
        id: password_input
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        y: (parent.height - height) / 2
        height: parent.height / 13

        iconLeftSource: "lock"
        iconLeftVisible: true
        iconRightSource: "visible"
        iconRightVisible: true
    }

    WIconButton {
        id: sign_in
        anchors.top: password_input.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        height: parent.height / 13

        text: "Sign up"
        iconSource: "add_user_2"
    }

    Text {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        height: parent.height / 18
        color: "#ffffff"
        wrapMode: Text.WrapAnywhere
        text: "January 2018\nWarehouse manager v. 0.1"
        font.pointSize: 9
    }

    Text {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        height: parent.height / 18
        width: parent.width

        color: "#ffffff"
        wrapMode: Text.WrapAnywhere
        text: "\n© Andrey Felenko"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        font.pointSize: 8
    }
}
