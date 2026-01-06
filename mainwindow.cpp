#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calc_btn_clicked()
{
    int input_base = 0, output_base = 0, result = 0;
    QString user_number;

    user_number = ui->user_input->text();
    input_base = ui->input_base->value();
    output_base = ui->output_base->value();

    ui->result->setText(calculate_result(user_number, input_base, output_base));
}

QString MainWindow::calculate_result(QString number, int input_base, int output_base)
{
    bool ok = false;
    int input_num = number.toInt(&ok, input_base);
    if(!ok) return QString("Error, check input base is same as what you typed");

    QString output_num = QString::number(input_num, output_base);
    return output_num;
}

