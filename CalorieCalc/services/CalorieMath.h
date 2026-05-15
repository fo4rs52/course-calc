#ifndef CALORIEMATH_H
#define CALORIEMATH_H

#include "models/UserProfile.h"
#include <memory>
#include <QString>

namespace Services {

    class ICalorieStrategy {
    public:
        virtual ~ICalorieStrategy() = default;
        virtual double calculateBMR(const Models::UserProfile& user) const = 0;
        virtual QString getFormulaName() const = 0;
    };

    class MifflinStrategy : public ICalorieStrategy {
    public:
        double calculateBMR(const Models::UserProfile& user) const override;
        QString getFormulaName() const override;
    };

    class HarrisBenedictStrategy : public ICalorieStrategy {
    public:
        double calculateBMR(const Models::UserProfile& user) const override;
        QString getFormulaName() const override;
    };

} 
#endif