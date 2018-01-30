import QtQuick 2.9

WRectangle {
    id: textInput

    property int marginH: 2
    property int marginV: 2
    property bool iconLeftVisible:  false
    property bool iconRightVisible: false
    property alias iconLeftSource: iconLeft_.iconSource
    property alias iconRightSource: iconRight_.iconSource
    property alias iconLeft:  iconLeft_
    property alias iconRight: iconRight_
    property alias input: textInput_

    signal leftChoose()
    signal rightChoose()

    WIconButton {
        id: iconLeft_
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: height
        visible: iconLeftSource !== "" && iconLeftVisible
    }

    WIconButton {
        id: iconRight_
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: height
        visible: iconRightSource !== "" && iconRightVisible
    }

    WRectangle {
        anchors.left:  iconLeftSource  === "" ? parent.left  : iconLeft_.right
        anchors.right: iconRightSource === "" ? parent.right : iconRight_.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        TextInput {
            id: textInput_
            anchors.fill: parent
            font.pixelSize: height / 3
            verticalAlignment: Text.AlignVCenter
            clip: true
        }
    }
}
