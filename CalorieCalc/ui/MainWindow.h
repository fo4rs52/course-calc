#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <memory>

#include "services/ProductCatalog.h"
#include "services/StorageManager.h"
#include "services/NutritionDiary.h"
#include "services/NotificationManager.h"
#include "ui/DashboardWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void setupUi();
    void loadData();
    void updateList();
    void refreshDashboard();

    QWidget* m_centralWidget;
    QListWidget* m_productListView;
    QPushButton* m_addProductButton;
    QPushButton* m_delProductButton;
    QPushButton* m_logFoodButton;
    QPushButton* m_addActivityButton;
    QPushButton* m_resetButton;

    QDoubleSpinBox* m_weightSpin;
    QDoubleSpinBox* m_heightSpin;
    QSpinBox* m_ageSpin;
    QComboBox* m_formulaCombo;
    DashboardWidget* m_dashboard;

    Services::ProductCatalog m_catalog;
    Services::StorageManager m_storage;
    Services::NutritionDiary m_diary;
    std::shared_ptr<Services::NotificationManager> m_notifier;
};

#endif