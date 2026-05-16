#include "ActivityRecord.h"

namespace Models {
    ActivityRecord::ActivityRecord(QString type, double kcal) : m_type(type), m_kcalBurned(kcal) {}

    QJsonObject ActivityRecord::toJson() const {
        QJsonObject obj;
        obj["type"] = m_type;
        obj["kcal"] = m_kcalBurned;
        return obj;
    }

    void ActivityRecord::fromJson(const QJsonObject& json) {
        m_type = json["type"].toString();
        m_kcalBurned = json["kcal"].toDouble();
    }
}