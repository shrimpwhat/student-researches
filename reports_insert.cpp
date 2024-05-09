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
    QSqlQuery queryCombo = QSqlQuery();
    queryCombo.exec("SELECT id, title FROM researches");
    while (queryCombo.next())
        ui->comboBox->addItem(queryCombo.value(1).toString(), queryCombo.value(0));
    ui->comboBox->setCurrentIndex(-1);
    ui->dateEdit->setDate(QDate::currentDate());
}

reports_insert::~reports_insert()
{
    delete ui;
}

void reports_insert::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT add_report(:name, :date, :research)");
    query.bindValue(":name", ui->NameInput->text());
    query.bindValue(":date", ui->dateEdit->date());
    query.bindValue(":research", ui->comboBox->currentData());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
