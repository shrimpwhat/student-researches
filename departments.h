#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlTableModel>
#include "login.h"
#include "departments_insert.h"
#include "departments_update.h"

namespace Ui {
class DepartmentsView;
}

class DepartmentsView : public QWidget
{
    Q_OBJECT

public:
    DepartmentsView(QWidget *parent = nullptr);
    ~DepartmentsView();

private slots:
    void on_tableRefreshButton_clicked();
    void on_InsertDialogOpen_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_DeleteSubmit_clicked();

    void DelRecAction();
    void ModRecAction();

    void on_pushButton_clicked();

    void on_UpdateDialogOpen_clicked();

signals:
    void sendID(int);

private:
    Ui::DepartmentsView *ui;
    Login *login;
    QSqlQueryModel *qmodel;
    DepartmentsInsert *insert_dialog;
    DepartmentsUpdate *update_dialog;
    int fl = 0;
    int selected_id;
};

#endif // DEPARTMENTS_H
