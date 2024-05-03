#include "departments_update.h"
#include "ui_departments_update.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

DepartmentsUpdate::DepartmentsUpdate(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentsUpdate)
{
    ui->setupUi(this);
    this->id = id;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM departments WHERE id = :id");
    query->bindValue(":id", id);
    query->exec();
    query->next();
    ui->CodeInput->setText(query->value(1).toString());
    ui->NameInput->setText(query->value(2).toString());
}

DepartmentsUpdate::~DepartmentsUpdate()
{
    delete ui;
}

void DepartmentsUpdate::on_pushButton_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT edit_department(:id, :code, :name)");
    query.bindValue(":id", id);
    query.bindValue(":code", ui->CodeInput->text());
    query.bindValue(":name", ui->NameInput->text());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}

