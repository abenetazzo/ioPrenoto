#ifndef UTILITYPANEL_H
#define UTILITYPANEL_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QCalendarWidget>
#include <QRadioButton>

class UtilityPanel : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout *layout, *radioLayout;
    QHBoxLayout *subLayout;
    QLabel *radioLabel, *selectedActivity;
    QImage *room, *table, *umbrella;
    QCalendarWidget *calendar;
    QRadioButton *hotel, *restaurant, *beach;

public:
    UtilityPanel(QWidget *parent = 0);
    virtual QDate getSelectedDate();
    virtual std::string getActivityShown();
    virtual void showHotel();
    virtual void showRestaurant();
    virtual void showBeach();
    virtual void showNewDate();

signals:
    void hotelShown();
    void restaurantShown();
    void beachShown();
    void dateChanged(QDate &newDate);
};

#endif // UTILITYPANEL_H
