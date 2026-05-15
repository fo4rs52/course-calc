#include "NutritionDiary.h"

namespace Services {

    NutritionDiary::NutritionDiary() {}

    void NutritionDiary::addMeal(std::shared_ptr<Models::Meal> meal) {
        if (meal) {
            m_dailyMeals.push_back(meal);
            notifyObservers();
        }
    }

    void NutritionDiary::addObserver(INutritionObserver* observer) {
        if (observer) {
            m_observers.push_back(observer);
        }
    }

    void NutritionDiary::notifyObservers() {
        double currentCals = totalDayCalories();
        for (auto* observer : m_observers) {
            if (observer) {
                observer->onCaloriesChanged(currentCals);
            }
        }
    }

    double NutritionDiary::totalDayCalories() const {
        double sum = 0;
        for (const auto& m : m_dailyMeals) {
            sum += m->totalCalories();
        }
        return sum;
    }

    double NutritionDiary::totalDayProteins() const {
        double sum = 0;
        for (const auto& m : m_dailyMeals) {
            sum += m->totalProteins();
        }
        return sum;
    }

    double NutritionDiary::totalDayFats() const {
        double sum = 0;
        for (const auto& m : m_dailyMeals) {
            sum += m->totalFats();
        }
        return sum;
    }

    double NutritionDiary::totalDayCarbs() const {
        double sum = 0;
        for (const auto& m : m_dailyMeals) {
            sum += m->totalCarbs();
        }
        return sum;
    }

    void NutritionDiary::clear() {
        m_dailyMeals.clear();
        notifyObservers(); 
    }

} 