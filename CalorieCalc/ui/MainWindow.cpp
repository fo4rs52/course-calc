#include "MainWindow.h"
#include "models/Product.h"
#include "models/Portion.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();

    connect(m_testButton, &QPushButton::clicked, this, &MainWindow::runModelTest);
}

void MainWindow::setupUi() {
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_mainLayout = new QVBoxLayout(m_centralWidget);

    m_infoLabel = new QLabel("Добро пожаловать в Калькулятор Калорий\nНажмите кнопку для теста", this);
    m_infoLabel->setAlignment(Qt::AlignCenter);
    m_infoLabel->setStyleSheet("font-size: 16px; color: #333;");

    m_testButton = new QPushButton("Проверить расчет (Apple 200g)", this);
    m_testButton->setMinimumHeight(40);

    m_mainLayout->addWidget(m_infoLabel);
    m_mainLayout->addWidget(m_testButton);

    setWindowTitle("Advanced Calorie Counter");
    resize(400, 300);
}

void MainWindow::runModelTest() {
    using namespace Models;

    auto apple = std::make_shared<Product>("Яблоко", 0.4, 0.4, 9.8);

    Portion p(apple, 200.0);

    QString result = QString("Успех\n\n"
        "Продукт: %1\n"
        "Калорий на 100г: %2\n"
        "Вес порции: 200г\n"
        "ИТОГО калорий в порции: %3")
        .arg(apple->getDisplayName())
        .arg(apple->caloriesPer100g(), 0, 'f', 1)
        .arg(p.totalCalories(), 0, 'f', 1);

    m_infoLabel->setText(result);
}