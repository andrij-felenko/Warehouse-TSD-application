import QtQuick 2.9
import "qrc:/wcomponent"
import WEnum 1.0

WAdditionalWindow {
    id: additionalEmployeeList
    title: "Выбор пользователя"
    onClose: {
        comboBoxAuth.current_text = WUser.current.name
        Model.employeeList(false)
        additional.pop()
    }

    content: WRectangle {
        id: rectChooseEmployee
        anchors.fill: parent
        color: "#504d4a"
        
        ListView {
            clip: true
            anchors.fill: parent
            spacing: 3
            
            delegate: WMirrorLabel {
                color: WUser.current.name === m_item.name ? "#00C97C" : "#CCCCCC"
                height: rectChooseEmployee.height / 13
                width: parent.width
                textLeft: m_item.name
                clickMode: true
                onClicked: {
                    WUser.setUserList(m_item.id)
                    password_input.text = ""
                    additionalEmployeeList.close()
                }
            }
            model: WModel.getModel("employeeList")
        }
    }
}
