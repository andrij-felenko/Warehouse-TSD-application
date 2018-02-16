import QtQuick 2.0

WRectangle {
    id: page

    property bool backMode: false
    property alias  content: item.children
    property alias    title: steppedText.title
    property alias subTitle: steppedText.subTitle
    property alias titleItem: steppedText.titleItem
    property alias subTitleItem: steppedText.subTitleItem
    property alias header: headerPage
    border.width: 0
    color: "#504d4a"

    signal back()
    signal menu()
    signal setting()

    WItemIconBorder {
        id: headerPage
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height:  parent.height / 13

        iconLeftSource: backMode ? "arrow_left_89" : "menu_4"
        iconLeftVisible: true
        iconRightSource: "settings_3"
        iconRightVisible: true

        onRightChoosed: /* emit */ page.setting()
        onLeftChoosed: page.backMode ? /* emit */ page.back() : /* emit */ page.menu()

        content: WTwoStepped {
            id: steppedText
            anchors.fill: parent
//            titleItem.textItem.color: "#4483b6"
//            subTitleItem.textItem.color: "#4483b6"
        }
    }

    WItem {
        id: item
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: headerPage.bottom
    }
}
