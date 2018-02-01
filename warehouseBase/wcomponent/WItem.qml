import QtQuick 2.0

Item {
    id: item
    property bool clickMode: false
    property bool barcodeMode: false

    signal open()
    signal hide()
    signal clicked()

    onVisibleChanged: visible ? /* emit */ open() : /* emit */ hide()

    MouseArea {
        anchors.fill: parent
        visible: clickMode
        onClicked: {
            /* emit */ item.clicked()
            console.log("click item")
        }
    }
}
