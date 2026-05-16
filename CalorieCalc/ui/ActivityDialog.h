#ifndef ACTIVITYDIALOG_H
#define ACTIVITYDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include "models/ActivityRecord.h"
#include <memory>

class ActivityDialog : public QDialog {
    Q_OBJECT
public:
    explicit ActivityDialog(QWidget* parent = nullptr);
    std::shared_ptr<Models::ActivityRecord> getActivity() const;

private:
    QLineEdit* m_typeEdit;
    QDoubleSpinBox* m_kcalSpin;
};

#endif