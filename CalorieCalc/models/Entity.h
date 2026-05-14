#ifndef ENTITY_H
#define ENTITY_H

#include <QString>
#include <QJsonObject>

namespace Models {

    class Entity {
    public:
        virtual ~Entity() = default;

        virtual QJsonObject toJson() const = 0;
        virtual void fromJson(const QJsonObject& json) = 0;
        virtual QString getDisplayName() const = 0;
    };

}
#endif