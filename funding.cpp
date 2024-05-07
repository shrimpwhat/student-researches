#include "funding.h"
#include "ui_funding.h"

#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

funding::funding(QWidget* parent): QWidget(parent),
    ui(new Ui::funding)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel(this);
}


funding::~funding()
{
    delete ui;
    delete qmodel;
    delete insert_dialog;
    delete update_dialog;
}


void funding::on_tableRefreshButton_clicked() {
    qmodel->setQuery("select id, source, (select title from researches where researches.id = research) as research, amount, date from funding;");
    ui->tableView->setModel(qmodel);
    ui->tableView->hideColumn(0);
}


void funding::on_InsertDialogOpen_clicked() {
    insert_dialog = new funding_insert();
    insert_dialog->show();
}


void funding::on_UpdateDialogOpen_clicked()
{
    update_dialog = new funding_update(selected_id);
    update_dialog->show();
}

void funding::on_DeleteRow_clicked()
{
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT delete_funding(:id)");
    query.bindValue(":id", selected_id);
    if (!query.exec())
        QMessageBox::critical(nullptr, "Ошибка", query.lastError().text());
    on_tableRefreshButton_clicked();
}


void funding::on_tableView_clicked(const QModelIndex &index) {
    selected_id = ui->tableView->model()
                 ->data(ui->tableView->model()->index(index.row(), 0))
                 .toInt();
}
