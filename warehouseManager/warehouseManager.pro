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
    cpp/whmodel.h \
    cpp/testhandler.h

SOURCES += \
    cpp/main.cpp \
    cpp/whmodel.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../warehouseBase/release/ -lwarehouseBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../warehouseBase/debug/ -lwarehouseBase
else:unix: LIBS += -L$$OUT_PWD/../warehouseBase/ -lwarehouseBase

INCLUDEPATH += $$PWD/../warehouseBase/cpp
DEPENDPATH  += $$PWD/../warehouseBase/cpp

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../lib/arm/libssl.so \
        $$PWD/../lib/arm/libcrypto.so
}
