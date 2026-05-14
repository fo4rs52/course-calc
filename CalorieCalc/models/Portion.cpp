#include "Portion.h"

namespace Models {

    Portion::Portion(std::shared_ptr<Product> p, double w)
        : m_product(p), m_weight(w) {}

    QString Portion::getDisplayName() const {
        if (!m_product) return "Unknown";
        return QString("%1 (%2г)").arg(m_product->name()).arg(m_weight);
    }

    QJsonObject Portion::toJson() const {
        QJsonObject obj;
        if (m_product) obj["product"] = m_product->toJson();
        obj["weight"] = m_weight;
        return obj;
    }

    void Portion::fromJson(const QJsonObject& json) {
        m_weight = json["weight"].toDouble();
    }

}