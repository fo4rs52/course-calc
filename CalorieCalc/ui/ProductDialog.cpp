#include "ProductDialog.h"
#include <QHBoxLayout>
#include <QMessageBox>

ProductDialog::ProductDialog(QWidget* parent) : QDialog(parent) {
    setupUi();

    connect(m_saveButton, &QPushButton::clicked, this, [this]() {
        if (m_nameEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите название продукта!");
            return;
        }
        accept(); 
        });

    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void ProductDialog::setupUi() {
    setWindowTitle("Новый продукт");
    setMinimumWidth(300);

    auto mainLayout = new QVBoxLayout(this);
    auto formLayout = new QFormLayout();

    m_nameEdit = new QLineEdit(this);

    auto setupSpinBox = [this]() {
        auto spin = new QDoubleSpinBox(this);
        spin->setRange(0.0, 100.0);
        spin->setDecimals(1);
        spin->setSuffix(" г");
        return spin;
        };

    m_proteinSpin = setupSpinBox();
    m_fatSpin = setupSpinBox();
    m_carbSpin = setupSpinBox();

    formLayout->addRow("Название:", m_nameEdit);
    formLayout->addRow("Белки (на 100г):", m_proteinSpin);
    formLayout->addRow("Жиры (на 100г):", m_fatSpin);
    formLayout->addRow("Углеводы (на 100г):", m_carbSpin);

    mainLayout->addLayout(formLayout);

    auto buttonLayout = new QHBoxLayout();
    m_saveButton = new QPushButton("Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);

    mainLayout->addLayout(buttonLayout);
}

std::shared_ptr<Models::Product> ProductDialog::getProduct() const {
    return std::make_shared<Models::Product>(
        m_nameEdit->text().trimmed(),
        m_proteinSpin->value(),
        m_fatSpin->value(),
        m_carbSpin->value()
    );
}