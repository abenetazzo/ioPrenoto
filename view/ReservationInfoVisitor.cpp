#include "ReservationInfoVisitor.h"
#include <QLabel>
#include <QString>
#include "../BeachRes.h"
#include "../RoomRes.h"
#include "../TableRes.h"

ReservationInfoVisitor::ReservationInfoVisitor(QWidget *_widget, QGridLayout *_fieldsLayout) : widget(_widget), fieldsLayout(_fieldsLayout) {}

void ReservationInfoVisitor::visitBeachRes(BeachRes *beachRes) {
    widget->setWindowTitle("Edit Beach reservation");
    QLabel *umbrellaLabel = new QLabel("Umbrella:");
    QLabel *sunbedsLabel = new QLabel("Sunbeds:");
    QLabel *arrDateLabel = new QLabel("Arrival date:");
    QLabel *depDateLabel = new QLabel("Departure date:");
    umbrellaLine = new QLineEdit();
    sunbedsLine = new QDoubleSpinBox();
    sunbedsLine->setDecimals(0);
    sunbedsLine->setMinimum(1);
    sunbedsLine->setMaximum(4);
    arrDateLine = new QDateEdit(QDate::currentDate());
    depDateLine = new QDateEdit(QDate::currentDate());
    arrDateLine->setDisplayFormat("dd/MM/yy");
    depDateLine->setDisplayFormat("dd/MM/yy");
    umbrellaLine->setText(QString::fromStdString(beachRes->getReservable()));
    sunbedsLine->setValue(beachRes->getSunbeds());
    QDate arrDate(beachRes->getArrDateY(), beachRes->getArrDateM(), beachRes->getArrDateD()), depDate(beachRes->getDepDateY(), beachRes->getDepDateM(), beachRes->getDepDateD());;
    arrDateLine->setDate(arrDate);
    depDateLine->setDate(depDate);
    umbrellaLabel->setBuddy(umbrellaLine);
    sunbedsLabel->setBuddy(sunbedsLine);
    arrDateLabel->setBuddy(arrDateLine);
    depDateLabel->setBuddy(depDateLine);
    fieldsLayout->addWidget(umbrellaLabel, 5, 0);
    fieldsLayout->addWidget(umbrellaLine, 5, 1);
    fieldsLayout->addWidget(sunbedsLabel, 6, 0);
    fieldsLayout->addWidget(sunbedsLine, 6, 1);
    fieldsLayout->addWidget(arrDateLabel, 7, 0);
    fieldsLayout->addWidget(arrDateLine, 7, 1);
    fieldsLayout->addWidget(depDateLabel, 8, 0);
    fieldsLayout->addWidget(depDateLine, 8, 1);
}

void ReservationInfoVisitor::visitRoomRes(RoomRes *roomRes) {
    widget->setWindowTitle("Edit Hotel reservation");
    QLabel *roomLabel = new QLabel("Room:");
    QLabel *guestsLabel = new QLabel("Guests:");
    QLabel *roomBasisLabel = new QLabel("Room Basis:");
    QLabel *arrDateLabel = new QLabel("Arrival date:");
    QLabel *depDateLabel = new QLabel("Departure date:");
    roomLine = new QLineEdit();
    guestsLine = new QDoubleSpinBox();
    guestsLine->setDecimals(0);
    guestsLine->setMinimum(1);
    guestsLine->setMaximum(99);
    basis = new QComboBox;
    basis->insertItem(0, "Only breakfast");
    basis->insertItem(1, "Half basis");
    basis->insertItem(2, "Full basis");
    basis->setEditable(false);
    basis->setCurrentIndex(0);
    arrDateLine = new QDateEdit(QDate::currentDate());
    depDateLine = new QDateEdit(QDate::currentDate().addDays(1));
    arrDateLine->setDisplayFormat("dd/MM/yy");
    depDateLine->setDisplayFormat("dd/MM/yy");
    roomLine->setText(QString::fromStdString(roomRes->getReservable()));
    guestsLine->setValue(roomRes->getGuests());
    if (roomRes->getBasis() == 0)
        basis->setCurrentIndex(0);
    else if (roomRes->getBasis() == 1)
        basis->setCurrentIndex(1);
    else if (roomRes->getBasis() == 2)
        basis->setCurrentIndex(2);
    QDate arrDate(roomRes->getArrDateY(), roomRes->getArrDateM(), roomRes->getArrDateD()), depDate(roomRes->getDepDateY(), roomRes->getDepDateM(), roomRes->getDepDateD());;
    arrDateLine->setDate(arrDate);
    depDateLine->setDate(depDate);
    roomLabel->setBuddy(roomLine);
    guestsLabel->setBuddy(guestsLine);
    roomBasisLabel->setBuddy(basis);
    arrDateLabel->setBuddy(arrDateLine);
    depDateLabel->setBuddy(depDateLine);
    fieldsLayout->addWidget(roomLabel, 5, 0);
    fieldsLayout->addWidget(roomLine, 5, 1);
    fieldsLayout->addWidget(guestsLabel, 6, 0);
    fieldsLayout->addWidget(guestsLine, 6, 1);
    fieldsLayout->addWidget(roomBasisLabel, 7, 0);
    fieldsLayout->addWidget(basis, 7, 1);
    fieldsLayout->addWidget(arrDateLabel, 8, 0);
    fieldsLayout->addWidget(arrDateLine, 8, 1);
    fieldsLayout->addWidget(depDateLabel, 9, 0);
    fieldsLayout->addWidget(depDateLine, 9, 1);
}

