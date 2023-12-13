#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QString>
#include "TableRes.h"
#include "BeachRes.h"
#include "RoomRes.h"
#include "Data.h"

Data::Data() {
    loadData();
}

List* Data::getReservations() {
    return &reservations;
}

bool Data::loadData() {
    QFile loadFile("saveFile.json");

    if (!loadFile.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file for loading operations.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    readData(loadDoc.object());

    QTextStream(stdout) << "Save file loaded.\n";
    return true;
}

bool Data::saveData() const {
    QFile loadFile("saveFile.json");
    loadFile.moveToTrash();

    QFile saveFile("saveFile.json");

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file for saving operations.");
        return false;
    }

    QJsonObject sessionObject;
    writeData(sessionObject);
    saveFile.write(QJsonDocument(sessionObject).toJson());
    QTextStream(stdout) << "Data saved to file.\n";

    return true;
}

void Data::readData(const QJsonObject &json) {
    if (!json.empty()) {
        if (json.contains("reservations")) {
            const QJsonArray reservationsArray = json["reservations"].toArray();
            for (int i=0; i<reservationsArray.size(); i++) {
                const QJsonObject reservationObject = reservationsArray[i].toObject();
                unsigned int jid;
                std::string jname, jsurname, jphone, jemail, jnotes, jreservable;
                jid = reservationObject["id"].toInt();
                jsurname = reservationObject["surname"].toString().toStdString();
                jname = reservationObject["name"].toString().toStdString();
                jphone = reservationObject["phone"].toString().toStdString();
                jemail = reservationObject["email"].toString().toStdString();
                jnotes = reservationObject["notes"].toString().toStdString();
                if (reservationObject.contains("reservable")) jreservable = reservationObject["reservable"].toString().toStdString();
                if (reservationObject["reservationType"] == "Restaurant") {
                    unsigned int jguests, jyear, jmonth, jday, jhour, jminute;
                    std::string jallergies;
                    jguests = reservationObject["guests"].toInt();
                    QJsonObject jsDate;
                    jsDate = reservationObject["date"].toObject();
                    jyear = jsDate["year"].toInt();
                    jmonth = jsDate["month"].toInt();
                    jday = jsDate["day"].toInt();
                    QJsonObject jsTime;
                    jsTime = reservationObject["time"].toObject();
                    jhour = jsTime["hour"].toInt();
                    jminute = jsTime["minute"].toInt();
                    jallergies = reservationObject["allergies"].toString().toStdString();
                    TableRes *tableRes = new TableRes(jsurname, jname, jphone, jemail, jguests, jyear, jmonth, jday, jhour, jminute, jnotes, jallergies, jreservable, jid);
                    reservations.insertFront(tableRes);
                }
                if (reservationObject["reservationType"] == "Beach") {
                    unsigned int jsunbeds, jarrYear, jarrMonth, jarrDay, jdepYear, jdepMonth, jdepDay;
                    jsunbeds = reservationObject["sunbeds"].toInt();
                    QJsonObject jsArrDate, jsDepDate;
                    jsArrDate = reservationObject["arrivalDate"].toObject();
                    jsDepDate = reservationObject["departureDate"].toObject();
                    jarrYear = jsArrDate["year"].toInt();
                    jarrMonth = jsArrDate["month"].toInt();
                    jarrDay = jsArrDate["day"].toInt();
                    jdepYear = jsDepDate["year"].toInt();
                    jdepMonth = jsDepDate["month"].toInt();
                    jdepDay = jsDepDate["day"].toInt();
                    BeachRes *beachRes = new BeachRes(jsurname, jname, jphone, jemail, jarrYear, jarrMonth, jarrDay, jdepYear, jdepMonth, jdepDay, jnotes, jsunbeds, jreservable, jid);
                    reservations.insertFront(beachRes);
                }
                if (reservationObject["reservationType"] == "Hotel") {
                    unsigned int jguests, jarrYear, jarrMonth, jarrDay, jdepYear, jdepMonth, jdepDay;
                    Basis jbasis;
                    jguests = reservationObject["guests"].toInt();
                    QJsonObject jsArrDate, jsDepDate;
                    jsArrDate = reservationObject["arrivalDate"].toObject();
                    jsDepDate = reservationObject["departureDate"].toObject();
                    jarrYear = jsArrDate["year"].toInt();
                    jarrMonth = jsArrDate["month"].toInt();
                    jarrDay = jsArrDate["day"].toInt();
                    jdepYear = jsDepDate["year"].toInt();
                    jdepMonth = jsDepDate["month"].toInt();
                    jdepDay = jsDepDate["day"].toInt();
                    jbasis = static_cast<Basis>(reservationObject["basis"].toInt());
                    RoomRes *roomRes = new RoomRes(jsurname, jname, jphone, jemail, jguests, jarrYear, jarrMonth, jarrDay, jdepYear, jdepMonth, jdepDay, jbasis, jnotes, jreservable, jid);
                    reservations.insertFront(roomRes);
                }
            }
            if (json.contains("reservationCounter")) Reservation::setCounter(json["reservationCounter"].toInt());
        }
    }
}

