import QtQuick 2.9
import "qrc:/wcomponent"
import QtQuick.Layouts 1.3

WRectangle {
    id: msg
    opacity: 0.9
    visible: WMsg.current.text !== ""
    
    WText {
        id: msgText
        anchors.fill: parent
        textItem.verticalAlignment: Text.AlignVCenter
        textItem.horizontalAlignment: Text.AlignHCenter
        textItem.font.pointSize: height / 30
        text: WMsg.current.text
    }
    
    clickMode: true
    onClicked: WMsg.removeMessage()
}
