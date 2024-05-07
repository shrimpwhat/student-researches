#include "reports_update.h"
#include "ui_reports_update.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

reports_update::reports_update(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reports_update)
{
    ui->setupUi(this);
    this->id = id;
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT * FROM reports WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    ui->NameInput->setText(query.value(1).toString());
    ui->DescriptionInput->setText(query.value(2).toString());
    ui->dateEdit->setDate(query.value(3).toDate());
}

reports_update::~reports_update()
{
    delete ui;
}

void reports_update::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT edit_report(:id, :name, :description, :date)");
    query.bindValue(":id", id);
    query.bindValue(":name", ui->NameInput->text());
    query.bindValue(":description", ui->DescriptionInput->text());
    query.bindValue(":date", ui->dateEdit->date());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
