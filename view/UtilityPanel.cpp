#include "UtilityPanel.h"

UtilityPanel::UtilityPanel(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    subLayout = new QHBoxLayout;
    subLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout->addLayout(subLayout);

    radioLayout = new QVBoxLayout;
    radioLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    subLayout->addLayout(radioLayout);

    radioLabel = new QLabel("Select the activity:");
    hotel = new QRadioButton("Hotel");
    restaurant = new QRadioButton("Restaurant");
    beach = new QRadioButton("Beach");
    radioLayout->addWidget(radioLabel);
    radioLayout->addWidget(hotel);
    radioLayout->addWidget(restaurant);
    radioLayout->addWidget(beach);

    subLayout->addStretch(1);

    selectedActivity = new QLabel;
    room = new QImage(":/assets/room.png");
    table = new QImage(":/assets/table.png");
    umbrella = new QImage(":/assets/umbrella.png");
    subLayout->addWidget(selectedActivity);

    calendar = new QCalendarWidget;
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    layout->addWidget(calendar);

    hotel->setChecked(true);
    selectedActivity->setPixmap(QPixmap::fromImage(*room));

    connect(hotel, &QRadioButton::toggled, this, &UtilityPanel::showHotel);
    connect(restaurant, &QRadioButton::toggled, this, &UtilityPanel::showRestaurant);
    connect(beach, &QRadioButton::toggled, this, &UtilityPanel::showBeach);
    connect(calendar, &QCalendarWidget::selectionChanged, this, &UtilityPanel::showNewDate);
}

QDate UtilityPanel::getSelectedDate() {
    return calendar->selectedDate();
}

std::string UtilityPanel::getActivityShown() {
    std::string activityShown = "";
    if (hotel->isChecked())
        activityShown = "hotel";
    else if (restaurant->isChecked())
        activityShown = "restaurant";
    else if (beach->isChecked())
        activityShown = "beach";
    return activityShown;
}

void UtilityPanel::showHotel() {
    selectedActivity->setPixmap(QPixmap::fromImage(*room));
    emit hotelShown();
}

void UtilityPanel::showRestaurant() {
    selectedActivity->setPixmap(QPixmap::fromImage(*table));
    emit restaurantShown();
}

void UtilityPanel::showBeach() {
    selectedActivity->setPixmap(QPixmap::fromImage(*umbrella));
    emit beachShown();
}

void UtilityPanel::showNewDate() {
    QDate newDate = calendar->selectedDate();
    emit dateChanged(newDate);
}
