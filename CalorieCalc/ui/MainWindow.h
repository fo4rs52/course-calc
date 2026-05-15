#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <memory>

#include "services/ProductCatalog.h"
#include "services/StorageManager.h"
#include "services/NutritionDiary.h"
#include "services/NotificationManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

private:
    void setupUi();
    void loadData();
    void updateList();
    void handleCalculation(); 

    QWidget* m_centralWidget;
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;
    QListWidget* m_productListView;
    QPushButton* m_addProductButton;
    QPushButton* m_calcButton;

    Services::ProductCatalog m_catalog;
    Services::StorageManager m_storage;
    Services::NutritionDiary m_diary;
    std::shared_ptr<Services::NotificationManager> m_notifier;
};

#endif