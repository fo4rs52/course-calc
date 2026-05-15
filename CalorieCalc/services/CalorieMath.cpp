#include "CalorieMath.h"

namespace Services {
    double MifflinStrategy::calculateBMR(const Models::UserProfile& user) const {
        double base = (10.0 * user.weight()) + (6.25 * user.height()) - (5.0 * user.age());

        if (user.isMale()) {
            return base + 5.0;
        }
        else {
            return base - 161.0;
        }
    }

    QString MifflinStrategy::getFormulaName() const {
        return QString("Миффлин-Сан Жеор (современная)");
    }

    double HarrisBenedictStrategy::calculateBMR(const Models::UserProfile& user) const {
        if (user.isMale()) {
            return 88.362 + (13.397 * user.weight()) + (4.799 * user.height()) - (5.677 * user.age());
        }
        else {
            return 447.593 + (9.247 * user.weight()) + (3.098 * user.height()) - (4.330 * user.age());
        }
    }

    QString HarrisBenedictStrategy::getFormulaName() const {
        return QString("Харрис-Бенедикт (классическая)");
    }

} 