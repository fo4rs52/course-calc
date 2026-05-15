#ifndef GOALMANAGER_H
#define GOALMANAGER_H

#include <memory>
#include <QString>

namespace Services {

    class Goal {
    public:
        virtual ~Goal() = default;
        virtual double applyGoalModifier(double bmr) const = 0;
        virtual QString getGoalName() const = 0;
    };

    class WeightLossGoal : public Goal {
    public:
        double applyGoalModifier(double bmr) const override;
        QString getGoalName() const override;
    };

    class MassGainGoal : public Goal {
    public:
        double applyGoalModifier(double bmr) const override;
        QString getGoalName() const override;
    };

    class MaintenanceGoal : public Goal {
    public:
        double applyGoalModifier(double bmr) const override;
        QString getGoalName() const override;
    };

    class GoalFactory {
    public:
        enum GoalType { Loss, Maintain, Gain };

        static std::shared_ptr<Goal> createGoal(GoalType type);
    };

} 
#endif