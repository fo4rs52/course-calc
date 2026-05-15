#include "Meal.h"
#include <QJsonArray>

namespace Models {

    Meal::Meal(QString name) : m_mealName(name) {}

    void Meal::addPortion(const Portion& portion) {
        m_portions.push_back(portion);
    }

    double Meal::totalCalories() const {
        double sum = 0;
        for (const auto& p : m_portions) sum += p.totalCalories();
        return sum;
    }

    double Meal::totalProteins() const {
        double sum = 0;
        for (const auto& p : m_portions) sum += p.totalProteins();
        return sum;
    }

    double Meal::totalFats() const {
        double sum = 0;
        for (const auto& p : m_portions) sum += p.totalFats();
        return sum;
    }

    double Meal::totalCarbs() const {
        double sum = 0;
        for (const auto& p : m_portions) sum += p.totalCarbs();
        return sum;
    }

    QJsonObject Meal::toJson() const {
        QJsonObject obj;
        obj["name"] = m_mealName;

        QJsonArray portionsArray;
        for (const auto& p : m_portions) {
            portionsArray.append(p.toJson());
        }
        obj["portions"] = portionsArray;

        return obj;
    }

    void Meal::fromJson(const QJsonObject& json) {
        m_mealName = json["name"].toString();
        m_portions.clear();

        QJsonArray portionsArray = json["portions"].toArray();
        for (int i = 0; i < portionsArray.size(); ++i) {
            Portion p;
            p.fromJson(portionsArray[i].toObject());
            m_portions.push_back(p);
        }
    }

}