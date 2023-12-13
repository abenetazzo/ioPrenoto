#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QRadioButton>
#include "../List.h"

class SearchWindow : public QDialog {
    Q_OBJECT
private:
    List *reservations;
    QGridLayout *gridLayout;
    QVector<QLabel*> additionalLabels;
    QVector<QLabel*> infoReservations;
    QRadioButton *nameRadio, *phoneRadio, *emailRadio;
    QLineEdit *pattern;
    QFont *headerFont, *font;

public:
    SearchWindow(QWidget *parent = 0);
    virtual void cleanLabels();

public slots:
    virtual void search();
    virtual void showWindow(List *newReservations);

signals:
    void searchByName(QString pattern);
    void searchByPhone(QString pattern);
    void searchByEmail(QString pattern);
};

#endif // SEARCHWINDOW_H
