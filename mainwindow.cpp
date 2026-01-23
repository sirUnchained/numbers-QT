#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , isCollapsed(false)
    , sidebarWidth(200)
{
    // setting window size
    setWindowTitle("number application");
    resize(800, 600);

    // setting centeral widget
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // main layout setting
    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // sidebar setting
    sidebar = new QWidget(centralWidget);
    sidebar->setMinimumWidth(50);
    sidebar->setMaximumWidth(sidebarWidth);
    sidebar->setStyleSheet("background-color:#0f0f0f");

    sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

    // menu button setting
    menuBtn = new QPushButton("☰", sidebar); // آیکون بهتر
    menuBtn->setFixedHeight(50);
    menuBtn->setStyleSheet("QPushButton {"
                           "   background-color: #34495e;"
                           "   color: white;"
                           "   font-size: 20px;"
                           "   border: none;"
                           "}"
                           "QPushButton:hover {"
                           "   background-color: #3d566e;"
                           "}");
    connect(menuBtn, &QPushButton::clicked, this, &MainWindow::toggleMenu);

    // menu list setting
    menuList = new QListWidget(sidebar);
    menuList->setStyleSheet("QListWidget {"
                            "   background-color: #2c3e50;"
                            "   color: white;"
                            "   border: none;"
                            "   font-size: 14px;"
                            "}"
                            "QListWidget::item {"
                            "   padding: 15px;"
                            "   border-bottom: 1px solid #34495e;"
                            "}"
                            "QListWidget::item:selected {"
                            "   background-color: #3498db;"
                            "}"
                            "QListWidget::item:hover {"
                            "   background-color: #34495e;"
                            "}");

    // menu items setting
    menuList->addItem("convert base");
    menuList->addItem("calculator");

    connect(menuList, &QListWidget::itemClicked, this, &MainWindow::changePage);

    // setup sidebar
    sidebarLayout->addWidget(menuBtn);
    sidebarLayout->addWidget(menuList);

    // setup stack widget
    stackedWidget = new QStackedWidget(centralWidget);
    stackedWidget->setStyleSheet("background-color: #ecf0f1;");

    // create pages
    createConvertBasePages();
    createCalculatorPage();

    // add widgets to main layer
    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);
}

void MainWindow::createCalculatorPage()
{
    QWidget *page = new QWidget();
    QFormLayout *pageForm = new QFormLayout(page);
    QLabel *firstLabelInputNumber = new QLabel(), *firstLabelInputNumberBase = new QLabel(),
           *secondLabelInputNumber = new QLabel(), *secondLabelInputNumberBase = new QLabel(),
           *operationLabel = new QLabel(), *label_result_calc = new QLabel(),
           *labelOutNumber = new QLabel();
    QLineEdit *calc_inp1 = new QLineEdit(), *calc_inp2 = new QLineEdit();
    QPushButton *calcBtn = new QPushButton();
    QSpinBox *spinFirstNumBase = new QSpinBox(), *spinSecondNumBase = new QSpinBox(),
             *spinOutNumBase = new QSpinBox();
    QComboBox *operators = new QComboBox();

    calcBtn->setText("calculate");

    operators->addItems({"*", "/", "+", "-"});

    label_result_calc->setText("Result");
    label_result_calc->setAlignment(Qt::AlignCenter);

    firstLabelInputNumber->setText("first number: ");
    firstLabelInputNumberBase->setText("first number base: ");
    secondLabelInputNumber->setText("second number: ");
    secondLabelInputNumberBase->setText("second number base: ");
    operationLabel->setText("calculator operations: ");
    labelOutNumber->setText("output number base: ");

    spinFirstNumBase->setMaximum(16);
    spinFirstNumBase->setMinimum(2);
    spinSecondNumBase->setMaximum(16);
    spinSecondNumBase->setMinimum(2);
    spinOutNumBase->setMaximum(16);
    spinOutNumBase->setMinimum(2);

    pageForm->addRow(firstLabelInputNumber, calc_inp1);
    pageForm->addRow(firstLabelInputNumberBase, spinFirstNumBase);
    pageForm->addRow(secondLabelInputNumber, calc_inp2);
    pageForm->addRow(secondLabelInputNumberBase, spinSecondNumBase);
    pageForm->addRow(labelOutNumber, spinOutNumBase);
    pageForm->addRow(operationLabel, operators);
    pageForm->addRow(calcBtn, label_result_calc);

    QObject::connect(calcBtn, &QPushButton::clicked, this, [=] {
        QString operation = operators->currentText();

        int num1_base = spinFirstNumBase->value();
        int num2_base = spinSecondNumBase->value();
        int out_base = spinOutNumBase->value();

        bool ok = true;
        int num1 = calc_inp1->text().toInt(&ok, num1_base);
        int num2 = calc_inp2->text().toInt(&ok, num2_base);

        if (!ok) {
            label_result_calc->setText("Error, check fields numbers and bases");
            return;
        }

        if (operation == "+") {
            int result = num1 + num2;
            QString output_num = QString::number(result, out_base).toUpper();
            label_result_calc->setText(output_num);
        } else if (operation == "-") {
            int result = num1 - num2;
            QString output_num = QString::number(result, out_base).toUpper();
            label_result_calc->setText(output_num);
        } else if (operation == "*") {
            int result = num1 * num2;
            QString output_num = QString::number(result, out_base).toUpper();
            label_result_calc->setText(output_num);
        } else if (operation == "/") {
            if (num2 == 0) {
                label_result_calc->setText("Warning, division by zero");
                return;
            }

            int result = num1 / num2;
            QString output_num = QString::number(result, out_base).toUpper();
            label_result_calc->setText(output_num);
        }
    });

    stackedWidget->addWidget(page);
}

void MainWindow::createConvertBasePages()
{
    QWidget *page = new QWidget();
    QFormLayout *formLayout = new QFormLayout(page);
    QLineEdit *input_number = new QLineEdit();
    QLabel *label_input_number = new QLabel(), *label_input_number_base = new QLabel(),
           *label_target_number_base = new QLabel(), *label_result = new QLabel();
    QPushButton *calc_btn = new QPushButton();
    QSpinBox *spin_target_base = new QSpinBox(), *spin_input_base = new QSpinBox();

    calc_btn->setText("calculate");

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

    connect(calc_btn, &QPushButton::clicked, this, [=]() {
        QString user_number = input_number->text();
        int input_base = spin_input_base->value();
        int output_base = spin_target_base->value();

        bool ok = false;
        int input_num = user_number.toInt(&ok, input_base);
        if (!ok) {
            label_result->setText("Error: Invalid number for given base");
            return;
        }

        QString output_num = QString::number(input_num, output_base).toUpper();
        label_result->setText(output_num);
    });

    stackedWidget->addWidget(page);
}

void MainWindow::toggleMenu()
{
    if (isCollapsed) {
        sidebar->setFixedWidth(sidebarWidth);
        menuList->setVisible(true);
        isCollapsed = false;
    } else {
        sidebar->setFixedWidth(50);
        menuList->setVisible(false);
        isCollapsed = true;
    }
}

void MainWindow::changePage(QListWidgetItem *item)
{
    // change page by selected item
    int index = menuList->row(item);
    stackedWidget->setCurrentIndex(index);

    if (isCollapsed) {
        toggleMenu();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
