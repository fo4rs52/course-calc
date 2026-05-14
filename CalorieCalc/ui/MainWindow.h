#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <memory>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() = default;

private:
    void setupUi();

    void runModelTest();

    QWidget* m_centralWidget;
    QVBoxLayout* m_mainLayout;
    QLabel* m_infoLabel;
    QPushButton* m_testButton;
};

#endif