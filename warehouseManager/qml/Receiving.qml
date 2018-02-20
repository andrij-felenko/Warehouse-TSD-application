import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"

StackView {
    id: receivingStack
    initialItem: receivingDocumentList
    property var parentItem: parent

    WPage {
        id: receivingDocumentList
        parentItem: receivingStack.parentItem
        backMode: true
        onBack: mainStack.pop()
        onSetting: mainPage.currentIndex = 1
        title: "Приемка"
        subTitle: "список документов"
    }
}


