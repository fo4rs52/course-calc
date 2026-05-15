#include "ProgressAnalyzer.h"

namespace Services {

    ProgressAnalyzer::ProgressResult ProgressAnalyzer::analyze(double current, double target) {
        ProgressResult res;
        res.consumed = current;
        res.remaining = target - current;
        res.percent = (current / target) * 100.0;

        if (res.percent < 80) {
            res.statusMessage = "Можно еще поесть!";
        }
        else if (res.percent <= 100) {
            res.statusMessage = "Норма почти выполнена. Идеально!";
        }
        else {
            res.statusMessage = "Внимание! Лимит калорий превышен.";
        }

        return res;
    }

}