import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrl 1.0
import WDocument 1.0
import WEnum 1.0

WRectangle {
    id: rect
    property WHeader item: m_item
    property int heightItem: 30
    
    color: {
        if (rect.item === null)
            return "#CCCCFF"
        else
            switch (rect.item.status){
            case WEnum.Document_created: "#FFCCFF"; break
            case WEnum.Document_inWorking: "#CCFFE5"; break
            case WEnum.Document_accepted: "#99FF99"; break
            case WEnum.Document_done: "#D0D0D0"; break
            default:"#CCCCFF";
            }
    }
    
    height: column.implicitHeight
    onClicked: {}
    
    Column {
        id: column
        anchors.fill: parent
        
        WText {
            height: heightItem * 0.7
            textPercent: 1.2
            width: parent.width
            textItem.horizontalAlignment: Text.AlignRight
            text: rect.item === null ? "" : WStatic.statusToString(rect.item.status)
        }
        
        WMirrorLabel {
            color: rect.color
            height: heightItem * 0.7
            width: parent.width
            textLeft: qsTr("Name")
            textRight: rect.item === null ? "" : rect.item.name
            leftItem.textPercent: 1.6
            rightItem.textPercent: 1.6
        }
        
        WMirrorLabel {
            color: rect.color
            height: heightItem * 0.7
            width: parent.width
            textLeft: qsTr("Date")
            textRight: rect.item === null ? "" : WStatic.shortDateTimeToString(rect.item.dateCreated)
            leftItem.textPercent: 1.6
            rightItem.textPercent: 1.6
        }
        
        WMirrorLabel {
            color: rect.color
            height: heightItem * 0.7
            width: parent.width
            textLeft: qsTr("Supplier")
            textRight: rect.item === null ? "" : rect.item.supplier
            leftItem.textPercent: 1.6
            rightItem.textPercent: 1.6
            visible: textRight !== ""
        }
    }
}
