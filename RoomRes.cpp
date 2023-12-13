#include "RoomRes.h"

RoomRes::RoomRes(
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
        unsigned int _id
        ) : Reservation(_arrDateY,
                        _arrDateM,
                        _arrDateD,
                        _depDateY,
                        _depDateM,
                        _depDateD,
                        0,
                        0,
                        0,
                        0,
                        _surname,
                        _name,
                        _phone,
                        _email,
                        _notes,
                        _room,
                        _id),
        guests(_guests),
        roomBasis(_roomBasis) {}

unsigned int RoomRes::getGuests() const {
    return guests;
}

Basis RoomRes::getBasis() const {
    return roomBasis;
}

void RoomRes::setGuests(unsigned int _guests) {
    guests = _guests;
}

void RoomRes::setBasis(Basis _roomBasis) {
    roomBasis = _roomBasis;
}

void RoomRes::accept(ReservationVisitorInterface& visitor) {
    visitor.visitRoomRes(this);
}

void RoomRes::save(ReservationVisitorInterface& visitor) {
    visitor.saveRoomRes(this);
}
