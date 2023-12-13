#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QRadioButton>
#include <QStringList>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDoubleSpinBox>
#include "../Data.h"

class NewWindow: public QDialog {
    Q_OBJECT
private:
    Data *data;
    QVBoxLayout *mainLayout;
    QGridLayout *fieldsLayout;
    QDialogButtonBox *buttons;
    QPushButton *confirm, *cancel;
    QVector<QLabel*> labels;
    QLineEdit *surnameLine, *nameLine, *phoneLine, *emailLine, *notesLine; // common info
    QLineEdit *roomLine, *tableLine, *allergiesLine, *umbrellaLine; // specific info
    QComboBox *basis;
    QDateEdit *dateLine, *arrDateLine, *depDateLine;
    QTimeEdit *timeLine;
    QDoubleSpinBox *guestsLine, *sunbedsLine;
    QString activity;

public:
    NewWindow(Data *_data, QString &activity, QWidget *parent = 0);
    virtual void showWindow();
    virtual void showBasicInfo();
    virtual void showHotel();
    virtual void showRestaurant();
    virtual void showBeach();

public slots:
    virtual void addReservation();
};

#endif // NEWWINDOW_H
