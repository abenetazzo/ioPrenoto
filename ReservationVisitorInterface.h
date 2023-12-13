#ifndef RESERVATIONVISITORINTERFACE_H
#define RESERVATIONVISITORINTERFACE_H

class BeachRes;
class RoomRes;
class TableRes;

class ReservationVisitorInterface {
  public:
    virtual ~ReservationVisitorInterface() = default;
    virtual void visitBeachRes(BeachRes *beachRes) = 0;
    virtual void visitRoomRes(RoomRes *roomRes) = 0;
    virtual void visitTableRes(TableRes *tableRes) = 0;
    virtual void saveBeachRes(BeachRes *beachRes) = 0;
    virtual void saveRoomRes(RoomRes *roomRes) = 0;
    virtual void saveTableRes(TableRes *tableRes) = 0;
};

#endif // RESERVATIONVISITORINTERFACE_H
