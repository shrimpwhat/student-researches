#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "departments.h"
#include "supervisors.h"
#include "students.h"
#include "researches.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->Router->hide();

    login = new Login(this);
    login->setParent(ui->LoginBox);
    connect(login, &Login::on_DBConnected, this, &MainWindow::on_DBConnected);

    auto departments_view = new departments(ui->Router);
    ui->Router->addTab(departments_view, "Кафедры");

    auto supervisors_view = new supervisors(ui->Router);
    ui->Router->addTab(supervisors_view, "Руководители");

    auto students_view = new students(ui->Router);
    ui->Router->addTab(students_view, "Студенты");

    auto researches_view = new researches(ui->Router);
    ui->Router->addTab(researches_view, "Исследовательские работы");
}

MainWindow::~MainWindow() {
    delete ui;
    delete login;
    delete qmodel;
}

void MainWindow::on_DBConnected() {
    ui->LoginBox->hide();
    ui->Router->show();
}
