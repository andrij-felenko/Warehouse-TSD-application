QT += core
QT += gui
QT += network
QT += qml
QT += quick
QT -= widgets

CONFIG += c++14
TARGET  = "Warehouse manager"
DESTDIR = $$PWD/..

RESOURCES += \
    resource_images.qrc \
    resource_qml.qrc

OTHER_FILES += $$PWD/qml/Acceptance/*.qml

DEPENDPATH += $$PWD/cpp
INCLUDEPATH += $$PWD/cpp

HEADERS += \
    cpp/view/view.h

SOURCES += \
    cpp/view/view.cpp \
    cpp/main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../warehouseBase/release/ -lwarehouseBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../warehouseBase/debug/ -lwarehouseBase
else:unix: LIBS += -L$$OUT_PWD/../warehouseBase/ -lwarehouseBase

INCLUDEPATH += $$PWD/../warehouseBase/cpp
DEPENDPATH += $$PWD/../warehouseBase/cpp
