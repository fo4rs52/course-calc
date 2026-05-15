#include "MainWindow.h"
#include "ProductDialog.h"
#include "models/UserProfile.h"
#include "services/CalorieMath.h"
#include "services/GoalManager.h"
#include "services/ProgressAnalyzer.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_storage("products.json")
{
    setupUi();

    m_notifier = std::make_shared<Services::NotificationManager>(2000.0); 
    m_diary.addObserver(m_notifier.get());

    loadData();

    connect(m_addProductButton, &QPushButton::clicked, this, [this]() {
        ProductDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            auto newProduct = dialog.getProduct();
            m_catalog.addProduct(newProduct);
            m_storage.saveCatalog(m_catalog);
            updateList();
        }
        });

    connect(m_calcButton, &QPushButton::clicked, this, &MainWindow::handleCalculation);
}

void MainWindow::setupUi() {
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    m_mainLayout = new QVBoxLayout(m_centralWidget);

    m_titleLabel = new QLabel("Каталог продуктов и анализ нормы:", this);
    m_titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50;");

    m_productListView = new QListWidget(this);

    m_addProductButton = new QPushButton("Создать новый продукт", this);
    m_addProductButton->setMinimumHeight(40);
    m_addProductButton->setStyleSheet("background-color: #27ae60; color: white;");

    m_calcButton = new QPushButton("Проверить дневную норму", this);
    m_calcButton->setMinimumHeight(40);
    m_calcButton->setStyleSheet("background-color: #2980b9; color: white;");

    m_mainLayout->addWidget(m_titleLabel);
    m_mainLayout->addWidget(m_productListView);
    m_mainLayout->addWidget(m_addProductButton);
    m_mainLayout->addWidget(m_calcButton);

    setWindowTitle("Advanced Calorie Counter - OOP Project");
    resize(500, 600);
}

void MainWindow::handleCalculation() {
    using namespace Services;

    Models::UserProfile user(80.0, 180.0, 25, true);

    std::unique_ptr<ICalorieStrategy> strategy = std::make_unique<MifflinStrategy>();
    double bmr = strategy->calculateBMR(user);

    auto goal = GoalFactory::createGoal(GoalFactory::Loss);
    double target = goal->applyGoalModifier(bmr);

    m_notifier->setLimit(target);

    m_diary.clear();
    auto lunch = std::make_shared<Models::Meal>("Обед");
    if (!m_catalog.getAllProducts().empty()) {
        lunch->addPortion(Models::Portion(m_catalog.getAllProducts().at(0), 500.0));
    }
    m_diary.addMeal(lunch); 

    auto result = ProgressAnalyzer::analyze(m_diary.totalDayCalories(), target);

    QString report = QString(
        "Цель: %1\n"
        "Ваша норма: %2 ккал\n"
        "Съедено: %3 ккал\n\n"
        "Вердикт: %4\n"
        "Уведомление: %5" 
    ).arg(goal->getGoalName())
        .arg(target, 0, 'f', 0)
        .arg(result.consumed, 0, 'f', 0)
        .arg(result.statusMessage)
        .arg(m_notifier->getLastAdvice());

    QMessageBox::information(this, "Анализ прогресса", report);
}

void MainWindow::loadData() {
    if (!m_storage.loadCatalog(m_catalog)) {
        m_catalog.addProduct(std::make_shared<Models::Product>("Куриная грудка", 23, 2, 0));
        m_storage.saveCatalog(m_catalog);
    }
    updateList();
}

void MainWindow::updateList() {
    m_productListView->clear();
    for (const auto& p : m_catalog.getAllProducts()) {
        m_productListView->addItem(p->getDisplayName() + " | " + QString::number(p->caloriesPer100g(), 'f', 0) + " ккал");
    }
}