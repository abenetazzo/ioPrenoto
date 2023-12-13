#include "BeachRes.h"

BeachRes::BeachRes(
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
                        _umbrella,
                        _id),
        sunbeds(_sunbeds) {}

unsigned int BeachRes::getSunbeds() const {
    return sunbeds;
}

void BeachRes::setSunbeds(unsigned int _sunbeds) {
    sunbeds = _sunbeds;
}

void BeachRes::accept(ReservationVisitorInterface& visitor) {
    visitor.visitBeachRes(this);
}

void BeachRes::save(ReservationVisitorInterface& visitor) {
    visitor.saveBeachRes(this);
}
