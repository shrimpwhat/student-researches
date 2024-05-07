#include "funding_update.h"
#include "ui_funding_update.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

funding_update::funding_update(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::funding_update)
{
    ui->setupUi(this);
    this->id = id;
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT * FROM funding WHERE id = :id");

    QSqlQuery queryCombo = QSqlQuery();
    queryCombo.exec("SELECT id, title FROM researches");

    query.bindValue(":id", id);
    query.exec();
    query.next();
    ui->SourceInput->setText(query.value(1).toString());
    ui->AmountInput->setText(query.value(3).toString());
    ui->dateEdit->setDate(query.value(4).toDate());

    while (queryCombo.next())
        ui->comboBox->addItem(queryCombo.value(1).toString(), queryCombo.value(0));
    int index = ui->comboBox->findData(query.value(2));
    ui->comboBox->setCurrentIndex(index);

}

funding_update::~funding_update()
{
    delete ui;
}

void funding_update::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT edit_funding(:id, :source, :research, :amount, :date)");
    query.bindValue(":id", id);
    query.bindValue(":source", ui->SourceInput->text());
    query.bindValue(":research", ui->comboBox->currentData());
    query.bindValue(":amount", ui->AmountInput->text());
    query.bindValue(":date", ui->dateEdit->date());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
