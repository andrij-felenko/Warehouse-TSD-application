import QtQuick 2.9
import "qrc:/wcomponent"

WPage {
    id: containerList
    title: qsTr("Приемка")
    subTitle: qsTr("Контейнера")
    backMode: true

    onBack: {
        mainStack.pop()
        Model.cacheDocList("receiving", false)
    }

    content: WRectangle {
        anchors.fill: parent
        property var listModel: WModel.getModel("receivingCacheDocList")

        WDocumentHeader {
            id: header
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            item: parent.listModel.document()
        }

        ListView {
            clip: true
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            spacing: 3

            delegate: WMirrorLabel {
                color: "#00C97C"
                height: containerList.height / 13
                width: parent.width
                textLeft: m_item.name
                clickMode: true
                onClicked: console.log("container choose")
            }

            model: parent.listModel
        }

        WCircleIcon {
            id: addContainerItem
            border.color: "#003319"
            visible: false
            color: "#FFFFFF"
            iconSource: "plus_8"
            opacity: 0.8
        }

        color: "yellow"
    }
}
