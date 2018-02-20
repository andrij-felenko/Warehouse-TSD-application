import QtQuick 2.0

WItem {
    property alias text: main.text
    property alias textItem: main

    Text {
        id: main
        anchors.fill: parent
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        text: ""
        font.pointSize: parent.height > 3 ? parent.height / 3 : 3
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WrapAnywhere
        color: "navy"
    }
}
