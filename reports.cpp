#include "reports.h"
#include "ui_reports.h"

#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

reports::reports(QWidget* parent): QWidget(parent),
    ui(new Ui::reports)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
}


reports::~reports()
{
    delete ui;
    delete qmodel;
    delete insert_dialog;
    delete update_dialog;
}


void reports::on_tableRefreshButton_clicked() {
    qmodel->setQuery("select * from reports;");
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
}


void reports::on_InsertDialogOpen_clicked() {
    insert_dialog = new reports_insert();
    insert_dialog->show();
}


void reports::on_UpdateDialogOpen_clicked()
{
    update_dialog = new reports_update(selected_id);
    update_dialog->show();
}

void reports::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT delete_report(:id)");
    query.bindValue(":id", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void reports::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}
