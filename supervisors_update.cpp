#include "supervisors_update.h"
#include "ui_supervisors_update.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

supervisors_update::supervisors_update(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::supervisors_update)
{
    ui->setupUi(this);
    this->id = id;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM supervisors WHERE id = :id");

    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT id, code FROM departments");

    query->bindValue(":id", id);
    query->exec();
    query->next();
    ui->NameInput->setText(query->value(1).toString());
    ui->EmailInput->setText(query->value(2).toString());
    ui->PhoneInput->setText(query->value(3).toString());

    while (queryCombo->next())
        ui->comboBox->addItem(queryCombo->value(1).toString(), queryCombo->value(0).toUInt());
    int index = ui->comboBox->findData(query->value(4));
    ui->comboBox->setCurrentIndex(index);

}

supervisors_update::~supervisors_update()
{
    delete ui;
}

void supervisors_update::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT edit_supervisor(:id, :name, :email, :phone, :department)");
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

