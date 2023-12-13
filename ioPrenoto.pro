QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BeachRes.cpp \
    Data.cpp \
    List.cpp \
    Reservation.cpp \
    RoomRes.cpp \
    view/ReservationInfoVisitor.cpp \
    view/SearchWindow.cpp \
    TableRes.cpp \
    view/DeleteButton.cpp \
    view/EditButton.cpp \
    view/EditWindow.cpp \
    view/NewWindow.cpp \
    view/ReservationPanel.cpp \
    main.cpp \
    view/Mainwindow.cpp \
    view/UtilityPanel.cpp

HEADERS += \
    BeachRes.h \
    Data.h \
    List.h \
    ReservationVisitorInterface.h \
    RoomRes.h \
    view/ReservationInfoVisitor.h \
    view/SearchWindow.h \
    TableRes.h \
    view/DeleteButton.h \
    view/EditButton.h \
    view/EditWindow.h \
    view/NewWindow.h \
    view/ReservationPanel.h \
    Reservation.h \
    view/Mainwindow.h \
    view/UtilityPanel.h

RESOURCES += \
    assets/delete.png \
    assets/edit.png \
    assets/ioPrenoto.png \
    assets/new.png \
    assets/quit.png \
    assets/room.png \
    assets/search.png \
    assets/table.png \
    assets/umbrella.png

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target