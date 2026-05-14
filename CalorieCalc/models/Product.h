#ifndef PRODUCT_H
#define PRODUCT_H

#include "Entity.h"

namespace Models {

    class Product : public Entity {
    private:
        QString m_name;
        double m_p, m_f, m_c;

    public:
        Product(QString name = "", double p = 0, double f = 0, double c = 0);

        QString name() const { return m_name; }
        double proteins() const { return m_p; }
        double fats() const { return m_f; }
        double carbs() const { return m_c; }
        double caloriesPer100g() const { return (m_p * 4.0) + (m_f * 9.0) + (m_c * 4.0); }

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject& json) override;
        QString getDisplayName() const override { return m_name; }
    };

}
#endif