#include <QString>
#include <QScrollArea>
#include "ReservationPanel.h"
#include "Mainwindow.h"
#include "../BeachRes.h"
#include "../RoomRes.h"
#include "../TableRes.h"

ReservationPanel::ReservationPanel(List *_reservations, QWidget *parent) : QWidget(parent), layout(new QGridLayout), reservations(_reservations) {
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *client = new QWidget;
    client->setFixedSize((MainWindow::mainWindowWidth/3)*2, MainWindow::mainWindowHeigth);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    client->setLayout(layout);
    scrollArea->setWidget(client);

    editIcon = new QIcon(":/assets/edit.png");
    delIcon = new QIcon(":/assets/delete.png");

    headerFont = new QFont("Century Gothic", 14, QFont::Bold);
    font = new QFont("Century Gothic", 10);

    int col = 0;
    editHeader = new QLabel;
    deleteHeader = new QLabel;
    nameHeader = new QLabel;
    phoneHeader = new QLabel;
    emailHeader = new QLabel;
    notesHeader = new QLabel;
    editHeader->setFont(*headerFont);
    deleteHeader->setFont(*headerFont);
    nameHeader->setFont(*headerFont);
    phoneHeader->setFont(*headerFont);
    emailHeader->setFont(*headerFont);
    notesHeader->setFont(*headerFont);
    layout->addWidget(editHeader, 0, col++);
    layout->addWidget(deleteHeader, 0, col++);
    layout->addWidget(nameHeader, 0, col++);
    layout->addWidget(phoneHeader, 0, col++);
    layout->addWidget(emailHeader, 0, col++);
    layout->addWidget(notesHeader, 0, col);
}

void ReservationPanel::cleanLabels() {
    for (auto it = additionalLabels.begin(); it != additionalLabels.end();) {
        QLabel *additionalLabel = *it;
        layout->removeWidget(additionalLabel);
        delete additionalLabel;
        it = additionalLabels.erase(it);
    }
    for (auto it = infoReservations.begin(); it != infoReservations.end();) {
        QLabel *infoReservation = *it;
        layout->removeWidget(infoReservation);
        delete infoReservation;
        it = infoReservations.erase(it);
    }
    for (auto it = editButtons.begin(); it != editButtons.end();) {
        EditButton *button = *it;
        layout->removeWidget(button);
        delete button;
        it = editButtons.erase(it);
    }
    for (auto it = deleteButtons.begin(); it != deleteButtons.end();) {
        DeleteButton *button = *it;
        layout->removeWidget(button);
        delete button;
        it = deleteButtons.erase(it);
    }
}

void ReservationPanel::showBasicInfo(unsigned int row, unsigned int &col, Reservation *reservation) {
    EditButton *edit = new EditButton(reservation, editIcon);
    edit->setFixedSize(30, 30);
    layout->addWidget(edit, row, col++);
    DeleteButton *del = new DeleteButton(reservation, delIcon);
    del->setFixedSize(30, 30);
    layout->addWidget(del, row, col++);
    editButtons.append(edit);
    deleteButtons.append(del);

    connect(del, &DeleteButton::deletePressed, this, &ReservationPanel::signalDelete);
    connect(edit, &EditButton::editPressed, this, &ReservationPanel::signalEdit);

    QLabel *nameLabel = new QLabel(QString::fromStdString(reservation->getSurname() + " " + reservation->getName()));
    QLabel *phoneLabel = new QLabel(QString::fromStdString(reservation->getPhone()));
    QLabel *emailLabel = new QLabel(QString::fromStdString(reservation->getEmail()));
    QLabel *notesLabel = new QLabel(QString::fromStdString(reservation->getNotes()));
    QLabel *reservableLabel;
    if (reservation->isParked())
        reservableLabel = new QLabel(QString::fromStdString(reservation->getReservable()));
    else
        reservableLabel = new QLabel;
    nameLabel->setFont(*font);
    phoneLabel->setFont(*font);
    emailLabel->setFont(*font);
    notesLabel->setFont(*font);
    reservableLabel->setFont(*font);
    layout->addWidget(nameLabel, row, col++);
    layout->addWidget(phoneLabel, row, col++);
    layout->addWidget(emailLabel, row, col++);
    layout->addWidget(notesLabel, row, col++);
    layout->addWidget(reservableLabel, row, col++);
    infoReservations.append(nameLabel);
    infoReservations.append(phoneLabel);
    infoReservations.append(emailLabel);
    infoReservations.append(notesLabel);
    infoReservations.append(reservableLabel);

    layout->setRowMinimumHeight(row, 18);
}

