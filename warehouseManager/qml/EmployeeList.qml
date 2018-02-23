import QtQuick 2.9
import "qrc:/wcomponent"
import WEnum 1.0

Component {
    id: comboBoxListComponent
    
    WAdditionalWindow {
        id: additionalEmployeeList
        title: "Выбор пользователя"
        onClose: {
            comboBoxAuth.current_text = WUser.current.name
            Model.employeeList(false)
            additional.pop()
        }
        parentItem: additional
        
        content: WRectangle {
            id: rectChooseEmployee
            anchors.fill: parent
            
            ListView {
                clip: true
                anchors.fill: parent
                spacing: 3
                
                delegate: WMirrorLabel {
                    color: WUser.current.name === m_item.name ? "#999999" : "#CCCCCC"
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
}
