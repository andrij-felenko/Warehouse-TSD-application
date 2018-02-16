import QtQuick 2.0

WRectangle {
    id: iconButton
    property alias text: text_.text
    property alias iconSource:  icon.source
    property alias iconPercent: icon.percent
    property alias iconColor:   icon.color
    property bool isRight: false

    signal iconClicked()

    anchors.topMargin:    anchors.top    === parentItem.top    ? private_.parentItemBorderWidth : 0
    anchors.leftMargin:   anchors.left   === parentItem.left   ? private_.parentItemBorderWidth : 0
    anchors.rightMargin:  anchors.right  === parentItem.right  ? private_.parentItemBorderWidth : 0
    anchors.bottomMargin: anchors.bottom === parentItem.bottom ? private_.parentItemBorderWidth : 0

    WIcon {
        id: icon
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left:  isRight ? undefined : parent.left
        anchors.right: isRight ? parent.right : undefined
        width: height
        clickMode: true

        onClicked: /* emit */ iconButton.iconClicked()
    }

    WText {
        id: text_
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left:  icon.visible ? isRight ? parent.left : icon.right : parent.left
        anchors.right: icon.visible ? isRight ? icon.left : parent.right : parent.right
        textItem.horizontalAlignment: Text.AlignHCenter
        textItem.verticalAlignment: Text.AlignVCenter
        visible: text !== ""
    }

    Item {
        id: private_
        property int parentItemBorderWidth: parentItem.border === undefined ? 0 : parentItem.border.width
    }
}
