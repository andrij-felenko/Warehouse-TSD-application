import QtQuick 2.9
import "qrc:/wcomponent"

WPage {
    backMode: true
    onBack: mainStack.pop()
    onSetting: mainPage.currentIndex = 1
    title: "Приемка"
}
