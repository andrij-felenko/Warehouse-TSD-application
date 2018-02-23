import QtQuick 2.9
import "qrc:/wcomponent"
import WUrl 1.0

WPage {
    id: auth
    header.iconLeftSource: "power_4"
    header.onLeftChoosed: WApp.quit()
    titleItem.textItem.horizontalAlignment: Text.AlignHCenter
    title: "Авторизация"

    signal authorization(string password)

    content: WRectangle {
        anchors.fill: parent

        color: "#504d4a"

        signal addUser()
        signal forgetPassword(string login)

        Image {
            id: logo_item
            width: parent.width * 0.4
            fillMode: Image.PreserveAspectFit
            x: parent.width * 0.3
            y: 20
            source: "qrc:/icon/cheese.png"

            MouseArea {
                anchors.fill: parent
                onClicked: WApp.quit()
            }
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
            iconRightSource: "list"
            iconRightVisible: true

            onAccepted: password_input.input.focus = true
        }

        WItemIconBorder {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: password_input.top
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.bottomMargin: 20
            height: parent.height / 13

            iconLeftSource: "businessman"
            iconLeftVisible: true
            iconRightSource: "" // textInputAuth.visible ? "text" : "list"
            iconRightVisible: false // true
            onRightChoosed: textInputAuth.visible = ! textInputAuth.visible
            contentBorder: textInputAuth.visible ? contentBorderDefault : 0

            content: [
                TextInput {
                    id: textInputAuth
                    anchors.fill: parent
                    font.pixelSize: height * 0.4
                    verticalAlignment: Text.AlignVCenter
                    onVisibleChanged: if (visible) text = User.current.name
                    clip: true
                    visible: false
                    onAccepted: {
                        User.setUserInput(text)
                        password_input.input.focus = true
                    }
                },

                WComboBox {
                    id: comboBoxAuth
                    anchors.fill: parent
                    visible: ! textInputAuth.visible
                    onOpenList: {
                        Model.employeeList(true)
                        additional.push(comboBoxListComponent)
                        console.log(WUrl.Receiving, " pp")
                    }
                }
            ]

            EmployeeList {
                id: comboBoxListComponent
            }
        }

        WTextInput {
            id: password_input
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            y: (parent.height - height) / 2
            height: parent.height / 13
            hideSymbol: true

            iconLeftSource: "lock"
            iconLeftVisible: true
            iconRightSource: hideSymbol ? "invisible" : "visible"
            onRightChoosed: hideSymbol = ! hideSymbol
            iconRightVisible: true
            onAccepted: sign_in.clicked()
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
            clickMode: true

            text: qsTr("Войти")
//            iconSource: "add_user_2"
            onClicked: {
                /* emit */ auth.authorization(password_input.text)
                password_input.text = ""
            }
        }

        Text {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 20
            height: parent.height / 18
            color: "#ffffff"
            wrapMode: Text.WrapAnywhere
            text: WApp.appName + " v. " + WApp.version + "\nWHLib v. 1.0"
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 8
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
            text: "\n© Andrij Felenko"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pointSize: 6
        }
    }
}
