#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>
#include <QJsonObject>

struct Contact {
    QString name;
    QString mobile;
    QString email;
    QDate birthday;

    QJsonObject toJson() const {
        QJsonObject json;
        json["name"] = name;
        json["mobile"] = mobile;
        json["email"] = email;
        json["birthday"] = birthday.toString(Qt::ISODate);
        return json;
    }

    static Contact fromJson(const QJsonObject& json) {
        Contact contact;
        if (json.contains("name") && json["name"].isString())
            contact.name = json["name"].toString();
        if (json.contains("mobile") && json["mobile"].isString())
            contact.mobile = json["mobile"].toString();
        if (json.contains("email") && json["email"].isString())
            contact.email = json["email"].toString();
        if (json.contains("birthday") && json["birthday"].isString())
            contact.birthday = QDate::fromString(json["birthday"].toString(), Qt::ISODate);
        return contact;
    }
};

#endif // CONTACT_H
