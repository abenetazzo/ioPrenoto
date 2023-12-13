#ifndef TABLERES_H
#define TABLERES_H

#include "Reservation.h"

class TableRes : public Reservation {
private:
    unsigned int guests;
    std::string allergies;

public:
    TableRes(
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
        unsigned int _id = getCounter() + 1
    );

    unsigned int getGuests() const;
    unsigned int getDateY() const;
    unsigned int getDateM() const;
    unsigned int getDateD() const;
    unsigned int getTimeH() const;
    unsigned int getTimeM() const;
    std::string getAllergies() const;

    void setGuests(unsigned int _guests);
    void setDate(unsigned int _dateY, unsigned int _dateM, unsigned int _dateD);
    void setTime(unsigned int _timeH, unsigned int _timeM);
    void setAllergies(std::string _allergies);

    virtual void accept(ReservationVisitorInterface& visitor) override;
    virtual void save(ReservationVisitorInterface& visitor) override;
};

#endif // TABLERES_H
