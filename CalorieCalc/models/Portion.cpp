#include "Portion.h"

namespace Models {

    Portion::Portion(std::shared_ptr<Product> p, double w)
        : m_product(p), m_weight(w) {
    }

    double Portion::totalCalories() const {
        if (!m_product) return 0.0;
        return (m_product->caloriesPer100g() * m_weight) / 100.0;
    }

    double Portion::totalProteins() const {
        if (!m_product) return 0.0;
        return (m_product->proteins() * m_weight) / 100.0;
    }

    double Portion::totalFats() const {
        if (!m_product) return 0.0;
        return (m_product->fats() * m_weight) / 100.0;
    }

    double Portion::totalCarbs() const {
        if (!m_product) return 0.0;
        return (m_product->carbs() * m_weight) / 100.0;
    }

    QString Portion::getDisplayName() const {
        if (!m_product) return "Неизвестная порция";
        return QString("%1 (%2г)").arg(m_product->getDisplayName()).arg(m_weight);
    }

    QJsonObject Portion::toJson() const {
        QJsonObject obj;
        obj["weight"] = m_weight;
        if (m_product) {
            obj["product"] = m_product->toJson();
        }
        return obj;
    }

    void Portion::fromJson(const QJsonObject& json) {
        m_weight = json["weight"].toDouble();

        if (json.contains("product")) {
            m_product = std::make_shared<Product>();
            m_product->fromJson(json["product"].toObject());
        }
    }

} 