import QtQuick 2.9
import "qrc:/wcomponent"

WPage {
    title: "Меню"
    backMode: true
    header.iconLeftSource: "account_logout"

    onBack: mainStack.pop()
    onSetting: mainPage.currentIndex = 1

    content: WItem {
        anchors.fill: parent

        WIconButton {
            id: receiving
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 5
            height: parent.height / 12

            text: "Приемка"
            clickMode: true
            onClicked: mainStack.push(receivingComponent)
        }

        WIconButton {
            id: allotted
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: receiving.bottom
            anchors.topMargin: 5
            height: parent.height / 12

            text: "Перемещение"
            clickMode: true
            onClicked: mainStack.push(allottedComponent)
        }

        WIconButton {
            id: picking
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: allotted.bottom
            anchors.topMargin: 5
            height: parent.height / 12

            text: "Отбор"
            clickMode: true
            onClicked: mainStack.push(pickingComponent)
        }

        WIconButton {
            id: purchase
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: picking.bottom
            anchors.topMargin: 5
            height: parent.height / 12

            text: "Отгрузка"
            clickMode: true
            onClicked: mainStack.push(purchaseComponent)
        }

        Component {
            id: allottedComponent
            Allotted { parentItem: mainStack }
        }

        Component {
            id: pickingComponent
            Picking { parentItem: mainStack }
        }

        Component {
            id: purchaseComponent
            Purchase { parentItem: mainStack }
        }

        Component {
            id: receivingComponent
            Receiving { parentItem: mainStack }
        }
    }
}