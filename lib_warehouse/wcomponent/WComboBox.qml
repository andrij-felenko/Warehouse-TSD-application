import QtQuick 2.0

WItemIconBorder {
    id: combobox
    iconRightVisible: true
    iconRightSource: "arrow_down_204"
    iconRight.wborder.sizeH: 0
    iconRight.wborder.sizeV: 0

    property string current_id: ""
    property alias current_text: text.text
    onRightChoosed: /* emit */ openList()

    signal openList()

    content: WText {
        id: text
        anchors.fill: parent
        clickMode: true
        onClicked: /* emit */ combobox.openList()
    }
}
