import QtQuick 2.9

Rectangle {
    id: rectangle

    property alias wborder: _wborder
    property alias clickInterval: timer.interval
    property bool clickMode: false
    property bool clickVisible: true

    anchors.topMargin: _wborder.btop ? _wborder.sizeV : 0
    anchors.leftMargin: _wborder.bleft ? _wborder.sizeH : 0
    anchors.rightMargin: _wborder.bright ? _wborder.sizeH : 0
    anchors.bottomMargin: _wborder.bbottom ? _wborder.sizeV : 0

    signal open()
    signal hide()
    signal clicked()

    onVisibleChanged: visible ? /* emit */ open() : /* enum */ hide()

    WBorder { id: _wborder }

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
