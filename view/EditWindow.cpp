#include <QString>
#include <QDate>
#include <QTime>
#include "EditWindow.h"

EditWindow::EditWindow(Reservation *_reservation, QWidget *parent) : QDialog(parent), fieldsLayout(new QGridLayout), reservation(_reservation), visitor(this, fieldsLayout) {
    QPushButton *cancel = new QPushButton("Cancel");
    QPushButton *confirm = new QPushButton("Confirm");
    connect(cancel, &QPushButton::clicked,this, &EditWindow::close);
    connect(confirm, &QPushButton::clicked,this, &EditWindow::saveChanges);

    QDialogButtonBox *buttons = new QDialogButtonBox(Qt::Horizontal);
    buttons->addButton(cancel, QDialogButtonBox::RejectRole);
    buttons->addButton(confirm, QDialogButtonBox::AcceptRole);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);
}

void EditWindow::showWindow() {
    QLabel *surnameLabel = new QLabel("Surname:");
    QLabel *nameLabel = new QLabel("Name:");
    QLabel *phoneLabel = new QLabel("Phone:");
    QLabel *emailLabel = new QLabel("E-Mail:");
    QLabel *notesLabel = new QLabel("Notes:");
    surnameLine = new QLineEdit();
    nameLine = new QLineEdit();
    phoneLine = new QLineEdit();
    emailLine = new QLineEdit();
    notesLine = new QLineEdit();
    surnameLine->setText(QString::fromStdString(reservation->getSurname()));
    nameLine->setText(QString::fromStdString(reservation->getName()));
    phoneLine->setText(QString::fromStdString(reservation->getPhone()));
    emailLine->setText(QString::fromStdString(reservation->getEmail()));
    notesLine->setText(QString::fromStdString(reservation->getNotes()));
    surnameLabel->setBuddy(surnameLine);
    nameLabel->setBuddy(nameLine);
    phoneLabel->setBuddy(phoneLine);
    emailLabel->setBuddy(emailLine);
    notesLabel->setBuddy(notesLine);
    fieldsLayout->addWidget(surnameLabel, 0, 0);
    fieldsLayout->addWidget(surnameLine, 0, 1);
    fieldsLayout->addWidget(nameLabel, 1, 0);
    fieldsLayout->addWidget(nameLine, 1, 1);
    fieldsLayout->addWidget(phoneLabel, 2, 0);
    fieldsLayout->addWidget(phoneLine, 2, 1);
    fieldsLayout->addWidget(emailLabel, 3, 0);
    fieldsLayout->addWidget(emailLine, 3, 1);
    fieldsLayout->addWidget(notesLabel, 4, 0);
    fieldsLayout->addWidget(notesLine, 4, 1);

    reservation->accept(visitor);
}

void EditWindow::saveChanges() {
    reservation->setSurname(surnameLine->displayText().toStdString());
    reservation->setName(nameLine->displayText().toStdString());
    reservation->setPhone(phoneLine->displayText().toStdString());
    reservation->setEmail(emailLine->displayText().toStdString());
    reservation->setNotes(notesLine->displayText().toStdString());
    reservation->save(visitor);

    QWidget::close();
}
