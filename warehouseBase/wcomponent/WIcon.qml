import QtQuick 2.0
import Qt.labs.settings 1.0
import QtGraphicalEffects 1.0

Item {
    id: icon
    property alias color: colorOverlay.color
    property string source: ""
    property int percent : 60
    visible: source !== ""

    Image {
        id: image
        property string iconDir: "/icon/"
        source: icon.source === "" ? Qt.resolvedUrl(null)
                                   : Qt.resolvedUrl(iconDir + icon.source + ".png")
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectCrop
        height: parent.height * percent / 100
        width:  parent.width  * percent / 100

        ColorOverlay {
            id: colorOverlay
            anchors.fill: image
            source: image
        }
    }

    Settings {
        id: settings
        category: "path"
        property alias iconDir: image.iconDir
    }
}
