#ifndef ROOMRES_H
#define ROOMRES_H

#include <string>
#include "Reservation.h"

enum Basis {breakfast = 0, half = 1, full = 2};

class RoomRes : public Reservation {
    private:
    unsigned int guests;
    Basis roomBasis;

    public:
    RoomRes(
        std::string _surname,
        std::string _name,
        std::string _phone,
        std::string _email,
        unsigned int _guests,
        unsigned int _arrDateY,
        unsigned int _arrDateM,
        unsigned int _arrDateD,
        unsigned int _depDateY,
        unsigned int _depDateM,
        unsigned int _depDateD,
        Basis _roomBasis,
        std::string _notes,
        std::string _room,
        unsigned int _id = getCounter() + 1
    );

    unsigned int getGuests() const;
    Basis getBasis() const;

    void setGuests(unsigned int _guests);
    void setBasis(Basis _roomBasis);

    virtual void accept(ReservationVisitorInterface& visitor) override;
    virtual void save(ReservationVisitorInterface& visitor) override;
};

#endif
