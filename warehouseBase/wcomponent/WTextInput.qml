import QtQuick 2.9

WItemIconBorder {
    id: textInput

    property alias input: textInput_
    property alias text: textInput_.text

    signal accepted()

    content: TextInput {
        id: textInput_
        anchors.fill: parent
        font.pixelSize: height * 0.4
        verticalAlignment: Text.AlignVCenter
        clip: true
        onAccepted: /* emit */ textInput.accepted()
        echoMode: textInput.hideSymbol ? TextInput.Password : TextInput.Normal
    }
}
