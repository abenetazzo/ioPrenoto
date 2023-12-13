#include "TableRes.h"

TableRes::TableRes(
        std::string _surname,
        std::string _name,
        std::string _phone,
        std::string _email,
        unsigned int _guests,
        unsigned int _dateY,
        unsigned int _dateM,
        unsigned int _dateD,
        unsigned int _timeH,
        unsigned int _timeM,
        std::string _notes,
        std::string _allergies,
        std::string _table,
        unsigned int _id
        ) : Reservation(_dateY,
                        _dateM,
                        _dateD,
                        _dateY,
                        _dateM,
                        _dateD,
                        _timeH,
                        _timeM,
                        _timeH,
                        _timeM,
                        _surname,
                        _name,
                        _phone,
                        _email,
                        _notes,
                        _table,
                        _id),
        guests(_guests),
        allergies(_allergies) {}

unsigned int TableRes::getGuests() const {
    return guests;
}

unsigned int TableRes::getDateY() const {
    return getArrDateY();
}

unsigned int TableRes::getDateM() const {
    return getArrDateM();
}

unsigned int TableRes::getDateD() const {
    return getArrDateD();
}

unsigned int TableRes::getTimeH() const {
    return getArrTimeH();
}

unsigned int TableRes::getTimeM() const {
    return getArrTimeM();
}

std::string TableRes::getAllergies() const {
    return allergies;
}

void TableRes::setGuests(unsigned int _guests) {
    guests = _guests;
}

void TableRes::setDate(unsigned int _dateY, unsigned int _dateM, unsigned int _dateD) {
    setArrDate(_dateY, _dateM, _dateD);
    setDepDate(_dateY, _dateM, _dateD);
}

void TableRes::setTime(unsigned int _timeH, unsigned int _timeM) {
    setArrTime(_timeH, _timeM);
    setDepTime(_timeH, _timeM);
}

void TableRes::setAllergies(std::string _allergies) {
    allergies = _allergies;
}

void TableRes::accept(ReservationVisitorInterface& visitor) {
    visitor.visitTableRes(this);
}

void TableRes::save(ReservationVisitorInterface& visitor) {
    visitor.saveTableRes(this);
}
