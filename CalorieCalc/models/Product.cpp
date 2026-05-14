#include "Product.h"

namespace Models {

    Product::Product(QString name, double p, double f, double c)
        : m_name(name), m_p(p), m_f(f), m_c(c) {}

    QJsonObject Product::toJson() const {
        QJsonObject obj;
        obj["name"] = m_name;
        obj["p"] = m_p;
        obj["f"] = m_f;
        obj["c"] = m_c;
        return obj;
    }

    void Product::fromJson(const QJsonObject& json) {
        m_name = json["name"].toString();
        m_p = json["p"].toDouble();
        m_f = json["f"].toDouble();
        m_c = json["c"].toDouble();
    }

}