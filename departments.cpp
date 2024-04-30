#include "departments.h"
#include "ui_departments.h"
#include "departments_update.h"
#include <QMenu>
#include <QDebug>


DepartmentsView::DepartmentsView(QWidget* parent): QWidget(parent),
    ui(new Ui::DepartmentsView)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
}


DepartmentsView::~DepartmentsView()
{
    delete ui;
}


void DepartmentsView::on_tableRefreshButton_clicked() {
    fl = 1;
    qmodel->setQuery("SELECT * FROM departments");
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
}


void DepartmentsView::on_InsertDialogOpen_clicked() {
    insert_dialog = new DepartmentsInsert();
    insert_dialog->show();
}

void DepartmentsView::on_UpdateDialogOpen_clicked()
{
    update_dialog = new DepartmentsUpdate(selected_id);
    update_dialog->show();
}


void DepartmentsView::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}

void DepartmentsView::on_DeleteSubmit_clicked() {
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT delete_department(:ID)");
    query->bindValue(":ID", selected_id);
    query->exec();
    DepartmentsView::on_tableRefreshButton_clicked();
}

void DepartmentsView::DelRecAction() {
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID = :ID");
    query->bindValue(":ID", selected_id);
    query->exec();
    DepartmentsView::on_tableRefreshButton_clicked();
}

void DepartmentsView::ModRecAction() {
    update_dialog = new DepartmentsUpdate();
    connect(this, SIGNAL(sendID(int)), update_dialog, SLOT(sendingID(int)));
    emit sendID(selected_id);
    update_dialog->show();
    disconnect(this, SIGNAL(sendID(int)), update_dialog, SLOT(sendingID(int)));
}



