#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QStackedWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // main widget
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;

    // Menu widgets
    QWidget *sidebar;
    QVBoxLayout *sidebarLayout;
    QListWidget *menuList;
    QPushButton *menuBtn;

    // Page container
    QStackedWidget *stackedWidget;

    // menu status
    bool isCollapsed;
    int sidebarWidth;

    void createCalculatorPage();
    void createConvertBasePages();
    void changePage(QListWidgetItem *item);
};
#endif // MAINWINDOW_H
