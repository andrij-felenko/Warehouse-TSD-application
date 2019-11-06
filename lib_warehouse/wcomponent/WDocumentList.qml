import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WDocument 1.0
import WEnum 1.0
import WUrlEnum 1.0
import WJsonEnum 1.0

WPage {
    id: documentList
    header.iconRight2Visible: true
    header.iconRight2Source: "sinchronize"
    header.iconRightVisible: true
    header.iconRightSource: "settings_3"

    property alias model: documentListView.model
    property alias addDocumentMode: addDocumentItem.visible
    property int documentKey: WUrlEnum.___

    signal openSetting()
    signal openDocument(string id)

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

                onClicked: WServer.request([WUrlEnum.Get, documentKey, WUrlEnum.Document], WUrl.versionToInt(),
                                           qsTr("Загрузка строк документа"),
                                           WRequestor.tuple(WJsonEnum.Document_id, item.id),
                                           WEnum.Request_must_server, private_, "getDocumentAnswer")
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

    Item {
        id: private_
         function getDocumentAnswer(answer, id){
             if (answer)
                 /* emit */ documentList.openDocument(id)
         }
    }
}
