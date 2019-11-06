import QtQuick 2.0

WPage {
    id: additionalWindow
    header.iconLeftVisible: false
    header.iconLeftSource: ""
    header.iconRightVisible: true
    header.iconRightSource: "x_mark"

    signal close()

    header.onRightChoosed: /* emit */ close()
}
