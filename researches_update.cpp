#include "researches_update.h"
#include "ui_researches_update.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

researches_update::researches_update(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::researches_update)
{
    ui->setupUi(this);
    this->id = id;
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT * FROM researches WHERE id = :id");
    query.bindValue(":id", id);

    QSqlQuery queryCombo = QSqlQuery();
    queryCombo.exec("SELECT id, code FROM departments");

    query.exec();
    query.next();
    ui->NameInput->setText(query.value(1).toString());
    ui->FieldInput->setText(query.value(3).toString());
    ui->URLInput->setText(query.value(5).toString());

    while (queryCombo.next())
        ui->departmentCombo->addItem(queryCombo.value(1).toString(), queryCombo.value(0));
    int index = ui->departmentCombo->findData(query.value(2));
    ui->departmentCombo->setCurrentIndex(index);

    queryCombo.exec("SELECT id, full_name FROM supervisors");
    while (queryCombo.next())
        ui->supervisorCombo->addItem(queryCombo.value(1).toString(), queryCombo.value(0));
    index = ui->supervisorCombo->findData(query.value(4));
    ui->supervisorCombo->setCurrentIndex(index);

}

researches_update::~researches_update()
{
    delete ui;
}

void researches_update::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("CALL edit_research(:id, :title, :department, :field, :supervisor, :url)");
    query.bindValue(":id", id);
    query.bindValue(":title", ui->NameInput->text());
    query.bindValue(":department", ui->departmentCombo->currentData());
    query.bindValue(":field", ui->FieldInput->text());
    query.bindValue(":supervisor", ui->supervisorCombo->currentData());
    query.bindValue(":url", ui->URLInput->text());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
