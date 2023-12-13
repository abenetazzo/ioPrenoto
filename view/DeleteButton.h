#ifndef DELETEBUTTON_H
#define DELETEBUTTON_H

#include <QPushButton>
#include <QString>
#include "../Reservation.h"

class DeleteButton : public QPushButton {
    Q_OBJECT
private:
    Reservation *reservation;

public:
    DeleteButton(Reservation* _reservation, QIcon *_icon, QString *_text = new QString());
    virtual Reservation* getReservation();

public slots:
    virtual void pressDelete();

signals:
    void deletePressed(Reservation* reservation);
};

#endif // DELETEBUTTON_H
