#ifndef PORTION_H
#define PORTION_H

#include "Product.h"
#include <memory>

namespace Models {

    class Portion : public Entity {
    private:
        std::shared_ptr<Product> m_product;
        double m_weight;

    public:
        Portion(std::shared_ptr<Product> p = nullptr, double w = 0);

        double totalCalories() const { return (m_product->caloriesPer100g() * m_weight) / 100.0; }
        double totalProteins() const { return (m_product->proteins() * m_weight) / 100.0; }

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject& json) override;
        QString getDisplayName() const override;
    };

}
#endif