void ReservationPanel::showHeader() {
    cleanLabels();

    editHeader->setText("Edit");
    deleteHeader->setText("Delete");
    nameHeader->setText("Name");
    phoneHeader->setText("Phone");
    emailHeader->setText("E-Mail");
    notesHeader->setText("Notes");
}

void ReservationPanel::showHotel() {
    // header
    showHeader();
    unsigned int col = 6, row = 0;
    QLabel *roomHeader = new QLabel("Room");
    QLabel *guestsHeader = new QLabel("Guests");
    QLabel *arrDateHeader = new QLabel("Arrival date");
    QLabel *depDateHeader = new QLabel("Departure date");
    QLabel *roomBasisHeader = new QLabel("Room basis");
    additionalLabels.append(roomHeader);
    additionalLabels.append(guestsHeader);
    additionalLabels.append(arrDateHeader);
    additionalLabels.append(depDateHeader);
    additionalLabels.append(roomBasisHeader);
    roomHeader->setFont(*headerFont);
    guestsHeader->setFont(*headerFont);
    arrDateHeader->setFont(*headerFont);
    depDateHeader->setFont(*headerFont);
    roomBasisHeader->setFont(*headerFont);
    layout->addWidget(roomHeader, row, col++);
    layout->addWidget(guestsHeader, row, col++);
    layout->addWidget(arrDateHeader, row, col++);
    layout->addWidget(depDateHeader, row, col++);
    layout->addWidget(roomBasisHeader, row, col++);
    layout->setRowMinimumHeight(row++, 30);

    // rows
    for (auto it = reservations->begin(); it != reservations->end(); it++) {
        RoomRes *roomRes = dynamic_cast<RoomRes*>(*it);
        if (roomRes) {
            col = 0;
            showBasicInfo(row, col, roomRes);

            QLabel *guestsLabel = new QLabel(QString::number(roomRes->getGuests()));
            QDate arrDate(roomRes->getArrDateY(), roomRes->getArrDateM(), roomRes->getArrDateD()), depDate(roomRes->getDepDateY(), roomRes->getDepDateM(), roomRes->getDepDateD());
            QLabel *arrDateLabel = new QLabel(arrDate.toString("dd/MM"));
            QLabel *depDateLabel = new QLabel(depDate.toString("dd/MM"));
            Basis basis = roomRes->getBasis();
            QLabel *roomBasisLabel;
            if (basis == 0)
                roomBasisLabel = new QLabel("Only breakfast");
            else if (basis == 1)
                roomBasisLabel = new QLabel("Half basis");
            else if (basis == 2)
                roomBasisLabel = new QLabel("Full basis");
            else
                roomBasisLabel = new QLabel;
            guestsLabel->setFont(*font);
            arrDateLabel->setFont(*font);
            depDateLabel->setFont(*font);
            roomBasisLabel->setFont(*font);
            layout->addWidget(guestsLabel, row, col++);
            layout->addWidget(arrDateLabel, row, col++);
            layout->addWidget(depDateLabel, row, col++);
            layout->addWidget(roomBasisLabel, row, col);
            infoReservations.append(guestsLabel);
            infoReservations.append(arrDateLabel);
            infoReservations.append(depDateLabel);
            infoReservations.append(roomBasisLabel);

            row++;
        }
    }
}

