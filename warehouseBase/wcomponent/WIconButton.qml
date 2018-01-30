import QtQuick 2.0

FRectangle {
    id: iconButton
    property alias text: text_.text
    property alias iconSource: icon.source
    property alias iconPercent: icon.percent
    property alias iconColor: icon.color
    property bool isRight: false

    FIcon {
        id: icon
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left:  isRight ? undefined : parent.left
        anchors.right: isRight ? undefined : parent.right
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
