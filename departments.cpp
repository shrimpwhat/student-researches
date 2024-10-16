#include "departments.h"
#include "ui_departments.h"
#include "departments_update.h"
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>


departments::departments(QWidget* parent): QWidget(parent),
    ui(new Ui::departments)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
}


departments::~departments()
{
    delete ui;
    delete qmodel;
    delete insert_dialog;
    delete update_dialog;
}


void departments::on_tableRefreshButton_clicked() {
    qmodel->setQuery("SELECT * FROM departments");
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
}


void departments::on_InsertDialogOpen_clicked() {
    insert_dialog = new DepartmentsInsert();
    insert_dialog->show();
}


void departments::on_UpdateDialogOpen_clicked()
{
    update_dialog = new DepartmentsUpdate(selected_id);
    update_dialog->show();
}

void departments::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT delete_department(:id)");
    query.bindValue(":id", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void departments::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}
