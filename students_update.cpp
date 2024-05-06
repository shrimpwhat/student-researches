#include "students_update.h"
#include "ui_students_update.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

students_update::students_update(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::students_update)
{
    ui->setupUi(this);
    this->id = id;
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT * FROM students WHERE id = :id");

    QSqlQuery queryCombo = QSqlQuery();
    queryCombo.exec("SELECT id, code FROM departments");

    query.bindValue(":id", id);
    query.exec();
    query.next();
    ui->NameInput->setText(query.value(1).toString());
    ui->EmailInput->setText(query.value(2).toString());
    ui->PhoneInput->setText(query.value(3).toString());

    while (queryCombo.next())
        ui->comboBox->addItem(queryCombo.value(1).toString(), queryCombo.value(0).toUInt());
    int index = ui->comboBox->findData(query.value(4));
    ui->comboBox->setCurrentIndex(index);

}

students_update::~students_update()
{
    delete ui;
}

void students_update::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT edit_student(:id, :name, :email, :phone, :department)");
    query.bindValue(":id", id);
    query.bindValue(":name", ui->NameInput->text());
    query.bindValue(":email", ui->EmailInput->text());
    query.bindValue(":phone", ui->PhoneInput->text());
    query.bindValue(":department", ui->comboBox->currentData().toString());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
