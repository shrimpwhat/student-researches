#include "reports_insert.h"
#include "ui_reports_insert.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

reports_insert::reports_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reports_insert)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

reports_insert::~reports_insert()
{
    delete ui;
}

void reports_insert::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT add_report(:name, :description, :date)");
    query.bindValue(":name", ui->NameInput->text());
    query.bindValue(":description", ui->DescriptionInput->text());
    query.bindValue(":date", ui->dateEdit->date());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
