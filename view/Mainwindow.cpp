#include <QSplitter>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include "Mainwindow.h"
#include "EditWindow.h"
#include "NewWindow.h"

unsigned int MainWindow::mainWindowWidth = 1024;
unsigned int MainWindow::mainWindowHeigth = 512;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), data(nullptr), searchWindow(nullptr) {
    data = new Data();

    QToolBar *toolbar = addToolBar("main toolbar");
    QPixmap newIcon(":/assets/new.png");
    QPixmap searchIcon(":/assets/search.png");
    QPixmap quitIcon(":/assets/quit.png");
    QAction *newRes = toolbar->addAction(QIcon(newIcon), "New Reservation");
    QAction *searchRes = toolbar->addAction(QIcon(searchIcon), "Search Reservation");
    toolbar->addSeparator();
    QAction *quit = toolbar->addAction(QIcon(quitIcon), "Quit Application");

    QSplitter *splitter = new QSplitter(this);
    setCentralWidget(splitter);
    utilityPanel = new UtilityPanel();
    utilityPanel->setFixedSize(mainWindowWidth/3, mainWindowHeigth);
    splitter->addWidget(utilityPanel);
    List *reservations = data->getReservations();
    QDate selectedDate = utilityPanel->getSelectedDate();
    unsigned int selectedY = selectedDate.year(), selectedM = selectedDate.month(), selectedD = selectedDate.day();
    List *results = new List(reservations->searchByDate(selectedY, selectedM, selectedD));
    reservationPanel = new ReservationPanel(results);
    reservationPanel->setFixedSize((mainWindowWidth/3)*2, mainWindowHeigth);
    splitter->addWidget(reservationPanel);

    QDate date = utilityPanel->getSelectedDate();
    refreshDate(date);

    connect(newRes, &QAction::triggered, this, &MainWindow::newWindow);
    connect(searchRes, &QAction::triggered, this, &MainWindow::newSearchWindow);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(utilityPanel, &UtilityPanel::hotelShown, this, &MainWindow::showHotel);
    connect(utilityPanel, &UtilityPanel::restaurantShown, this, &MainWindow::showRestaurant);
    connect(utilityPanel, &UtilityPanel::beachShown, this, &MainWindow::showBeach);
    connect(utilityPanel, &UtilityPanel::dateChanged, this, &MainWindow::refreshDate);
    connect(reservationPanel, &ReservationPanel::deletePressed, this, &MainWindow::deleteConfirmation);
    connect(reservationPanel, &ReservationPanel::editPressed, this, &MainWindow::editWindow);
}

MainWindow::~MainWindow() {
    delete data;
}

void MainWindow::showHotel() {
    reservationPanel->showHotel();
}

void MainWindow::showRestaurant() {
    reservationPanel->showRestaurant();
}

void MainWindow::showBeach() {
    reservationPanel->showBeach();
}

void MainWindow::refreshDate(QDate &newDate) {
    List *reservations = data->getReservations();
    unsigned int selectedY = newDate.year(), selectedM = newDate.month(), selectedD = newDate.day();
    List *newReservations = new List(reservations->searchByDate(selectedY, selectedM, selectedD));
    reservationPanel->refreshReservations(newReservations);
    if (utilityPanel->getActivityShown() == "hotel")
        showHotel();
    else if (utilityPanel->getActivityShown() == "restaurant")
        showRestaurant();
    else if (utilityPanel->getActivityShown() == "beach")
        showBeach();
}

void MainWindow::deleteConfirmation(Reservation *reservation) {
    QMessageBox msgBox;
    msgBox.setText("Press OK to delete the reservation.");
    msgBox.setInformativeText("Press Close to go back.");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
    int ret = msgBox.exec();
    QDate selectedDate;
    switch (ret) {
        case QMessageBox::Ok:
            data->removeReservation(reservation);
            selectedDate = utilityPanel->getSelectedDate();
            refreshDate(selectedDate);
            break;
        case QMessageBox::Close:
            // do nothing
            break;
        default:
            // should never be reached
            break;
    }
}

void MainWindow::editWindow(Reservation *reservation) {
    EditWindow *editWindow = new EditWindow(reservation);
    editWindow->setFixedSize(mainWindowWidth/2, mainWindowHeigth/2);
    editWindow->setModal(true);
    editWindow->showWindow();
    editWindow->exec();
    QDate date = utilityPanel->getSelectedDate();
    refreshDate(date);
}

void MainWindow::addReservation(Reservation *reservation) {
    data->addReservation(reservation);
}

void MainWindow::newWindow() {
    QString activity(QString::fromStdString(utilityPanel->getActivityShown()));
    NewWindow *newWindow = new NewWindow(data, activity);
    newWindow->setFixedSize(mainWindowWidth/2, mainWindowHeigth/2);
    newWindow->setModal(true);
    newWindow->showWindow();
    newWindow->exec();
    QDate date = utilityPanel->getSelectedDate();
    refreshDate(date);
}

void MainWindow::newSearchWindow() {
    searchWindow = new SearchWindow();
    searchWindow->setFixedSize(mainWindowWidth,  (mainWindowHeigth/3)*2);
    searchWindow->setModal(true);

    connect(searchWindow, &SearchWindow::searchByName, this, &MainWindow::searchByName);
    connect(searchWindow, &SearchWindow::searchByPhone, this, &MainWindow::searchByPhone);
    connect(searchWindow, &SearchWindow::searchByEmail, this, &MainWindow::searchByEmail);

    searchWindow->exec();

    delete searchWindow;
    QDate date = utilityPanel->getSelectedDate();
    refreshDate(date);
}

void MainWindow::searchByName(QString pattern) {
    List *results = new List(data->getReservations()->searchByName(pattern.toStdString()));
    searchWindow->showWindow(results);
}

void MainWindow::searchByPhone(QString pattern) {
    List *results = new List(data->getReservations()->searchByPhone(pattern.toStdString()));
    searchWindow->showWindow(results);}

void MainWindow::searchByEmail(QString pattern) {
    List *results = new List(data->getReservations()->searchByEmail(pattern.toStdString()));
    searchWindow->showWindow(results);
}
