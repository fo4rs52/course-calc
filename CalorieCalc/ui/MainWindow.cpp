#include "MainWindow.h"
#include "ProductDialog.h"
#include "models/UserProfile.h"
#include "services/CalorieMath.h"
#include "services/GoalManager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_storage("products.json")
{
    setupUi();
    loadData();

    connect(m_testButton, &QPushButton::clicked, this, [this]() {
        ProductDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            auto newProduct = dialog.getProduct();
            m_catalog.addProduct(newProduct);
            m_storage.saveCatalog(m_catalog);
            updateList();
        }
        });

    connect(m_calcButton, &QPushButton::clicked, this, [this]() {
        Models::UserProfile user(85.0, 185.0, 30, true);

        std::unique_ptr<Services::ICalorieStrategy> strategy = std::make_unique<Services::MifflinStrategy>();
        double bmr = strategy->calculateBMR(user);

        auto goal = Services::GoalFactory::createGoal(Services::GoalFactory::Loss);
        double target = goal->applyGoalModifier(bmr);

        QString info = QString("Пользователь: Мужчина, 85кг, 185см, 30 лет\n\n"
            "Формула: %1\n"
            "Базовый обмен: %2 ккал\n"
            "Выбранная цель: %3\n"
            "ИТОГОВАЯ НОРМА: %4 ккал")
            .arg(strategy->getFormulaName())
            .arg(bmr, 0, 'f', 0)
            .arg(goal->getGoalName())
            .arg(target, 0, 'f', 0);

        QMessageBox::information(this, "Анализ прогресса и целей", info);
        });
}

void MainWindow::setupUi() {
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    m_mainLayout = new QVBoxLayout(m_centralWidget);

    m_titleLabel = new QLabel("Каталог доступных продуктов:", this);
    m_titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50;");

    m_productListView = new QListWidget(this);
    m_productListView->setStyleSheet("QListWidget { border: 1px solid #bdc3c7; border-radius: 5px; }");

    m_testButton = new QPushButton("Добавить новый продукт", this);
    m_testButton->setMinimumHeight(40);
    m_testButton->setStyleSheet("background-color: #27ae60; color: white; font-weight: bold;");

    m_calcButton = new QPushButton("Рассчитать целевую норму", this);
    m_calcButton->setMinimumHeight(40);
    m_calcButton->setStyleSheet("background-color: #2980b9; color: white; font-weight: bold;");

    m_mainLayout->addWidget(m_titleLabel);
    m_mainLayout->addWidget(m_productListView);
    m_mainLayout->addWidget(m_testButton);
    m_mainLayout->addWidget(m_calcButton);

    setWindowTitle("Advanced Calorie Counter");
    resize(500, 650);
}

void MainWindow::loadData() {
    if (!m_storage.loadCatalog(m_catalog)) {
        m_catalog.addProduct(std::make_shared<Models::Product>("Курица", 23, 2, 0));
        m_catalog.addProduct(std::make_shared<Models::Product>("Рис", 7, 1, 78));
        m_storage.saveCatalog(m_catalog);
    }
    updateList();
}

void MainWindow::updateList() {
    m_productListView->clear();
    for (const auto& product : m_catalog.getAllProducts()) {
        QString item = QString("%1 | Б:%2 Ж:%3 У:%4 | %5 ккал")
            .arg(product->getDisplayName())
            .arg(product->proteins())
            .arg(product->fats())
            .arg(product->carbs())
            .arg(product->caloriesPer100g(), 0, 'f', 0);
        m_productListView->addItem(item);
    }
}