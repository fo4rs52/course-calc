#include "UserProfile.h"

namespace Models {

    UserProfile::UserProfile(double w, double h, int a, bool male)
        : m_weight(w), m_height(h), m_age(a), m_isMale(male)
    {
    }

    QJsonObject UserProfile::toJson() const {
        QJsonObject obj;
        obj["weight"] = m_weight;
        obj["height"] = m_height;
        obj["age"] = m_age;
        obj["isMale"] = m_isMale;
        return obj;
    }

    void UserProfile::fromJson(const QJsonObject& json) {
        m_weight = json["weight"].toDouble();
        m_height = json["height"].toDouble();
        m_age = json["age"].toInt();
        m_isMale = json["isMale"].toBool();
    }

    QString UserProfile::getDisplayName() const {
        return QString("Профиль: %1 кг, %2 см").arg(m_weight).arg(m_height);
    }

}