import QtQuick 2.9

Rectangle {
    id: rectangle

    property alias clickInterval: timer.interval
    property bool clickMode: false
    property bool clickVisible: true
    property var parentItem: parent

    anchors.topMargin:    anchors.top    === parentItem.top    ? parentItem.border.width : 0
    anchors.leftMargin:   anchors.left   === parentItem.left   ? parentItem.border.width : 0
    anchors.rightMargin:  anchors.right  === parentItem.right  ? parentItem.border.width : 0
    anchors.bottomMargin: anchors.bottom === parentItem.bottom ? parentItem.border.width : 0

    signal open()
    signal hide()
    signal clicked()

    onVisibleChanged: visible ? /* emit */ open() : /* enum */ hide()

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        visible: clickMode
        onClicked: /* emit */ _private.click()
    }

    Timer {
        id: timer
        interval: 1000

        property bool isActive: false

        onTriggered: {
            isActive = false
            timer.stop()
        }
    }

    Item {
        id: _private

        function click(){
            timer.isActive = true
            timer.start()
            console.log("click rect")
            /* emit */ rectangle.clicked()
        }
    }
}
