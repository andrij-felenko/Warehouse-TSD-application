import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrl 1.0

StackView {
    id: receivingStack
    initialItem: receivingDocumentList
    property var parentItem: parent

    // список документов приемки
    WDocumentList {
        id: receivingDocumentList
        backMode: true
        parentItem: receivingStack.parentItem
        subTitle: "список документов"
        title: "Приемка"
        model: WModel.getModel("ReceivingDocumentList")

        onBack: {
            Model.documentList(WUrl.Receiving, false)
            mainStack.pop()
        }
        onSetting: mainPage.currentIndex = 1
    }
}


