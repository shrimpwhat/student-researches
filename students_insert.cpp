#include "students_insert.h"
#include "ui_students_insert.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

students_insert::students_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::students_insert)
{
    ui->setupUi(this);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT id, code FROM departments");
    while (queryCombo->next()) {
        ui->comboBox->addItem(queryCombo->value(1).toString(), queryCombo->value(0));
    }
    ui->comboBox->setCurrentIndex(-1);
}

students_insert::~students_insert()
{
    delete ui;
}

void students_insert::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT add_student(:name, :email, :phone, :department)");
    query.bindValue(":name", ui->NameInput->text());
    query.bindValue(":email", ui->EmailInput->text());
    query.bindValue(":phone", ui->PhoneInput->text());
    query.bindValue(":department", ui->comboBox->currentData().toString());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
