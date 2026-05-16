#include "DashboardWidget.h"

DashboardWidget::DashboardWidget(QWidget* parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Прогресс за день:", this));

    m_calorieBar = new QProgressBar(this);
    m_calorieBar->setTextVisible(true);
    m_calorieBar->setStyleSheet("QProgressBar::chunk { background-color: #3498db; }");
    layout->addWidget(m_calorieBar);

    m_macrosLabel = new QLabel("Б: 0г | Ж: 0г | У: 0г", this);
    layout->addWidget(m_macrosLabel);

    m_adviceLabel = new QLabel("Начните вносить данные!", this);
    m_adviceLabel->setWordWrap(true);
    m_adviceLabel->setStyleSheet("font-style: italic; color: #7f8c8d;");
    layout->addWidget(m_adviceLabel);
}

void DashboardWidget::updateStats(double current, double target, double p, double f, double c, QString advice) {
    m_calorieBar->setMaximum(static_cast<int>(target));
    m_calorieBar->setValue(static_cast<int>(current));
    m_calorieBar->setFormat(QString("%1 / %2 ккал").arg((int)current).arg((int)target));

    m_macrosLabel->setText(QString("Белки: %1г | Жиры: %2г | Углеводы: %3г").arg(p, 0, 'f', 1).arg(f, 0, 'f', 1).arg(c, 0, 'f', 1));
    m_adviceLabel->setText(advice);
}