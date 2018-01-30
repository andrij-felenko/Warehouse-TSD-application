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
    }

    Item {
        anchors.right: parent.right
        anchors.top: parent.top
        height: width
        width: parent.width / 5

        Image {
            anchors.fill: parent
            anchors.leftMargin: parent.height / 4
            anchors.rightMargin: parent.height / 4
            anchors.topMargin: parent.height / 4
            anchors.bottomMargin: parent.height / 4
            fillMode: Image.PreserveAspectFit
            source: "qrc:/icon/power_2.png"
        }
    }

    Rectangle {
        id: login_input
        anchors.top: logo_item.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        height: parent.height / 13
        opacity: 0.9

        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: login_icon.right
            anchors.right: parent.right
            anchors.topMargin: 1
            anchors.bottomMargin: 1
            anchors.leftMargin: 1
            anchors.rightMargin: 1
            color: "black"

            TextInput {
                anchors.centerIn: parent
            }
        }

        TextInput {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: login_icon.right
            anchors.right: parent.right
            anchors.topMargin: 1
            anchors.bottomMargin: 1
            anchors.leftMargin: 10
            anchors.rightMargin: 1
            color: "white"
            font.pointSize: 9
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {
            id: login_icon
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: height
            color: "white"

            Image {
                anchors.fill: parent
                anchors.leftMargin: parent.height / 4
                anchors.rightMargin: parent.height / 4
                anchors.topMargin: parent.height / 4
                anchors.bottomMargin: parent.height / 4
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icon/businessman.png"
            }
        }
    }

    Rectangle {
        id: password_input
        anchors.top: login_input.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        height: parent.height / 13
        opacity: 0.9

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: height
            color: "white"

            Image {
                anchors.fill: parent
                anchors.leftMargin: parent.height / 4
                anchors.rightMargin: parent.height / 4
                anchors.topMargin: parent.height / 4
                anchors.bottomMargin: parent.height / 4
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icon/lock.png"
            }
        }

        Rectangle {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: height
            color: "white"
            opacity: 0.5

            Image {
                anchors.fill: parent
                anchors.leftMargin: parent.height / 4
                anchors.rightMargin: parent.height / 4
                anchors.topMargin: parent.height / 4
                anchors.bottomMargin: parent.height / 4
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icon/question_mark_4.png"
            }
        }
    }

    Rectangle {
        id: sign_in
        anchors.top: password_input.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        height: parent.height / 13

        Rectangle {
            id: add_user_item
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: height
            color: "#acc864"

            Image {
                anchors.fill: parent
                anchors.leftMargin: parent.height / 4
                anchors.rightMargin: parent.height / 4
                anchors.topMargin: parent.height / 4
                anchors.bottomMargin: parent.height / 4
                fillMode: Image.PreserveAspectFit
                source: "qrc:/icon/add_user_2.png"
            }
        }

        Rectangle {
            anchors.left: add_user_item.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            color: "#008f47"

            Text {
                anchors.fill: parent
                text: "Sign up"
                font.pointSize: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "white"
            }
        }
    }

    WTextInput {
        anchors.top: sign_in.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        height: parent.height / 13

        iconLeftSource: "angry"
        iconLeftVisible: true
        iconRightVisible: true
        iconRightSource: "comments"
    }

    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        height: parent.height / 18
        width: parent.width

        Text {
            width: parent.width
            color: "#ffffff"
            wrapMode: Text.WrapAnywhere
            text: "Noto v. 0.1"
            font.pointSize: 9
        }
    }

    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: parent.height / 18
        width: parent.width

        Text {
            width: parent.width
            color: "#ffffff"
            wrapMode: Text.WrapAnywhere
            text: "Jan. 2018"
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 9
        }
    }

    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        height: parent.height / 18
        width: parent.width

        Text {
            color: "#ffffff"
            anchors.right: parent.right
            wrapMode: Text.WrapAnywhere
            text: "Andrey Felenko"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 8
        }
    }
}
