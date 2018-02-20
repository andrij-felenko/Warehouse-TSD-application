import QtQuick 2.0

WRectangle {
    id: mirrorLabel
    visible: visibleWithEmptyProperties ? true
                                        : textLeft  === undefined || textRight === undefined ? false
                                                                                             : true

    property alias textLeft:   left.text
    property alias textRight: right.text

    property int textSpacing: 5
    property int textMargin: 5
    property bool visibleWithEmptyProperties: true
    property string colorBackground: ""
    property string colorTextLeft: ""
    property string colorTextRight: ""

    onHeightChanged: _private.reHeight()
    onWidthChanged:  _private.reWidth()

    WText {
        id: left
        anchors.fill: parent
        textItem.verticalAlignment: Text.AlignVCenter

        onTextChanged: _private.reSize()
    }

    WText {
        id: right
        anchors.fill: parent
        textItem.horizontalAlignment: Text.AlignRight
        textItem.verticalAlignment: Text.AlignVCenter

        onTextChanged: _private.reSize()
    }

    Item {
        id: _private

        function reSize(){
            reHeight()
            reWidth()
        }

        function reHeight(){
            left.height = mirrorLabel.height
            right.height = mirrorLabel.height
        }

        function reWidth(){
            left.width = (mirrorLabel.height - textSpacing) / 2
            right.width = (mirrorLabel.height - textSpacing) / 2
        }
    }
}