void ReservationPanel::showRestaurant() {
    // header
    showHeader();
    unsigned int col = 6, row = 0;
    QLabel *tableHeader = new QLabel("Table");
    QLabel *guestsHeader = new QLabel("Guests");
    QLabel *timeHeader = new QLabel("Time");
    QLabel *allergiesHeader = new QLabel("Allergies");
    additionalLabels.append(tableHeader);
    additionalLabels.append(guestsHeader);
    additionalLabels.append(timeHeader);
    additionalLabels.append(allergiesHeader);
    tableHeader->setFont(*headerFont);
    guestsHeader->setFont(*headerFont);
    timeHeader->setFont(*headerFont);
    allergiesHeader->setFont(*headerFont);
    layout->addWidget(tableHeader, row, col++);
    layout->addWidget(guestsHeader, row, col++);
    layout->addWidget(timeHeader, row, col++);
    layout->addWidget(allergiesHeader, row, col++);
    layout->setRowMinimumHeight(row++, 30);

    // rows
    for (auto it = reservations->begin(); it != reservations->end(); it++) {
        TableRes *tableRes = dynamic_cast<TableRes*>(*it);
        if (tableRes) {
            col = 0;
            showBasicInfo(row, col, tableRes);

            QLabel *guestsLabel = new QLabel(QString::number(tableRes->getGuests()));
            QTime time = QTime(tableRes->getTimeH(), tableRes->getTimeM());
            QLabel *timeLabel = new QLabel(time.toString("hh:mm"));
            QLabel *allergiesLabel = new QLabel(QString::fromStdString(tableRes->getAllergies()));
            guestsLabel->setFont(*font);
            timeLabel->setFont(*font);
            allergiesLabel->setFont(*font);
            layout->addWidget(guestsLabel, row, col++);
            layout->addWidget(timeLabel, row, col++);
            layout->addWidget(allergiesLabel, row, col++);
            infoReservations.append(guestsLabel);
            infoReservations.append(timeLabel);
            infoReservations.append(allergiesLabel);

            row++;
        }
    }
}

void ReservationPanel::showBeach() {
    // header
    showHeader();
    unsigned int col = 6, row = 0;
    QLabel *umbrellaHeader = new QLabel("Umbrella");
    QLabel *sunbedsHeader = new QLabel("Sunbeds");
    QLabel *arrDateHeader = new QLabel("Arrival date");
    QLabel *depDateHeader = new QLabel("Departure date");
    additionalLabels.append(umbrellaHeader);
    additionalLabels.append(sunbedsHeader);
    additionalLabels.append(arrDateHeader);
    additionalLabels.append(depDateHeader);
    umbrellaHeader->setFont(*headerFont);
    sunbedsHeader->setFont(*headerFont);
    arrDateHeader->setFont(*headerFont);
    depDateHeader->setFont(*headerFont);
    layout->addWidget(umbrellaHeader, row, col++);
    layout->addWidget(sunbedsHeader, row, col++);
    layout->addWidget(arrDateHeader, row, col++);
    layout->addWidget(depDateHeader, row, col++);
    layout->setRowMinimumHeight(row++, 30);

    // rows
    for (auto it = reservations->begin(); it != reservations->end(); it++) {
        BeachRes *beachRes = dynamic_cast<BeachRes*>(*it);
        if (beachRes) {
            col = 0;
            showBasicInfo(row, col, beachRes);

            QLabel *sunbedsLabel = new QLabel(QString::number(beachRes->getSunbeds()));
            QDate arrDate(beachRes->getArrDateY(), beachRes->getArrDateM(), beachRes->getArrDateD()), depDate(beachRes->getDepDateY(), beachRes->getDepDateM(), beachRes->getDepDateD());
            QLabel *arrDateLabel = new QLabel(arrDate.toString("dd/MM"));
            QLabel *depDateLabel = new QLabel(depDate.toString("dd/MM"));
            sunbedsLabel->setFont(*font);
            arrDateLabel->setFont(*font);
            depDateLabel->setFont(*font);
            layout->addWidget(sunbedsLabel, row, col++);
            layout->addWidget(arrDateLabel, row, col++);
            layout->addWidget(depDateLabel, row, col++);
            infoReservations.append(sunbedsLabel);
            infoReservations.append(arrDateLabel);
            infoReservations.append(depDateLabel);

            row++;
        }
    }
}

void ReservationPanel::refreshReservations(List *newReservations) {
    reservations = newReservations;
}

void ReservationPanel::signalDelete(Reservation *reservation) {
    emit deletePressed(reservation);
}

void ReservationPanel::signalEdit(Reservation *reservation) {
    emit editPressed(reservation);
}
