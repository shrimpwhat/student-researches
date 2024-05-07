#ifndef REPORTS_H
#define REPORTS_H

#include "reports_insert.h"
#include "reports_update.h"

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class reports;
}

class reports : public QWidget
{
    Q_OBJECT

public:
    reports(QWidget *parent = nullptr);
    ~reports();

private slots:
    void on_tableRefreshButton_clicked();

    void on_InsertDialogOpen_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_UpdateDialogOpen_clicked();

    void on_DeleteRow_clicked();

private:
    Ui::reports *ui;
    QSqlQueryModel *qmodel;
    reports_insert *insert_dialog;
    reports_update *update_dialog;
    int selected_id;
};

#endif // REPORTS_H
