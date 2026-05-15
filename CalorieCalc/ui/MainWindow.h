#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include "services/ProductCatalog.h"
#include "services/StorageManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void setupUi();
    void loadData();
    void updateList();

    QWidget* m_centralWidget;
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;
    QListWidget* m_productListView;
    QPushButton* m_testButton;

    QPushButton* m_calcButton;

    Services::ProductCatalog m_catalog;
    Services::StorageManager m_storage;
};

#endif