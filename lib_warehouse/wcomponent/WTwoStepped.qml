import QtQuick 2.0

WRectangle {
    property alias titleItem: main
    property alias title: main.text
    property alias subTitleItem: sub
    property alias subTitle: sub.text

    WText {
        id: main
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: sub.text === "" ? parent.height : parent.height * 0.8
    }

    WText {
        id: sub
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * 0.6
    }
}
