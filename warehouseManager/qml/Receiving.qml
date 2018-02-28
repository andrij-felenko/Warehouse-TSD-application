import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrlEnum 1.0

StackView {
    id: receivingStack
    initialItem: receivingDocumentList
    property var parentItem: parent

    // список документов приемки
    WDocumentList {
        id: receivingDocumentList
        backMode: true
        subTitle: "список документов"
        title: "Приемка"
        documentKey: WUrlEnum.Receiving
        model: WModel.getModel("ReceivingDocumentList")
        header.onRight2Choosed: WDocList.requestDocumentList(WUrlEnum.Receiving)

        header.onRightChoosed: mainPage.currentIndex = 1 // FIXME
        onBack: {
            Model.documentList(WUrlEnum.Receiving, false)
            mainStack.pop()
        }
        onOpenDocument: console.log("open document") // FIXME
    }
}


