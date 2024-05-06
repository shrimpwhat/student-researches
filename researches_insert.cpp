#include "researches_insert.h"
#include "ui_researches_insert.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

researches_insert::researches_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::researches_insert)
{
    ui->setupUi(this);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT id, code FROM departments");
    while (queryCombo->next())
        ui->departmentCombo->addItem(queryCombo->value(1).toString(), queryCombo->value(0));
    ui->departmentCombo->setCurrentIndex(-1);

    queryCombo->exec("SELECT id, full_name FROM supervisors");
    while (queryCombo->next())
        ui->supervisorCombo->addItem(queryCombo->value(1).toString(), queryCombo->value(0));
    ui->supervisorCombo->setCurrentIndex(-1);
}

researches_insert::~researches_insert()
{
    delete ui;
}

void researches_insert::on_InsertSubmit_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT add_research(:name, :department, :field, :supervisor, :url)");
    query.bindValue(":name", ui->NameInput->text());
    query.bindValue(":field", ui->FieldInput->text());
    query.bindValue(":url", ui->URLInput->text());
    query.bindValue(":department", ui->departmentCombo->currentData());
    query.bindValue(":supervisor", ui->supervisorCombo->currentData());
    if (query.exec())
        close();
    else
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
}
