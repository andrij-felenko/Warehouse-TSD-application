import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/wcomponent"

StackView {
    id: stack
    initialItem: rect
    visible: currentItem !== rect

    WItem { id: rect }
}
