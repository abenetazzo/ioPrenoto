#include "EditButton.h"

EditButton::EditButton(Reservation *_reservation, QIcon *_icon, QString *_text) : QPushButton(*_icon, *_text), reservation(_reservation) {
    connect(this, &QPushButton::clicked, this, &EditButton::pressEdit);
}

Reservation* EditButton::getReservation() {
    return reservation;
}

void EditButton::pressEdit() {
    emit editPressed(reservation);
}
