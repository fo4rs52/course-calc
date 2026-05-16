#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>

class DashboardWidget : public QWidget {
    Q_OBJECT
private:
    QProgressBar* m_calorieBar;
    QLabel* m_macrosLabel; 
    QLabel* m_adviceLabel;

public:
    explicit DashboardWidget(QWidget* parent = nullptr);
    void updateStats(double current, double target, double p, double f, double c, QString advice);
};

#endif