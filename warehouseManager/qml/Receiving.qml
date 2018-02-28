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
        subTitle: "список документов"
        title: "Приемка"
        model: WModel.getModel("ReceivingDocumentList")
        header.onRight2Choosed: WDocList.requestDocumentList(WUrl.Receiving)

        onBack: {
            Model.documentList(WUrl.Receiving, false)
            mainStack.pop()
        }
        header.onRightChoosed: mainPage.currentIndex = 1
    }
}


