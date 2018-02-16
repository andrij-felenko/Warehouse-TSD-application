import QtQuick 2.9
import "qrc:/wcomponent"

WPage {
    backMode: true
    onBack: mainPage.currentIndex = 0
    title: "Настройки"
}
