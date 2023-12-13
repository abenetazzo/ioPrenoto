#include "Reservation.h"

unsigned int Reservation::counter = 0;

Reservation::Reservation(
        int _arrDateY,
        int _arrDateM,
        int _arrDateD,
        int _depDateY,
        int _depDateM,
        int _depDateD,
        int _arrTimeH,
        int _arrTimeM,
        int _depTimeH,
        int _depTimeM,
        std::string _surname,
        std::string _name,
        std::string _phone,
        std::string _email,
        std::string _notes,
        std::string _reservable,
        unsigned int _id
        ) : id(_id),
        arrival({
                .tm_sec=0,
                .tm_min=_arrTimeM,
                .tm_hour=_arrTimeH,
                .tm_mday=_arrDateD,
                .tm_mon=_arrDateM,
                .tm_year=_arrDateY-1900}),
        departure({
                .tm_sec=0,
                .tm_min=_depTimeM,
                .tm_hour=_depTimeH,
                .tm_mday=_depDateD,
                .tm_mon=_depDateM,
                .tm_year=_depDateY-1900}),
        surname(_surname),
        name(_name),
        phone(_phone),
        email(_email),
        notes(_notes),
        reservable(_reservable) {counter++;}

unsigned int Reservation::getID() const {
    return id;
}

unsigned int Reservation::getArrDateY() const {
    return arrival.tm_year + 1900;
}

unsigned int Reservation::getArrDateM() const {
    return arrival.tm_mon;
}

unsigned int Reservation::getArrDateD() const {
    return arrival.tm_mday;
}

unsigned int Reservation::getDepDateY() const {
    return departure.tm_year + 1900;
}

unsigned int Reservation::getDepDateM() const {
    return departure.tm_mon;
}

unsigned int Reservation::getDepDateD() const {
    return departure.tm_mday;
}

unsigned int Reservation::getArrTimeH() const {
    return arrival.tm_hour;
}

unsigned int Reservation::getArrTimeM() const {
    return arrival.tm_min;
}

unsigned int Reservation::getDepTimeH() const {
    return departure.tm_hour;
}

unsigned int Reservation::getDepTimeM() const {
    return departure.tm_min;
}

std::string Reservation::getSurname() const {
    return surname;
}

std::string Reservation::getName() const {
    return name;
}

std::string Reservation::getPhone() const {
    return phone;
}

std::string Reservation::getEmail() const {
    return email;
}

std::string Reservation::getNotes() const {
    return notes;
}

std::string Reservation::getReservable() const {
    return reservable;
}

bool Reservation::isParked() const {
    return reservable != "";
}

void Reservation::setArrDate(unsigned int _arrDateY, unsigned int _arrDateM, unsigned int _arrDateD) {
    arrival.tm_year = _arrDateY - 1900;
    arrival.tm_mon = _arrDateM;
    arrival.tm_mday = _arrDateD;
}

void Reservation::setDepDate(unsigned int _depDateY, unsigned int _depDateM, unsigned int _depDateD) {
    departure.tm_year = _depDateY - 1900;
    departure.tm_mon = _depDateM;
    departure.tm_mday = _depDateD;
}

void Reservation::setArrTime(unsigned int _arrTimeH, unsigned int _arrTimeM) {
    arrival.tm_hour = _arrTimeH;
    arrival.tm_min = _arrTimeM;
}

void Reservation::setDepTime(unsigned int _depTimeH, unsigned int _depTimeM) {
    departure.tm_hour = _depTimeH;
    departure.tm_min = _depTimeM;
}

void Reservation::setSurname(std::string _surname) {
    surname = _surname;
}

void Reservation::setName(std::string _name) {
    name = _name;
}

void Reservation::setPhone(std::string _phone) {
    phone = _phone;
}

void Reservation::setEmail(std::string _email) {
    email = _email;
}

void Reservation::setNotes(std::string _notes) {
    notes = _notes;
}

void Reservation::park(std::string _reservable) {
    reservable = _reservable;
}

bool Reservation::operator==(const Reservation &reservation) const {
    return id == reservation.id;
}

bool Reservation::operator!=(const Reservation &reservation) const {
    return id != reservation.id;
}

bool Reservation::operator==(Reservation &reservation) const {
    return id == reservation.id;
}

bool Reservation::operator!=(Reservation &reservation) const {
    return id != reservation.id;
}

unsigned int Reservation::getCounter() {
    return counter;
}

void Reservation::setCounter(unsigned int n) {
    counter = n;
}
