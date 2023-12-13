#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "UtilityPanel.h"
#include "ReservationPanel.h"
#include "Data.h"
#include "SearchWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Data *data;
    UtilityPanel *utilityPanel;
    ReservationPanel *reservationPanel;
    SearchWindow *searchWindow;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static unsigned int mainWindowHeigth, mainWindowWidth;

public slots:
    virtual void showHotel();
    virtual void showRestaurant();
    virtual void showBeach();
    virtual void refreshDate(QDate &date);
    virtual void deleteConfirmation(Reservation *reservation);
    virtual void editWindow(Reservation *reservation);
    virtual void addReservation(Reservation *reservation);
    virtual void newWindow();
    virtual void newSearchWindow();
    virtual void searchByName(QString pattern);
    virtual void searchByPhone(QString pattern);
    virtual void searchByEmail(QString pattern);
};

#endif // MAINWINDOW_H
