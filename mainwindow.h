#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QStackedWidget>
#include <QtDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString calculate_result(QString number, int input_base, int output_base);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *centralWidget;

    // Main page widgets
    QFormLayout *formLayout;
    QLineEdit *input_number;
    QLabel *label_input_number, *label_input_number_base, *label_target_number_base, *label_result;
    QPushButton *calc_btn;
    QSpinBox *spin_target_base, *spin_input_base;

    // Menu widgets
    QWidget *menuWidget;
    QVBoxLayout *menuLayout;
    QPushButton *menuButton;
    QPushButton *convertBasePageBtn;

    // Page container
    QStackedWidget *stackedWidget;

    // Pages
    QWidget *convertBasePage;
    QWidget *calculatorPage;

    void calculate_resultt();
    void setupMenu();
};
#endif // MAINWINDOW_H
