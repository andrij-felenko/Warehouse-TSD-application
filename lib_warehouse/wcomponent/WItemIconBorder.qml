import QtQuick 2.9

WRectangle {
    id: itemIconBorder
    color: "#CBCBCB"
    wborder.sizeH: height / 16
    wborder.sizeV: height / 16

    property bool iconLeftVisible:  false
    property bool iconRightVisible: false
    property bool iconRight2Visible: false
    property bool hideSymbol: false

    property alias iconLeftSource: iconLeft_.iconSource
    property alias iconRightSource: iconRight_.iconSource
    property alias iconRight2Source: iconRight_2.iconSource
    property alias iconLeft:  iconLeft_
    property alias iconRight: iconRight_
    property alias iconRight2: iconRight_2
    property alias content: contentItem.children

    signal leftChoosed()
    signal rightChoosed()
    signal right2Choosed()

    WIconButton {
        id: iconLeft_
        z: 1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        wborder.sizeH: itemIconBorder.wborder.sizeH
        wborder.sizeV: itemIconBorder.wborder.sizeV
        wborder.btop: true
        wborder.bleft: true
        wborder.bbottom: true

        width: height
        visible: iconLeftSource !== "" && iconLeftVisible
        onIconClicked: /* emit */ itemIconBorder.leftChoosed()
    }

    WIconButton {
        id: iconRight_
        z: 1
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        wborder.sizeH: itemIconBorder.wborder.sizeH
        wborder.sizeV: itemIconBorder.wborder.sizeV
        wborder.btop: true
        wborder.bright: true
        wborder.bbottom: true
        width: height
        visible: iconRightSource !== "" && iconRightVisible
        onIconClicked: /* emit */ itemIconBorder.rightChoosed()
    }

    WIconButton {
        id: iconRight_2
        z: 1
        anchors.right: iconRight.visible ? iconRight.left : parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        wborder.sizeH: itemIconBorder.wborder.sizeH
        wborder.sizeV: itemIconBorder.wborder.sizeV
        wborder.btop: true
        wborder.bright: true
        wborder.bbottom: true
        width: height
        visible: iconRight2Source !== "" && iconRight2Visible
        onIconClicked: /* emit */ itemIconBorder.right2Choosed()
    }

    WItem {
        anchors.left: iconLeft.visible ? iconLeft_.right : parent.left
        anchors.right: iconRight2.visible ? iconRight2.left : iconRight.visible ? iconRight.left : parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        wborder.sizeH: itemIconBorder.wborder.sizeH
        wborder.sizeV: itemIconBorder.wborder.sizeV
        wborder.btop: true
        wborder.bleft: true
        wborder.bbottom: true
        wborder.bright: true

        Item {
            id: contentItem
            anchors.fill: parent
        }
    }
}
