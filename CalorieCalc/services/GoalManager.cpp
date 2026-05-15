#include "GoalManager.h"

namespace Services {

    std::shared_ptr<Goal> GoalFactory::createGoal(GoalType type) {
        switch (type) {
        case Loss:     return std::make_shared<WeightLossGoal>();
        case Gain:     return std::make_shared<MassGainGoal>();
        case Maintain:
        default:       return std::make_shared<MaintenanceGoal>();
        }
    }

    double WeightLossGoal::applyGoalModifier(double bmr) const { return bmr * 0.85; }
    QString WeightLossGoal::getGoalName() const { return "Похудение (дефицит 15%)"; }

    double MassGainGoal::applyGoalModifier(double bmr) const { return bmr * 1.15; }
    QString MassGainGoal::getGoalName() const { return "Набор массы (профицит 15%)"; }

    double MaintenanceGoal::applyGoalModifier(double bmr) const { return bmr; }
    QString MaintenanceGoal::getGoalName() const { return "Поддержание веса"; }

} 