void Data::writeData(QJsonObject &json) const {
    if (!reservations.isEmpty()) {
        QJsonArray reservationsArray;
        auto it = reservations.begin();
        while (it != reservations.end()) {
            QJsonObject reservationObject;
            reservationObject["id"] = int((*it)->getID());
            reservationObject["surname"] = QString::fromStdString((*it)->getSurname());
            reservationObject["name"] = QString::fromStdString((*it)->getName());
            reservationObject["phone"] = QString::fromStdString((*it)->getPhone());
            reservationObject["email"] = QString::fromStdString((*it)->getEmail());
            reservationObject["notes"] = QString::fromStdString((*it)->getNotes());
            if ((*it)->getReservable() != "") reservationObject["reservable"] = QString::fromStdString((*it)->getReservable());
            TableRes *tableRes = dynamic_cast<TableRes*>(*it);
            if (tableRes) {
                reservationObject["guests"] = int(tableRes->getGuests());
                QJsonObject jsDate, jsTime;
                jsDate["year"] = int(tableRes->getDateY());
                jsDate["month"] = int(tableRes->getDateM());
                jsDate["day"] = int(tableRes->getDateD());
                reservationObject["date"] = jsDate;
                jsTime["hour"] = int(tableRes->getTimeH());
                jsTime["minute"] = int(tableRes->getTimeM());
                reservationObject["time"] = jsTime;
                reservationObject["allergies"] = QString::fromStdString(tableRes->getAllergies());
                reservationObject["reservationType"] = "Restaurant";
            }
            BeachRes *beachRes = dynamic_cast<BeachRes*>(*it);
            if (beachRes) {
                reservationObject["sunbeds"] = int(beachRes->getSunbeds());
                QJsonObject jsArrDate, jsDepDate;
                jsArrDate["year"] = int(beachRes->getArrDateY());
                jsArrDate["month"] = int(beachRes->getArrDateM());
                jsArrDate["day"] = int(beachRes->getArrDateD());
                jsDepDate["year"] = int(beachRes->getDepDateY());
                jsDepDate["month"] = int(beachRes->getDepDateM());
                jsDepDate["day"] = int(beachRes->getDepDateD());
                reservationObject["arrivalDate"] = jsArrDate;
                reservationObject["departureDate"] = jsDepDate;
                reservationObject["reservationType"] = "Beach";
            }
            RoomRes *roomRes = dynamic_cast<RoomRes*>(*it);
            if (roomRes) {
                reservationObject["guests"] = int(roomRes->getGuests());
                QJsonObject jsArrDate, jsDepDate;
                jsArrDate["year"] = int(roomRes->getArrDateY());
                jsArrDate["month"] = int(roomRes->getArrDateM());
                jsArrDate["day"] = int(roomRes->getArrDateD());
                jsDepDate["year"] = int(roomRes->getDepDateY());
                jsDepDate["month"] = int(roomRes->getDepDateM());
                jsDepDate["day"] = int(roomRes->getDepDateD());
                reservationObject["basis"] = roomRes->getBasis();
                reservationObject["arrivalDate"] = jsArrDate;
                reservationObject["departureDate"] = jsDepDate;
                reservationObject["reservationType"] = "Hotel";
            }
            reservationsArray.append(reservationObject);
            it++;
        }
        json["reservations"] = reservationsArray;
        int counter = Reservation::getCounter();
        json["reservationCounter"] = counter;
    }
}

void Data::addReservation(Reservation *reservation) {
    reservations.insertFront(reservation);
}

void Data::removeReservation(Reservation *reservation) {
    reservations.remove(reservation);
}

Data::~Data() {
    saveData();
}
