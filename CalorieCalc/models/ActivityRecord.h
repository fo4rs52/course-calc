#ifndef ACTIVITYRECORD_H
#define ACTIVITYRECORD_H

#include "Entity.h"

namespace Models {

    class ActivityRecord : public Entity {
    private:
        QString m_type;
        double m_kcalBurned;

    public:
        ActivityRecord(QString type = "Тренировка", double kcal = 0);

        double kcalBurned() const { return m_kcalBurned; }

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject& json) override;
        QString getDisplayName() const override { return m_type + " (-" + QString::number(m_kcalBurned) + " ккал)"; }
    };

}
#endif