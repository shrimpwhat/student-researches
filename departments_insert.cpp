#include "departments_insert.h"
#include "ui_departments_insert.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

DepartmentsInsert::DepartmentsInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentsInsert)
{
    ui->setupUi(this);
}

DepartmentsInsert::~DepartmentsInsert()
{
    delete ui;
}

void DepartmentsInsert::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT add_department(:code, :name)");
    query.bindValue(":code", ui->CodeInput->text());
    query.bindValue(":name", ui->NameInput->text());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}


