#include <QScrollArea>
#include "SearchWindow.h"
#include "Mainwindow.h"

SearchWindow::SearchWindow(QWidget *parent) : QDialog(parent), gridLayout(new QGridLayout) {
    headerFont = new QFont("Century Gothic", 14, QFont::Bold);
    font = new QFont("Century Gothic", 10);

    nameRadio = new QRadioButton("Search by name");
    phoneRadio = new QRadioButton("Search by phone");
    emailRadio = new QRadioButton("Search by e-mail");

    QVBoxLayout *radioLayout = new QVBoxLayout;
    radioLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    radioLayout->addWidget(nameRadio);
    radioLayout->addWidget(phoneRadio);
    radioLayout->addWidget(emailRadio);
    nameRadio->setChecked(true);

    pattern = new QLineEdit();

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *client = new QWidget;
    client->setFixedSize(MainWindow::mainWindowWidth, MainWindow::mainWindowHeigth/4);
    client->setLayout(gridLayout);
    scrollArea->setWidget(client);

    int col = 0;
    QLabel *nameHeader = new QLabel;
    QLabel *phoneHeader = new QLabel;
    QLabel *emailHeader = new QLabel;
    QLabel *dateHeader = new QLabel;
    nameHeader->setFont(*headerFont);
    phoneHeader->setFont(*headerFont);
    emailHeader->setFont(*headerFont);
    dateHeader->setFont(*headerFont);
    gridLayout->addWidget(nameHeader, 0, col++);
    gridLayout->addWidget(phoneHeader, 0, col++);
    gridLayout->addWidget(emailHeader, 0, col++);
    gridLayout->addWidget(dateHeader, 0, col);
    nameHeader->setText("Name");
    phoneHeader->setText("Phone");
    emailHeader->setText("E-Mail");
    dateHeader->setText("Date");

    QPushButton *search = new QPushButton("Search");
    QPushButton *close = new QPushButton("Close");
    QDialogButtonBox *buttons = new QDialogButtonBox(Qt::Horizontal);
    buttons->addButton(close, QDialogButtonBox::RejectRole);
    buttons->addButton(search, QDialogButtonBox::AcceptRole);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(radioLayout);
    mainLayout->addWidget(pattern);
    mainLayout->addWidget(client);
    mainLayout->addWidget(buttons);

    connect(close, &QPushButton::clicked,this, &SearchWindow::close);
    connect(search, &QPushButton::clicked,this, &SearchWindow::search);
    connect(pattern, &QLineEdit::textChanged,this, &SearchWindow::search);

    setLayout(mainLayout);
}

void SearchWindow::search() {
    if (nameRadio->isChecked())
        emit searchByName(pattern->text());
    if (phoneRadio->isChecked())
        emit searchByPhone(pattern->text());
    if (emailRadio->isChecked())
        emit searchByEmail(pattern->text());
}

void SearchWindow::cleanLabels() {
    for (auto it = additionalLabels.begin(); it != additionalLabels.end();) {
        QLabel *additionalLabel = *it;
        gridLayout->removeWidget(additionalLabel);
        delete additionalLabel;
        it = additionalLabels.erase(it);
    }
    for (auto it = infoReservations.begin(); it != infoReservations.end();) {
        QLabel *infoReservation = *it;
        gridLayout->removeWidget(infoReservation);
        delete infoReservation;
        it = infoReservations.erase(it);
    }
}

void SearchWindow::showWindow(List *newReservations) {
    reservations = newReservations;

    cleanLabels();

    unsigned int col = 0, row = 1;
    for (auto it = reservations->begin(); it != reservations->end(); it++) {
        col = 0;
        QLabel *nameLabel = new QLabel(QString::fromStdString((*it)->getSurname() + " " + (*it)->getName()));
        QLabel *phoneLabel = new QLabel(QString::fromStdString((*it)->getPhone()));
        QLabel *emailLabel = new QLabel(QString::fromStdString((*it)->getEmail()));
        QLabel *dateLabel = new QLabel(QString::number((*it)->getArrDateD()) + "/" + QString::number((*it)->getArrDateM()) + "/" + QString::number((*it)->getArrDateY()));
        nameLabel->setFont(*font);
        phoneLabel->setFont(*font);
        emailLabel->setFont(*font);
        dateLabel->setFont(*font);
        gridLayout->addWidget(nameLabel, row, col++);
        gridLayout->addWidget(phoneLabel, row, col++);
        gridLayout->addWidget(emailLabel, row, col++);
        gridLayout->addWidget(dateLabel, row, col++);
        infoReservations.append(nameLabel);
        infoReservations.append(phoneLabel);
        infoReservations.append(emailLabel);
        infoReservations.append(dateLabel);

        gridLayout->setRowMinimumHeight(row, 18);
        row++;
    }
}
