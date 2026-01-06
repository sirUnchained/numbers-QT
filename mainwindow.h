#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_calc_btn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
