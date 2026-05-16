#include "ActivityDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ActivityDialog::ActivityDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Добавить активность");
    auto layout = new QVBoxLayout(this);
    auto form = new QFormLayout();

    m_typeEdit = new QLineEdit("Бег", this);
    m_kcalSpin = new QDoubleSpinBox(this);
    m_kcalSpin->setRange(1, 2000);
    m_kcalSpin->setValue(200);
    m_kcalSpin->setSuffix(" ккал");

    form->addRow("Что делали:", m_typeEdit);
    form->addRow("Сожжено:", m_kcalSpin);
    layout->addLayout(form);

    auto buttons = new QHBoxLayout();
    auto save = new QPushButton("Добавить", this);
    auto cancel = new QPushButton("Отмена", this);
    buttons->addWidget(save);
    buttons->addWidget(cancel);
    layout->addLayout(buttons);

    connect(save, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
}

std::shared_ptr<Models::ActivityRecord> ActivityDialog::getActivity() const {
    return std::make_shared<Models::ActivityRecord>(m_typeEdit->text(), m_kcalSpin->value());
}