#ifndef PROGRESSANALYZER_H
#define PROGRESSANALYZER_H

#include "NutritionDiary.h"
#include <QString>

namespace Services {

    class ProgressAnalyzer {
    public:
        struct ProgressResult {
            double consumed;
            double remaining;
            double percent;
            QString statusMessage;
        };

        static ProgressResult analyze(double current, double target);
    };

} 
#endif