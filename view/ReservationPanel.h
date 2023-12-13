#ifndef RESERVATIONPANEL_H
#define RESERVATIONPANEL_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include "EditButton.h"
#include "DeleteButton.h"
#include "../List.h"

class ReservationPanel : public QWidget {
    Q_OBJECT
private:
    QGridLayout *layout;
    List *reservations;
    QLabel *editHeader, *deleteHeader, *nameHeader, *phoneHeader, *emailHeader, *notesHeader;
    QVector<QLabel*> additionalLabels;
    QVector<QLabel*> infoReservations;
    QVector<EditButton*> editButtons;
    QVector<DeleteButton*> deleteButtons;
    QFont *headerFont, *font;
    QIcon *editIcon, *delIcon;

public:
    ReservationPanel(List *_reservations, QWidget *parent = 0);
    virtual void showHeader();
    virtual void showHotel();
    virtual void showRestaurant();
    virtual void showBeach();
    virtual void showBasicInfo(unsigned int row, unsigned int &col, Reservation *reservation);
    virtual void cleanLabels();

public slots:
    virtual void refreshReservations(List *newReservations);
    virtual void signalDelete(Reservation *reservation);
    virtual void signalEdit(Reservation *reservation);

signals:
    void deletePressed(Reservation *reservation);
    void editPressed(Reservation *reservation);
};

#endif // RESERVATIONPANEL_H
