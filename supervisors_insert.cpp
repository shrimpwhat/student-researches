#include "supervisors_insert.h"
#include "ui_supervisors_insert.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

supervisors_insert::supervisors_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::supervisors_insert)
{
    ui->setupUi(this);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT id, code FROM departments");
    while (queryCombo->next())
        ui->comboBox->addItem(queryCombo->value(1).toString(), queryCombo->value(0).toUInt());
    ui->comboBox->setCurrentIndex(-1);
}

supervisors_insert::~supervisors_insert()
{
    delete ui;
}

void supervisors_insert::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT add_supervisor(:name, :email, :phone, :department)");
    query.bindValue(":name", ui->NameInput->text());
    query.bindValue(":email", ui->EmailInput->text());
    query.bindValue(":phone", ui->PhoneInput->text());
    query.bindValue(":department", ui->comboBox->currentData().toString());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
