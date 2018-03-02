import QtQuick 2.9
import "qrc:/wcomponent"

WPage {
    id: containerList
    title: qsTr("Приемка")
    subTitle: qsTr("Контейнера")
    backMode: true

    Component.onCompleted:   Model.cacheDocList("receiving", true, id, WJsonEnum.Container_receiver_id)
    Component.onDestruction: Model.cacheDocList("receiving", false)

    onBack: mainStack.pop()

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
                textRight: m_actual + m_plan !== 0 ? " / " + m_plan : ""
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
