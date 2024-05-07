#include "researches_reports.h"
#include "ui_researches_reports.h"

#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

researches_reports::researches_reports(int research_id, QWidget* parent): QWidget(parent),
    ui(new Ui::researches_reports)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
    this->research_id = research_id;
}


researches_reports::~researches_reports()
{
    delete ui;
    delete qmodel;
}


void researches_reports::on_tableRefreshButton_clicked() {
    qmodel->setQuery(QString("select * from reports where id in (select report_id from research_reports where research_id = %1);").arg(research_id));
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
    this->update_comboBox();
}


void researches_reports::update_comboBox() {
    ui->comboBox->clear();
    QSqlQuery query = QSqlQuery();
    query.prepare("select id, name from reports where id not in (select report_id from research_reports where research_id = :id);");
    query.bindValue(":id", research_id);
    query.exec();
    while(query.next())
        ui->comboBox->addItem(query.value(1).toString(), query.value(0));
    ui->comboBox->setCurrentIndex(-1);
}


void researches_reports::on_InsertDialogOpen_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT assign_report(:research, :report)");
    query.bindValue(":research", research_id);
    query.bindValue(":report", ui->comboBox->currentData());
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void researches_reports::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT unassign_report(:research, :report)");
    query.bindValue(":research", research_id);
    query.bindValue(":report", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void researches_reports::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}
