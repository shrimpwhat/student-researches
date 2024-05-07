#include "funding_insert.h"
#include "ui_funding_insert.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

funding_insert::funding_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::funding_insert)
{
    ui->setupUi(this);
    QSqlQuery queryCombo = QSqlQuery();
    queryCombo.exec("SELECT id, title FROM researches");
    while (queryCombo.next())
        ui->comboBox->addItem(queryCombo.value(1).toString(), queryCombo.value(0));
    ui->comboBox->setCurrentIndex(-1);
    ui->dateEdit->setDate(QDate::currentDate());
}

funding_insert::~funding_insert()
{
    delete ui;
}

void funding_insert::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT add_funding(:source, :research, :amount, :date)");
    query.bindValue(":source", ui->SourceInput->text());
    query.bindValue(":research", ui->comboBox->currentData());
    query.bindValue(":amount", ui->AmountInput->text());
    query.bindValue(":date", ui->dateEdit->date());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
