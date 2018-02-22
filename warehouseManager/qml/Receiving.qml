import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrl 1.0

StackView {
    id: receivingStack
    initialItem: receivingDocumentList
    property var parentItem: parent

    // список документов приемки
    ReceivingDocumentList {
        id: receivingDocumentList
        backMode: true
        parentItem: receivingStack.parentItem
        subTitle: "список документов"
        title: "Приемка"
    }
}


