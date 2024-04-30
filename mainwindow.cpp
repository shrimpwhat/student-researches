#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "departments.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->Router->hide();

    login = new Login(this);
    login->setParent(ui->LoginBox);
    connect(login, &Login::on_DBConnected, this, &MainWindow::on_DBConnected);

    departments = new DepartmentsView(ui->Router);
    ui->Router->addTab(departments, "Кафедры");
}

MainWindow::~MainWindow() {
    delete ui;
    delete login;
    delete departments;
    delete qmodel;
}

void MainWindow::on_DBConnected() {
    ui->LoginBox->hide();
    ui->Router->show();
//    QSqlQuery *queryCombo = new QSqlQuery();
//    queryCombo->exec("SELECT name FROM category");
//    while (queryCombo->next())
//    {
//        ui->comboBox->addItem(queryCombo->value(0).toString());
//    }
//    MainWindow::on_tableRefreshButton_clicked();
}
