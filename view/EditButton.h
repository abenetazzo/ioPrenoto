#ifndef EDITBUTTON_H
#define EDITBUTTON_H

#include <QPushButton>
#include <QString>
#include "../Reservation.h"

class EditButton : public QPushButton {
    Q_OBJECT
private:
    Reservation *reservation;

public:
    EditButton(Reservation* _reservation, QIcon *_icon, QString *_text = new QString());
    virtual Reservation* getReservation();

public slots:
    virtual void pressEdit();

signals:
    void editPressed(Reservation* reservation);
};

#endif // EDITBUTTON_H
