#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QString>
#include <vector>

namespace Services {

    class INutritionObserver {
    public:
        virtual ~INutritionObserver() = default;
        virtual void onCaloriesChanged(double totalCalories) = 0;
    };

    class NotificationManager : public INutritionObserver {
    private:
        double m_limit;
        QString m_lastAdvice;

    public:
        explicit NotificationManager(double limit = 2000.0);

        void onCaloriesChanged(double totalCalories) override;

        void setLimit(double limit);
        QString getLastAdvice() const;
    };

} 
#endif