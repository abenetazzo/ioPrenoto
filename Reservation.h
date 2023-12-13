#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <ctime>
#include "ReservationVisitorInterface.h"

class Reservation {
private:
    unsigned int id;
    tm arrival, departure;
    std::string surname;
    std::string name;
    std::string phone;
    std::string email;
    std::string notes;
    std::string reservable;

    static unsigned int counter;

public:
    Reservation(
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
        unsigned int _id = counter + 1
    );
    virtual ~Reservation() = default;

    unsigned int getID() const;
    unsigned int getArrDateY() const;
    unsigned int getArrDateM() const;
    unsigned int getArrDateD() const;
    unsigned int getDepDateY() const;
    unsigned int getDepDateM() const;
    unsigned int getDepDateD() const;
    unsigned int getArrTimeH() const;
    unsigned int getArrTimeM() const;
    unsigned int getDepTimeH() const;
    unsigned int getDepTimeM() const;
    std::string getSurname() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getNotes() const;
    std::string getReservable() const;
    virtual bool isParked() const;
    void setArrDate(unsigned int _arrDateY, unsigned int _arrDateM, unsigned int _arrDateD);
    void setDepDate(unsigned int _depDateY, unsigned int _depDateM, unsigned int _depDateD);
    void setArrTime(unsigned int _arrTimeH, unsigned int _arrTimeM);
    void setDepTime(unsigned int _depTimeH, unsigned int _depTimeM);
    void setSurname(std::string _surname);
    void setName(std::string _name);
    void setPhone(std::string _phone);
    void setEmail(std::string _email);
    void setNotes(std::string _notes);
    void park(std::string _reservable);

    virtual void accept(ReservationVisitorInterface& visitor) = 0;
    virtual void save(ReservationVisitorInterface& visitor) = 0;

    bool operator==(const Reservation &reservation) const;
    bool operator!=(const Reservation &reservation) const;
    bool operator==(Reservation &reservation) const;
    bool operator!=(Reservation &reservation) const;

    static unsigned int getCounter();
    static void setCounter(unsigned int n);
};

#endif // RESERVATION_H
