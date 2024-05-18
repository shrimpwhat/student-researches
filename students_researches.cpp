#include "students_researches.h"
#include "ui_students_researches.h"
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>


students_researches::students_researches(int student_id, QWidget* parent): QWidget(parent),
    ui(new Ui::students_researches)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
    this->student_id = student_id;
    update_comboBox();
}


students_researches::~students_researches()
{
    delete ui;
    delete qmodel;
}


void students_researches::on_tableRefreshButton_clicked() {
    qmodel->setQuery(QString("select id, title, field, url,"
                             "(select code from departments where department = departments.id) as department, "
                             "(select full_name from supervisors where supervisors.id = supervisor) as supervisor,"
                             "funding_sum, report_count from researches where id in (select research_id from students_researches where student_id = %1);").arg(student_id));
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
    this->update_comboBox();
}


void students_researches::update_comboBox() {
    ui->comboBox->clear();
    QSqlQuery query = QSqlQuery();
    query.prepare("select id, title from researches where id not in (select research_id from students_researches where student_id = :id);");
    query.bindValue(":id", student_id);
    query.exec();
    while(query.next())
        ui->comboBox->addItem(query.value(1).toString(), query.value(0));
    ui->comboBox->setCurrentIndex(-1);
}


void students_researches::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT unassign_research(:student, :research)");
    query.bindValue(":student", student_id);
    query.bindValue(":research", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void students_researches::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}

void students_researches::on_InsertDialogOpen_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT assign_research(:student, :research)");
    query.bindValue(":student", student_id);
    query.bindValue(":research", ui->comboBox->currentData());
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}

