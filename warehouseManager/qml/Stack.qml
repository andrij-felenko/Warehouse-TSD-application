import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"

StackView {
    id: mainStack
    initialItem: auth

    Auth {
        id: auth
        onAuthorization: if (User.tryAuthorization(password))
                             mainStack.push(menu)
        onSetting: mainPage.currentIndex = 1
    }

    Component {
        id: menu
        MenuWindow { parentItem: mainStack }
    }
}
