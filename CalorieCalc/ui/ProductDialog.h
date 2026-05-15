#ifndef PRODUCTDIALOG_H
#define PRODUCTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <memory>
#include "models/Product.h"

class ProductDialog : public QDialog {
    Q_OBJECT

public:
    explicit ProductDialog(QWidget* parent = nullptr);

    std::shared_ptr<Models::Product> getProduct() const;

private:
    void setupUi();

    QLineEdit* m_nameEdit;
    QDoubleSpinBox* m_proteinSpin;
    QDoubleSpinBox* m_fatSpin;
    QDoubleSpinBox* m_carbSpin;
    QPushButton* m_saveButton;
    QPushButton* m_cancelButton;
};

#endif