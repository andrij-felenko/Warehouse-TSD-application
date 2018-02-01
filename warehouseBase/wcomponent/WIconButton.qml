import QtQuick 2.0

WRectangle {
    id: iconButton
    property alias text: text_.text
    property alias iconSource:  icon.source
    property alias iconPercent: icon.percent
    property alias iconColor:   icon.color
    property bool isRight: false
    clickMode: true

    signal iconClicked()

    anchors.topMargin:    anchors.top    === parent.top    ? parent.border.width : 0
    anchors.leftMargin:   anchors.left   === parent.left   ? parent.border.width : 0
    anchors.rightMargin:  anchors.right  === parent.right  ? parent.border.width : 0
    anchors.bottomMargin: anchors.bottom === parent.bottom ? parent.border.width : 0

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

    Text {
        id: text_
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left:  icon.visible ? isRight ? parent.left : icon.right : parent.left
        anchors.right: icon.visible ? isRight ? icon.left : parent.right : parent.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        visible: text !== ""
    }
}
