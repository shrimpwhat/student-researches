#include "researches.h"
#include "ui_researches.h"

#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>


researches::researches(QWidget* parent): QWidget(parent),
    ui(new Ui::researches)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
}


researches::~researches()
{
    delete ui;
    delete qmodel;
    delete insert_dialog;
    delete update_dialog;
}


void researches::on_tableRefreshButton_clicked() {
    qmodel->setQuery("select id, title, field, url,"
                     "(select code from departments where department = departments.id) as department, "
                     "(select full_name from supervisors where supervisors.id = supervisor) as supervisor,"
                     "funding_sum from researches;");
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
}


void researches::on_InsertDialogOpen_clicked() {
    insert_dialog = new researches_insert();
    insert_dialog->show();
}


void researches::on_UpdateDialogOpen_clicked()
{
    update_dialog = new researches_update(selected_id);
    update_dialog->show();
}

void researches::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT delete_research(:id)");
    query.bindValue(":id", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void researches::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}
