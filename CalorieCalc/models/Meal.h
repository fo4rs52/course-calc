#ifndef MEAL_H
#define MEAL_H

#include "Entity.h"
#include "Portion.h"
#include <vector>

namespace Models {

    class Meal : public Entity {
    private:
        QString m_mealName; 
        std::vector<Portion> m_portions; 

    public:
        explicit Meal(QString name = "Прием пищи");

        void addPortion(const Portion& portion);
        const std::vector<Portion>& getPortions() const { return m_portions; }

        double totalCalories() const;
        double totalProteins() const;
        double totalFats() const;
        double totalCarbs() const;

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject& json) override;
        QString getDisplayName() const override { return m_mealName; }
    };

} 
#endif