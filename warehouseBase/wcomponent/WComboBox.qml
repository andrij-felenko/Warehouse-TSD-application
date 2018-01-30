import QtQuick 2.0

Item {
    id: combobox
    anchors.bottom: _private.isOpen ? anchorsBottom : undefined

    property alias model: value
    property alias title: itemTitle.children

    property int itemHeight: 30
    property string current: ""
    property string colorText: ""
    property string colorTextChoose: ""
    property string colorBackground: ""
    property string colorBackgroundChoose: ""
    property var anchorsBottom: parent.bottom

    signal choose(string name)

    onChoose: current = name

    Item {
        id: itemTitle
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: itemHeight
    }

    FRectangle {
        id: itemList
        anchors.top: itemTitle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: combobox.bottom
        visible: _private.isOpen

        ListView {
            id: listView
            anchors.fill: parent

            delegate: FMirrorLabel {
                textLeft: name
                height: itemHeight
                anchors.left: parent.left
                anchors.right: parent.right
                clickMode: true

                onClicked: /* emit */ combobox.choose()
            }
        }
    }

    Item {
        id: _private
        property bool isOpen: false
    }
}
