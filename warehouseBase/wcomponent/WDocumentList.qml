import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrl 1.0
import WDocument 1.0
import WEnum 1.0

WPage {
    id: documentList
    header.iconRight2Visible: true
    header.iconRight2Source: "sinchronize"
    header.iconRightVisible: true
    header.iconRightSource: "settings_3"

    property alias model: documentListView.model
    property alias addDocumentMode: addDocumentItem.visible

    signal openSetting()

    header.onRightChoosed: /* emit */ documentList.openSetting()

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

        WCircleIcon {
            id: addDocumentItem
            border.color: "#003319"
            visible: false
            color: "#FFFFFF"
            iconSource: "plus_8"
            opacity: 0.8
        }
    }
}
