#include "MainWindow.h"
#include "ProductDialog.h"
#include "ActivityDialog.h"
#include "services/CalorieMath.h"
#include "services/GoalManager.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_storage("products.json")
{
    setupUi();

    m_notifier = std::make_shared<Services::NotificationManager>(2000.0);
    m_diary.addObserver(m_notifier.get());

    loadData();
    refreshDashboard();
}

void MainWindow::setupUi() {
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    auto rootLayout = new QHBoxLayout(m_centralWidget);

    auto leftLayout = new QVBoxLayout();
    auto catGroup = new QGroupBox("Каталог продуктов", this);
    auto catLayout = new QVBoxLayout(catGroup);

    m_productListView = new QListWidget(this);
    m_addProductButton = new QPushButton("Новый продукт", this);
    m_delProductButton = new QPushButton("Удалить выбранный", this);
    m_delProductButton->setStyleSheet("background-color: #e74c3c; color: white;");
    m_addActivityButton = new QPushButton("Добавить тренировку", this);
    m_addActivityButton->setStyleSheet("background-color: #f39c12; color: white;");

    catLayout->addWidget(m_productListView);
    catLayout->addWidget(m_addProductButton);
    catLayout->addWidget(m_delProductButton);
    catLayout->addWidget(m_addActivityButton);
    leftLayout->addWidget(catGroup);

    auto rightLayout = new QVBoxLayout();

    auto profGroup = new QGroupBox("Ваш профиль", this);
    auto profLayout = new QFormLayout(profGroup);
    m_weightSpin = new QDoubleSpinBox(this); m_weightSpin->setRange(30, 200); m_weightSpin->setValue(80);
    m_heightSpin = new QDoubleSpinBox(this); m_heightSpin->setRange(100, 250); m_heightSpin->setValue(180);
    m_ageSpin = new QSpinBox(this); m_ageSpin->setRange(10, 99); m_ageSpin->setValue(25);
    profLayout->addRow("Вес (кг):", m_weightSpin);
    profLayout->addRow("Рост (см):", m_heightSpin);
    profLayout->addRow("Возраст:", m_ageSpin);

    m_dashboard = new DashboardWidget(this);
    m_logFoodButton = new QPushButton("СЪЕСТЬ ВЫБРАННОЕ (200г)", this);
    m_logFoodButton->setMinimumHeight(50);
    m_logFoodButton->setStyleSheet("background-color: #2ecc71; color: white; font-weight: bold;");

    m_resetButton = new QPushButton("Очистить день", this);

    m_formulaCombo = new QComboBox(this);
    m_formulaCombo->addItem("Миффлин-Сан Жеор");
    m_formulaCombo->addItem("Харрис-Бенедикт");
    profLayout->addRow("Формула расчета:", m_formulaCombo);

    rightLayout->addWidget(profGroup);
    rightLayout->addWidget(m_dashboard);
    rightLayout->addWidget(m_logFoodButton);
    rightLayout->addWidget(m_resetButton);
    rightLayout->addStretch();

    rootLayout->addLayout(leftLayout, 2);
    rootLayout->addLayout(rightLayout, 3);

    connect(m_addProductButton, &QPushButton::clicked, this, [this]() {
        ProductDialog d(this);
        if (d.exec() == QDialog::Accepted) {
            m_catalog.addProduct(d.getProduct());
            m_storage.saveCatalog(m_catalog);
            updateList();
        }
        });

    connect(m_delProductButton, &QPushButton::clicked, this, [this]() {
        int row = m_productListView->currentRow();
        if (row >= 0) {
            auto list = m_catalog.getAllProducts();
            m_catalog.clear();
            for (int i = 0; i < list.size(); ++i) if (i != row) m_catalog.addProduct(list[i]);
            m_storage.saveCatalog(m_catalog);
            updateList();
        }
        });

    connect(m_addActivityButton, &QPushButton::clicked, this, [this]() {
        ActivityDialog d(this);
        if (d.exec() == QDialog::Accepted) {
            m_diary.addActivity(d.getActivity());
            refreshDashboard();
        }
        });

    connect(m_logFoodButton, &QPushButton::clicked, this, [this]() {
        int row = m_productListView->currentRow();
        if (row < 0) return;
        auto meal = std::make_shared<Models::Meal>();
        meal->addPortion(Models::Portion(m_catalog.getAllProducts().at(row), 200.0));
        m_diary.addMeal(meal);
        refreshDashboard();
        });

    connect(m_resetButton, &QPushButton::clicked, this, [this]() {
        m_diary.clear();
        refreshDashboard();
        });

    setWindowTitle("Calorie Counter");
    resize(950, 600);
}

void MainWindow::refreshDashboard() {
    Models::UserProfile user(m_weightSpin->value(), m_heightSpin->value(), m_ageSpin->value(), true);

    std::unique_ptr<Services::ICalorieStrategy> strategy;
    if (m_formulaCombo->currentIndex() == 0) {
        strategy = std::make_unique<Services::MifflinStrategy>();
    }
    else {
        strategy = std::make_unique<Services::HarrisBenedictStrategy>();
    }

    double bmr = strategy->calculateBMR(user);

    auto goal = Services::GoalFactory::createGoal(Services::GoalFactory::Loss);
    double target = goal->applyGoalModifier(bmr);

    m_notifier->setLimit(target);
    m_dashboard->updateStats(m_diary.totalDayCalories(), target,
        m_diary.totalDayProteins(), m_diary.totalDayFats(),
        m_diary.totalDayCarbs(), m_notifier->getLastAdvice());
}

void MainWindow::loadData() {
    m_storage.loadCatalog(m_catalog);
    updateList();
}

void MainWindow::updateList() {
    m_productListView->clear();
    for (const auto& p : m_catalog.getAllProducts()) {
        m_productListView->addItem(p->getDisplayName() + " [" + QString::number(p->caloriesPer100g(), 'f', 0) + " ккал]");
    }
}