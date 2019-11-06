import QtQuick 2.9

WIconButton {
    property int size: parent.width / 14

    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.bottomMargin: size
    anchors.rightMargin: size

    width: size * 2
    height: size * 2
    border.width: 3
    radius: size
}
