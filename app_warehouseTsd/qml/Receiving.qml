import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"
import WUrlEnum 1.0
import WJsonEnum 1.0

StackView {
    id: receivingStack
    initialItem: receivingDocumentList
    property var parentItem: parent

    Component.onCompleted: {
        WDocList.requestDocumentList(WUrlEnum.Receiving)
        Model.documentList(WUrlEnum.Receiving, true)
        receivingDocumentList.model = WModel.getModel("ReceivingDocumentList")
    }
    Component.onDestruction: Model.documentList(WUrlEnum.Receiving, false)

    // список документов приемки
    WDocumentList {
        id: receivingDocumentList
        backMode: true
        subTitle: "список документов"
        title: "Приемка"
        documentKey: WUrlEnum.Receiving
        header.onRight2Choosed: WDocList.requestDocumentList(WUrlEnum.Receiving)

        header.onRightChoosed: mainPage.currentIndex = 1 // FIXME
        onBack: mainStack.pop()
        onOpenDocument: mainStack.push(receivingContainerList)
    }

    Component {
        id: receivingContainerList
        ReceivingContainerList {  }
    }
}


