import QtQuick 2.9

WRectangle {
    id: itemIconBorder

    property int marginH: 2
    property int marginV: 2
    property bool iconLeftVisible:  false
    property bool iconRightVisible: false
    property bool hideSymbol: false
    property alias iconLeftSource: iconLeft_.iconSource
    property alias iconRightSource: iconRight_.iconSource
    property alias iconLeft:  iconLeft_
    property alias iconRight: iconRight_
    property alias content: contentItem.children
    property int contentBorder: contentItem.height / 8
    readonly property int contentBorderDefault: contentItem.height / 8
    border.color: "#AAAAAA"
    border.width: 2

    signal leftChoosed()
    signal rightChoosed()

    WIconButton {
        id: iconLeft_
        z: 1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
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
        width: height
        visible: iconRightSource !== "" && iconRightVisible
        onIconClicked: /* emit */ itemIconBorder.rightChoosed()
    }

    WRectangle {
        anchors.left:  iconLeftSource  === "" ? parent.left  : iconLeft_.right
        anchors.right: iconRightSource === "" ? parent.right : iconRight_.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        color: "#CCCCCC"

        Item {
            id: contentItem
            anchors.fill: parent
            anchors.leftMargin:  contentBorder
            anchors.rightMargin: contentBorder
        }
    }
}
