import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrl 1.0
import WDocument 1.0
import WEnum 1.0

WPage {
    id: documentList

    property alias model: documentListView.model

    content: WRectangle {
        id: rectChooseDocumentList
        anchors.fill: parent
        color: documentList.color
        
        ListView {
            id: documentListView
            anchors.fill: parent
            clip: true
            spacing: 3
            model: null
            
            delegate: WDocumentHeader {
                clickMode: true
                width: parent.width
                heightItem: documentList.height / 18
            }
        }
    }
}
