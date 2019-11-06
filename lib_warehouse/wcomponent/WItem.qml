import QtQuick 2.0

Item {
    id: item
    property bool clickMode: false
    property bool barcodeMode: false
    property alias wborder: _wborder

    anchors.topMargin: _wborder.btop ? _wborder.sizeV : 0
    anchors.leftMargin: _wborder.bleft ? _wborder.sizeH : 0
    anchors.rightMargin: _wborder.bright ? _wborder.sizeH : 0
    anchors.bottomMargin: _wborder.bbottom ? _wborder.sizeV : 0

    signal open()
    signal hide()
    signal clicked()

    onVisibleChanged: visible ? /* emit */ open() : /* emit */ hide()

    WBorder { id: _wborder }

    MouseArea {
        anchors.fill: parent
        visible: clickMode
        onClicked: {
            /* emit */ item.clicked()
            console.log("click item")
        }
    }
}
