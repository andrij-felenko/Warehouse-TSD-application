QT += core
QT += gui
QT += network
QT += qml
QT += quick
QT -= widgets

CONFIG += c++14
TARGET  = "Warehouse manager"

RESOURCES += \
    resource_images.qrc \
    resource_qml.qrc

OTHER_FILES += $$PWD/qml/*.qml

DEPENDPATH  += $$PWD/cpp
INCLUDEPATH += $$PWD/cpp

HEADERS += \

SOURCES += \
    cpp/main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../warehouseBase/release/ -lwarehouseBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../warehouseBase/debug/ -lwarehouseBase
else:unix: LIBS += -L$$OUT_PWD/../warehouseBase/ -lwarehouseBase

INCLUDEPATH += $$PWD/../warehouseBase/cpp
DEPENDPATH  += $$PWD/../warehouseBase/cpp
