#include "students.h"
#include "ui_students.h"
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>


students::students(QWidget* parent): QWidget(parent),
    ui(new Ui::students)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
}


students::~students()
{
    delete ui;
    delete qmodel;
    delete insert_dialog;
    delete update_dialog;
    delete researches;
}


void students::on_tableRefreshButton_clicked() {
    qmodel->setQuery("select id, full_name, email, phone, (select code from departments where department = departments.id) as department from students;");
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
}


void students::on_InsertDialogOpen_clicked() {
    insert_dialog = new students_insert();
    insert_dialog->show();
}


void students::on_UpdateDialogOpen_clicked()
{
    update_dialog = new students_update(selected_id);
    update_dialog->show();
}

void students::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT delete_student(:id)");
    query.bindValue(":id", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void students::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}

void students::on_showResearches_clicked()
{
    if (selected_id) {
        researches = new students_researches(selected_id);
        researches->show();
    }
}

