#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDoubleSpinBox>
#include "../Reservation.h"
#include "ReservationInfoVisitor.h"

class EditWindow: public QDialog {
    Q_OBJECT
private:
    QGridLayout *fieldsLayout;
    Reservation *reservation;
    QLineEdit *surnameLine, *nameLine, *phoneLine, *emailLine, *notesLine; // common info
    QLineEdit *roomLine, *tableLine, *allergiesLine, *umbrellaLine; // specific info
    QComboBox *basis;
    QDateEdit *dateLine, *arrDateLine, *depDateLine;
    QTimeEdit *timeLine;
    QDoubleSpinBox *guestsLine, *sunbedsLine;
    ReservationInfoVisitor visitor;

public:
    EditWindow(Reservation *_reservation, QWidget *parent = 0);
    virtual void showWindow();

public slots:
    virtual void saveChanges();

signals:
    void dataChanged(Reservation *reservation);
};

#endif // EDITWINDOW_H
