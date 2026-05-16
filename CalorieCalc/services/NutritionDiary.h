#ifndef NUTRITIONDIARY_H
#define NUTRITIONDIARY_H

#include <vector>
#include <memory>
#include "models/Meal.h"
#include "models/ActivityRecord.h"
#include "services/NotificationManager.h"

namespace Services {

    class NutritionDiary {
    private:
        std::vector<std::shared_ptr<Models::Meal>> m_dailyMeals;
        std::vector<std::shared_ptr<Models::ActivityRecord>> m_activities;
        std::vector<INutritionObserver*> m_observers;

        void notifyObservers();

    public:
        NutritionDiary();

        void addMeal(std::shared_ptr<Models::Meal> meal);
        void addActivity(std::shared_ptr<Models::ActivityRecord> act);
        void addObserver(INutritionObserver* observer);
        void clear();

        double totalDayCalories() const;
        double totalDayProteins() const;
        double totalDayFats() const;
        double totalDayCarbs() const;
    };

} 
#endif