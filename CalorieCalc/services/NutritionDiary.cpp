#include "NutritionDiary.h"
#include <algorithm>

namespace Services {

    NutritionDiary::NutritionDiary() {}

    void NutritionDiary::addMeal(std::shared_ptr<Models::Meal> meal) {
        if (meal) {
            m_dailyMeals.push_back(meal);
            notifyObservers();
        }
    }

    void NutritionDiary::addActivity(std::shared_ptr<Models::ActivityRecord> act) {
        if (act) {
            m_activities.push_back(act);
            notifyObservers();
        }
    }

    void NutritionDiary::addObserver(INutritionObserver* observer) {
        if (observer) m_observers.push_back(observer);
    }

    void NutritionDiary::notifyObservers() {
        double current = totalDayCalories();
        for (auto* obs : m_observers) {
            if (obs) obs->onCaloriesChanged(current);
        }
    }

    double NutritionDiary::totalDayCalories() const {
        double consumed = 0;
        for (const auto& m : m_dailyMeals) consumed += m->totalCalories();

        double burned = 0;
        for (const auto& a : m_activities) burned += a->kcalBurned();

        return std::max(0.0, consumed - burned);
    }

    double NutritionDiary::totalDayProteins() const {
        double sum = 0;
        for (const auto& m : m_dailyMeals) sum += m->totalProteins();
        return sum;
    }

    double NutritionDiary::totalDayFats() const {
        double sum = 0;
        for (const auto& m : m_dailyMeals) sum += m->totalFats();
        return sum;
    }

    double NutritionDiary::totalDayCarbs() const {
        double sum = 0;
        for (const auto& m : m_dailyMeals) sum += m->totalCarbs();
        return sum;
    }

    void NutritionDiary::clear() {
        m_dailyMeals.clear();
        m_activities.clear();
        notifyObservers();
    }

} 