#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , centralWidget(new QWidget)
    , formLayout(new QFormLayout)
    , input_number(new QLineEdit)
    , label_input_number(new QLabel)
    , label_input_number_base(new QLabel)
    , label_target_number_base(new QLabel)
    , label_result(new QLabel)
    , calc_btn(new QPushButton)
    , spin_target_base(new QSpinBox)
    , spin_input_base(new QSpinBox)
    , menuButton(new QPushButton)
{
    ui->setupUi(this);

    setWindowTitle("number application");
    setCentralWidget(centralWidget);
    centralWidget->setLayout(formLayout);

    calc_btn->setText("calculate");
    menuButton->setText("Menu");
    menuButton->setFixedSize(40, 40);
    menuButton->setStyleSheet("font-size: 20px;");

    label_input_number->setText("enter your number :");
    label_input_number_base->setText("input number base :");
    label_target_number_base->setText("target number base :");
    label_result->setText("result");
    label_result->setAlignment(Qt::AlignCenter);

    spin_input_base->setMaximum(16);
    spin_input_base->setMinimum(2);
    spin_target_base->setMaximum(16);
    spin_target_base->setMinimum(2);

    formLayout->addRow(label_input_number, input_number);
    formLayout->addRow(label_input_number_base, spin_input_base);
    formLayout->addRow(label_target_number_base, spin_target_base);
    formLayout->addRow(calc_btn, label_result);

    QObject::connect(calc_btn, &QPushButton::clicked, this, &MainWindow::calculate_resultt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_resultt()
{
    QString user_number = input_number->text();
    int input_base = spin_input_base->value();
    int output_base = spin_target_base->value();

    bool ok = false;
    int input_num = user_number.toInt(&ok, input_base);
    if (!ok) {
        label_result->setText("Error, check input base is same as what you typed");
        return;
    }

    QString output_num = QString::number(input_num, output_base);
    label_result->setText(output_num);
}

void MainWindow::setupMenu()
{
    menuWidget = new QWidget(this);
    menuWidget->setFixedWidth(200);
    menuWidget->setStyleSheet("background-color: #f0f0f0;");

    menuLayout = new QVBoxLayout(menuWidget);

    convertBasePageBtn = new QPushButton("🏠 Convert Numbers Base", this);

    // Style menu buttons
    QString buttonStyle = "QPushButton {"
                          "text-align: left;"
                          "padding: 15px;"
                          "font-size: 14px;"
                          "border: none;"
                          "border-radius: 5px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #e0e0e0;"
                          "}";

    convertBasePageBtn->setStyleSheet(buttonStyle);

    menuLayout->addWidget(convertBasePageBtn);
    menuLayout->addStretch();
}
