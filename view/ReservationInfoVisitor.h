#ifndef RESERVATIONINFOVISITOR_H
#define RESERVATIONINFOVISITOR_H

#include <QWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QGridLayout>
#include <QComboBox>
#include "../ReservationVisitorInterface.h"

class ReservationInfoVisitor: public ReservationVisitorInterface {
  private:
    QWidget* widget;
    QGridLayout *fieldsLayout;
    QLineEdit *umbrellaLine, *roomLine, *tableLine, *allergiesLine;
    QDoubleSpinBox *guestsLine, *sunbedsLine;
    QDateEdit *dateLine, *arrDateLine, *depDateLine;
    QComboBox *basis;
    QTimeEdit *timeLine;

  public:
    ReservationInfoVisitor(QWidget *_widget, QGridLayout *_fieldsLayout);
    virtual void visitBeachRes(BeachRes *beachRes);
    virtual void visitRoomRes(RoomRes *roomRes);
    virtual void visitTableRes(TableRes *tableRes);
    virtual void saveBeachRes(BeachRes *beachRes);
    virtual void saveRoomRes(RoomRes *roomRes);
    virtual void saveTableRes(TableRes *tableRes);
};

#endif // RESERVATIONINFOVISITOR_H
