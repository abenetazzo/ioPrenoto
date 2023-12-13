#include "DeleteButton.h"

DeleteButton::DeleteButton(Reservation *_reservation, QIcon *_icon, QString *_text) : QPushButton(*_icon, *_text), reservation(_reservation) {
    connect(this, &QPushButton::clicked, this, &DeleteButton::pressDelete);
}

Reservation* DeleteButton::getReservation() {
    return reservation;
}

void DeleteButton::pressDelete() {
    emit deletePressed(reservation);
}