void ReservationInfoVisitor::visitTableRes(TableRes *tableRes) {
    widget->setWindowTitle("Edit Restaurant reservation");
    QLabel *tableLabel = new QLabel("Table:");
    QLabel *guestsLabel = new QLabel("Guests:");
    QLabel *dateLabel = new QLabel("Date:");
    QLabel *timeLabel = new QLabel("Time:");
    QLabel *allergiesLabel = new QLabel("Allergies:");
    tableLine = new QLineEdit();
    guestsLine = new QDoubleSpinBox();
    guestsLine->setDecimals(0);
    guestsLine->setMinimum(1);
    guestsLine->setMaximum(99);
    dateLine = new QDateEdit(QDate::currentDate());
    dateLine->setDisplayFormat("dd/MM/yy");
    timeLine = new QTimeEdit();
    timeLine->setDisplayFormat("hh:mm");
    allergiesLine = new QLineEdit();
    tableLine->setText(QString::fromStdString(tableRes->getReservable()));
    guestsLine->setValue(tableRes->getGuests());
    QDate date(tableRes->getDateY(), tableRes->getDateM(), tableRes->getDateD());
    dateLine->setDate(date);
    QTime time(tableRes->getTimeH(), tableRes->getTimeM());
    timeLine->setTime(time);
    allergiesLine->setText(QString::fromStdString(tableRes->getAllergies()));
    tableLabel->setBuddy(tableLine);
    guestsLabel->setBuddy(guestsLine);
    dateLabel->setBuddy(dateLine);
    timeLabel->setBuddy(timeLine);
    allergiesLabel->setBuddy(allergiesLine);
    fieldsLayout->addWidget(tableLabel, 5, 0);
    fieldsLayout->addWidget(tableLine, 5, 1);
    fieldsLayout->addWidget(guestsLabel, 6, 0);
    fieldsLayout->addWidget(guestsLine, 6, 1);
    fieldsLayout->addWidget(dateLabel, 7, 0);
    fieldsLayout->addWidget(dateLine, 7, 1);
    fieldsLayout->addWidget(timeLabel, 8, 0);
    fieldsLayout->addWidget(timeLine, 8, 1);
    fieldsLayout->addWidget(allergiesLabel, 9, 0);
    fieldsLayout->addWidget(allergiesLine, 9, 1);
}

void ReservationInfoVisitor::saveBeachRes(BeachRes *beachRes) {
    beachRes->park(umbrellaLine->displayText().toStdString());
    beachRes->setSunbeds(sunbedsLine->value());
    QDate arrDate = arrDateLine->date(), depDate = depDateLine->date();
    beachRes->setArrDate(arrDate.year(), arrDate.month(), arrDate.day());
    beachRes->setDepDate(depDate.year(), depDate.month(), depDate.day());
}

void ReservationInfoVisitor::saveRoomRes(RoomRes *roomRes) {
    roomRes->park(roomLine->displayText().toStdString());
    roomRes->setGuests(guestsLine->value());
    int intBasis = basis->currentIndex();
    roomRes->setBasis(static_cast<Basis>(intBasis));
    QDate arrDate = arrDateLine->date(), depDate = depDateLine->date();
    roomRes->setArrDate(arrDate.year(), arrDate.month(), arrDate.day());
    roomRes->setDepDate(depDate.year(), depDate.month(), depDate.day());
}

void ReservationInfoVisitor::saveTableRes(TableRes *tableRes) {
    tableRes->park(tableLine->displayText().toStdString());
    tableRes->setGuests(guestsLine->value());
    QDate date = dateLine->date();
    tableRes->setDate(date.year(), date.month(), date.day());
    QTime time = timeLine->time();
    tableRes->setTime(time.hour(), time.minute());
    tableRes->setAllergies(allergiesLine->displayText().toStdString());
}
