import QtQuick 2.9
import QtQuick.Layouts 1.3

WRectangle {
    id: msg
    opacity: 0.95
    visible: msgText.text !== ""

    readonly property alias text: msgText.text
    
    WText {
        id: msgText
        anchors.fill: parent
        anchors.leftMargin:  parent.width / 10
        anchors.rightMargin: parent.width / 10
        textItem.verticalAlignment: Text.AlignVCenter
        textItem.horizontalAlignment: Text.AlignHCenter
        textItem.font.pointSize: height / 40
        textItem.wrapMode: Text.WordWrap
        text: WMessage.current.text
    }
    
    clickMode: true
    onClicked: WMessage.removeMessage()
}
