#include "supervisors.h"
#include "ui_supervisors.h"
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>


supervisors::supervisors(QWidget* parent): QWidget(parent),
    ui(new Ui::supervisors)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
}


supervisors::~supervisors()
{
    delete ui;
    delete qmodel;
    delete insert_dialog;
    delete update_dialog;
}


void supervisors::on_tableRefreshButton_clicked() {
    qmodel->setQuery("select id, full_name, email, phone, (select code from departments where department = departments.id) as department, research_count from supervisors;");
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
}


void supervisors::on_InsertDialogOpen_clicked() {
    insert_dialog = new supervisors_insert();
    insert_dialog->show();
}


void supervisors::on_UpdateDialogOpen_clicked()
{
    update_dialog = new supervisors_update(selected_id);
    update_dialog->show();
}

void supervisors::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT delete_supervisor(:id)");
    query.bindValue(":id", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void supervisors::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}
