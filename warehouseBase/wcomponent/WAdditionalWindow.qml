import QtQuick 2.0

WRectangle {
    id: additionalWindow
    property alias content: contentItem.children
    property alias title: text.text

    WItemIconBorder {
        id: headerItem
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height / 13

        iconRightSource: "x_mark"
        iconRightVisible: true
        onRightChoosed: additionalWindow.visible = false

        content: WText {
            id: text
            anchors.fill: parent
        }
    }

    Item {
        id: contentItem
        anchors.top: headerItem.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
