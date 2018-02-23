import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrl 1.0
import WDocument 1.0

WPage {
    id: receivingDocumentList
    onBack: {
        Model.documentList(WUrl.Receiving, false)
        mainStack.pop()
    }
    onSetting: mainPage.currentIndex = 1
    content: WRectangle {
        id: rectChooseReceivingDocumentList
        anchors.fill: parent
        color: receivingDocumentList.color
        
        ListView {
            id: receivingDocumentListView
            clip: true
            anchors.fill: parent
            spacing: 3
            
            delegate: WRectangle{
                property WHeader item: m_item

                WMirrorLabel {
                    color: "#BBCCDD"
                    height: rectChooseReceivingDocumentList.height / 13
                    width: parent.width
                    textLeft: item === null ? "" : item.name
                    clickMode: true
                    onClicked: {}
                }
            }
            model: WModel.getModel("ReceivingDocumentList")
        }
    }
}
