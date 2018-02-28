import QtQuick 2.9
import "qrc:/wcomponent"
import WUrl 1.0
import WDocument 1.0

WPage {
    title: "Меню"
    backMode: true
    header.iconLeftSource: "account_logout"

    onBack: mainStack.pop()
    header.onRightChoosed: mainPage.currentIndex = 1

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
            onClicked: {
                WDocList.requestDocumentList(WUrl.Receiving)
                Model.documentList(WUrl.Receiving, true)
                mainStack.push(receivingComponent)
            }
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
            id: allottedComponent // приемка
            Allotted {  }
        }

        Component {
            id: pickingComponent // перемещение
            Picking {  }
        }

        Component {
            id: purchaseComponent // отгрузка
            Purchase {  }
        }

        Component {
            id: receivingComponent // приемка
            Receiving {  }
        }
    }
}
