#ifndef NUTRITIONDIARY_H
#define NUTRITIONDIARY_H

#include "models/Meal.h"
#include "NotificationManager.h" // Содержит интерфейс INutritionObserver
#include <vector>
#include <memory>

namespace Services {

    class NutritionDiary {
    private:
        // Список приемов пищи за день
        std::vector<std::shared_ptr<Models::Meal>> m_dailyMeals;

        // Список наблюдателей (Паттерн Observer)
        std::vector<INutritionObserver*> m_observers;

        // Метод оповещения всех подписчиков
        void notifyObservers();

    public:
        NutritionDiary();

        // Методы управления данными
        void addMeal(std::shared_ptr<Models::Meal> meal);
        void clear();

        // Регистрация наблюдателей
        void addObserver(INutritionObserver* observer);

        // Расчет итогов дня (Агрегация)
        double totalDayCalories() const;
        double totalDayProteins() const;
        double totalDayFats() const;
        double totalDayCarbs() const;
    };

} // namespace Services

#endif