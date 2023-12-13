#include <QString>
#include <QDate>
#include <QTime>
#include "NewWindow.h"
#include "../RoomRes.h"
#include "../TableRes.h"
#include "../BeachRes.h"

NewWindow::NewWindow(Data *_data, QString &_activity, QWidget *parent) : QDialog(parent), data(_data), mainLayout(new QVBoxLayout(this)), fieldsLayout(new QGridLayout), activity(_activity) {
    if (activity == "hotel")
        setWindowTitle("New Hotel reservation");
    else if (activity == "restaurant")
        setWindowTitle("New Restaurant reservation");
    else if (activity == "beach")
        setWindowTitle("New Beach reservation");

    cancel = new QPushButton("Cancel");
    confirm = new QPushButton("Confirm");
    connect(cancel, &QPushButton::clicked,this, &NewWindow::close);
    connect(confirm, &QPushButton::clicked,this, &NewWindow::addReservation);

    buttons = new QDialogButtonBox(Qt::Horizontal);
    buttons->addButton(cancel, QDialogButtonBox::RejectRole);
    buttons->addButton(confirm, QDialogButtonBox::AcceptRole);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);
}

void NewWindow::showWindow() {
    if (activity == "hotel")
        showHotel();
    else if (activity == "restaurant")
        showRestaurant();
    else if (activity == "beach")
        showBeach();
}

void NewWindow::showBasicInfo() {
    QLabel *surnameLabel = new QLabel("Surname:");
    QLabel *nameLabel = new QLabel("Name:");
    QLabel *phoneLabel = new QLabel("Phone:");
    QLabel *emailLabel = new QLabel("E-Mail:");
    QLabel *notesLabel = new QLabel("Notes:");
    surnameLine = new QLineEdit();
    nameLine = new QLineEdit();
    phoneLine = new QLineEdit();
    emailLine = new QLineEdit();
    notesLine = new QLineEdit();
    labels.append(surnameLabel);
    labels.append(nameLabel);
    labels.append(phoneLabel);
    labels.append(emailLabel);
    labels.append(notesLabel);
    surnameLabel->setBuddy(surnameLine);
    nameLabel->setBuddy(nameLine);
    phoneLabel->setBuddy(phoneLine);
    emailLabel->setBuddy(emailLine);
    notesLabel->setBuddy(notesLine);
    fieldsLayout->addWidget(surnameLabel, 0, 0);
    fieldsLayout->addWidget(surnameLine, 0, 1);
    fieldsLayout->addWidget(nameLabel, 1, 0);
    fieldsLayout->addWidget(nameLine, 1, 1);
    fieldsLayout->addWidget(phoneLabel, 2, 0);
    fieldsLayout->addWidget(phoneLine, 2, 1);
    fieldsLayout->addWidget(emailLabel, 3, 0);
    fieldsLayout->addWidget(emailLine, 3, 1);
    fieldsLayout->addWidget(notesLabel, 4, 0);
    fieldsLayout->addWidget(notesLine, 4, 1);
}

void NewWindow::showHotel() {
    showBasicInfo();
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
    guestsLine->setValue(2);
    basis = new QComboBox;
    basis->insertItem(0, "Only breakfast");
    basis->insertItem(1, "Half basis");
    basis->insertItem(2, "Full basis");
    basis->setEditable(false);
    basis->setCurrentIndex(0);
    arrDateLine = new QDateEdit(QDate::currentDate());
    arrDateLine->setDisplayFormat("dd/MM/yy");
    depDateLine = new QDateEdit(QDate::currentDate().addDays(1));
    depDateLine->setDisplayFormat("dd/MM/yy");
    labels.append(roomLabel);
    labels.append(roomBasisLabel);
    labels.append(arrDateLabel);
    labels.append(depDateLabel);
    basis->setCurrentIndex(0);
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

void NewWindow::showRestaurant() {
    showBasicInfo();
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
    guestsLine->setValue(2);
    dateLine = new QDateEdit(QDate::currentDate());
    dateLine->setDisplayFormat("dd/MM/yy");
    timeLine = new QTimeEdit(QTime::currentTime());
    timeLine->setDisplayFormat("hh:mm");
    allergiesLine = new QLineEdit();
    labels.append(tableLabel);
    labels.append(guestsLabel);
    labels.append(dateLabel);
    labels.append(timeLabel);
    labels.append(allergiesLabel);
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

void NewWindow::showBeach() {
    showBasicInfo();
    QLabel *umbrellaLabel = new QLabel("Umbrella:");
    QLabel *sunbedsLabel = new QLabel("Sunbeds:");
    QLabel *arrDateLabel = new QLabel("Arrival date:");
    QLabel *depDateLabel = new QLabel("Departure date:");
    umbrellaLine = new QLineEdit();
    sunbedsLine = new QDoubleSpinBox();
    sunbedsLine->setDecimals(0);
    sunbedsLine->setMinimum(1);
    sunbedsLine->setMaximum(4);
    sunbedsLine->setValue(0);
    arrDateLine = new QDateEdit(QDate::currentDate());
    arrDateLine->setDisplayFormat("dd/MM/yy");
    depDateLine = new QDateEdit(QDate::currentDate());
    depDateLine->setDisplayFormat("dd/MM/yy");
    labels.append(umbrellaLabel);
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

void NewWindow::addReservation() {
    if (activity == "hotel") {
        QDate arrDate = arrDateLine->date(), depDate = depDateLine->date();
        int intBasis = basis->currentIndex();
        data->addReservation(new RoomRes(
                                 surnameLine->displayText().toStdString(),
                                 nameLine->displayText().toStdString(),
                                 phoneLine->displayText().toStdString(),
                                 emailLine->displayText().toStdString(),
                                 guestsLine->value(),
                                 arrDate.year(),
                                 arrDate.month(),
                                 arrDate.day(),
                                 depDate.year(),
                                 depDate.month(),
                                 depDate.day(),
                                 static_cast<Basis>(intBasis),
                                 notesLine->displayText().toStdString(),
                                 roomLine->displayText().toStdString()));
    }
    else if (activity == "restaurant") {
        QDate date = dateLine->date();
        QTime time = timeLine->time();
        data->addReservation(new TableRes(
                                 surnameLine->displayText().toStdString(),
                                 nameLine->displayText().toStdString(),
                                 phoneLine->displayText().toStdString(),
                                 emailLine->displayText().toStdString(),
                                 guestsLine->value(),
                                 date.year(),
                                 date.month(),
                                 date.day(),
                                 time.hour(),
                                 time.minute(),
                                 notesLine->displayText().toStdString(),
                                 allergiesLine->displayText().toStdString(),
                                 tableLine->displayText().toStdString()));
    }
    else if (activity == "beach") {
        QDate arrDate = arrDateLine->date(), depDate = depDateLine->date();
        data->addReservation(new BeachRes(
                                 surnameLine->displayText().toStdString(),
                                 nameLine->displayText().toStdString(),
                                 phoneLine->displayText().toStdString(),
                                 emailLine->displayText().toStdString(),
                                 arrDate.year(),
                                 arrDate.month(),
                                 arrDate.day(),
                                 depDate.year(),
                                 depDate.month(),
                                 depDate.day(),
                                 notesLine->displayText().toStdString(),
                                 sunbedsLine->value(),
                                 umbrellaLine->displayText().toStdString()));
    }

    QWidget::close();
}
