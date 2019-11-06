import QtQuick 2.9
import "qrc:/wcomponent"

WPage {
    backMode: true
    onBack: mainStack.pop()
    header.onRightChoosed: mainPage.currentIndex = 1
    title: "Перемещение"
}
