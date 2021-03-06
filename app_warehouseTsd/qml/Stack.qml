import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"

StackView {
    id: mainStack
    initialItem: auth

    Auth {
        id: auth
        onAuthorization: if (WUser.tryAuthorization(password))
                             mainStack.push(menu)
        header.onRightChoosed: mainPage.currentIndex = 1
    }

    Component {
        id: menu
        MenuWindow {  }
    }
}
