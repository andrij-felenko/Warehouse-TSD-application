import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
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
            case WEnum.Document_created:   "#F2EADF"; break
            case WEnum.Document_inWorking: "#E5C1AD"; break
            case WEnum.Document_accepted:  "#F1F1F9"; break
            case WEnum.Document_done:      "#DBD5DE"; break
            default:"darkgray";
            }
    }
    
    height: column.implicitHeight
    
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
            textRight: rect.item === null ? "" : WStatic.fullDateToString(rect.item.dateCreated)
            leftItem.textPercent: 1.6
            rightItem.textPercent: 1.6
        }
        
        WMirrorLabel {
            color: rect.color
            height: heightItem * 0.7
            width: parent.width
            textLeft: qsTr("Supplier")
            textRight: rect.item === null ? "" : rect.item.supplierId
            leftItem.textPercent: 1.6
            rightItem.textPercent: 1.6
            visible: textRight !== ""
        }
    }
}
