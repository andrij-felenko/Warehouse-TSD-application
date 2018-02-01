import QtQuick 2.9

Rectangle {
    id: rectangle

    property alias clickInterval: timer.interval
    property bool clickMode: false
    property bool clickVisible: true

    anchors.topMargin: anchors.top === parent.top ? parent.border.width : 0
    anchors.bottomMargin: anchors.bottom === parent.bottom ? parent.border.width : 0
    anchors.leftMargin: anchors.left === parent.left ? parent.border.width : 0
    anchors.rightMargin: anchors.right === parent.right ? parent.border.width : 0

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
            console.log("click")
            /* emit */ rectangle.clicked()
        }
    }
}
