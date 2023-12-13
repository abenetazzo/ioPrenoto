#ifndef BEACHRES_H
#define BEACHRES_H

#include <chrono>
#include "Reservation.h"

class BeachRes : public Reservation {
private:
    unsigned int sunbeds;

public:
    BeachRes(
        std::string _surname,
        std::string _name,
        std::string _phone,
        std::string _email,
        unsigned int _arrDateY,
        unsigned int _arrDateM,
        unsigned int _arrDateD,
        unsigned int _depDateY,
        unsigned int _depDateM,
        unsigned int _depDateD,
        std::string _notes,
        unsigned int _sunbeds,
        std::string _umbrella,
        unsigned int _id = getCounter() + 1
    );

    unsigned int getSunbeds() const;

    void setSunbeds(unsigned int _sunbeds);

    virtual void accept(ReservationVisitorInterface& visitor) override;
    virtual void save(ReservationVisitorInterface& visitor) override;
};

#endif
