#ifndef DATA_H
#define DATA_H

#include <QJsonObject>
#include "Reservation.h"
#include "List.h"

class Data {
private:
    List reservations;

public:
    Data();
    ~Data();
    List* getReservations();
    bool loadData();
    bool saveData() const;
    void readData(const QJsonObject &json);
    void writeData(QJsonObject &json) const;
    void addReservation(Reservation *reservation);
    void removeReservation(Reservation *reservation);
};

#endif // DATA_H
