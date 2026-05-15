#include "NotificationManager.h"

namespace Services {

    NotificationManager::NotificationManager(double limit)
        : m_limit(limit), m_lastAdvice("Данных пока нет") {
    }

    void NotificationManager::onCaloriesChanged(double totalCalories) {
        double percent = (totalCalories / m_limit) * 100.0;

        if (percent > 100.0) {
            m_lastAdvice = "ВНИМАНИЕ: Лимит калорий превышен!";
        }
        else if (percent > 80.0) {
            m_lastAdvice = "Вы близки к суточной норме.";
        }
        else {
            m_lastAdvice = "Норма соблюдается. Хороший темп!";
        }
    }

    void NotificationManager::setLimit(double limit) {
        m_limit = limit;
    }

    QString NotificationManager::getLastAdvice() const {
        return m_lastAdvice;
    }

} 