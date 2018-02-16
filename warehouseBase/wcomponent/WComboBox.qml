import QtQuick 2.0

WItemIconBorder {
    id: combobox
    iconRightVisible: true
    iconRightSource: "arrow_down_204"

    property string current_id: ""
    property alias current_text: text.text
    onRightChoosed: /* emit */ openList()

    signal openList()

    content: WText {
        id: text
    }
}
