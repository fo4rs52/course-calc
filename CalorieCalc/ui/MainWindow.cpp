#include "MainWindow.h"
#include "ProductDialog.h" 
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
}

void MainWindow::setupUi() {
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    m_mainLayout = new QVBoxLayout(m_centralWidget);

    m_titleLabel = new QLabel("Доступные продукты:", this);
    m_titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    m_productListView = new QListWidget(this);

    m_testButton = new QPushButton("Добавить свой продукт", this);
    m_testButton->setMinimumHeight(40);

    m_mainLayout->addWidget(m_titleLabel);
    m_mainLayout->addWidget(m_productListView);
    m_mainLayout->addWidget(m_testButton);

    setWindowTitle("Калькулятор Калорий - Каталог");
    resize(450, 600);
}

void MainWindow::loadData() {
    if (!m_storage.loadCatalog(m_catalog)) {
        m_catalog.addProduct(std::make_shared<Models::Product>("Куриная грудка", 23.6, 1.9, 0.4));
        m_catalog.addProduct(std::make_shared<Models::Product>("Гречка (сухая)", 12.6, 3.3, 62.1));
        m_storage.saveCatalog(m_catalog);
    }
    updateList();
}

void MainWindow::updateList() {
    m_productListView->clear();
    for (const auto& product : m_catalog.getAllProducts()) {
        QString itemText = QString("%1 | Белки: %2 | Жиры: %3 | Углеводы: %4 | %5 ккал/100г")
            .arg(product->getDisplayName())
            .arg(product->proteins(), 0, 'f', 1)
            .arg(product->fats(), 0, 'f', 1)
            .arg(product->carbs(), 0, 'f', 1)
            .arg(product->caloriesPer100g(), 0, 'f', 1);
        m_productListView->addItem(itemText);
    }
}