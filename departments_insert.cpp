#include "departments_insert.h"
#include "ui_departments_insert.h"
#include <QSqlQuery>

DepartmentsInsert::DepartmentsInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentsInsert)
{
    ui->setupUi(this);
//    QSqlQuery *queryCombo = new QSqlQuery();
//    queryCombo->exec("SELECT name FROM category");
//    while (queryCombo->next())
//    {
//        ui->comboBox->addItem(queryCombo->value(0).toString());
//    }
}

DepartmentsInsert::~DepartmentsInsert()
{
    delete ui;
}

void DepartmentsInsert::on_InsertSubmit_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT add_department(:code, :name)");
    query->bindValue(":code", ui->CodeInput->text());
    query->bindValue(":name", ui->NameInput->text());
    query->exec();
    close();
}


