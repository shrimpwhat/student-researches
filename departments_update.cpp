#include "departments_update.h"
#include "ui_departments_update.h"

#include <QFileDialog>
#include <QSqlQuery>

DepartmentsUpdate::DepartmentsUpdate(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentsUpdate)
{
    ui->setupUi(this);
    this->id = id;
}

DepartmentsUpdate::~DepartmentsUpdate()
{
    delete ui;
}

void DepartmentsUpdate::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE product SET name = :name, catID = :category, ImagePath = :img, prodDate = :date WHERE ID = :ID");
    query->bindValue(":ID", tempID);
    query->bindValue(":name",ui->lineEdit->text());
    query->bindValue(":category",ui->comboBox->currentIndex()+1);
    query->bindValue(":date", ui->dateEdit->text());
    if(query->exec())
    {
        close();
    }
}

void DepartmentsUpdate::sendingID(int aa)
{
    tempID = aa;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, catID, ImagePath, prodDate FROM product WHERE ID = ?");
    query->bindValue(0,aa);
    if (query->exec())
    {
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        ui->comboBox->setCurrentIndex(query->value(1).toInt()-1);
        ui->dateEdit->setDate(QDate::fromString(query->value(3).toString(), "yyyy-MM-dd"));
    }
}

