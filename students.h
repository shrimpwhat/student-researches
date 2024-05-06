#ifndef STUDENTS_H
#define STUDENTS_H

#include "students_insert.h"
#include "students_update.h"

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class students;
}

class students : public QWidget
{
    Q_OBJECT

public:
    students(QWidget *parent = nullptr);
    ~students();

private slots:
    void on_tableRefreshButton_clicked();

    void on_InsertDialogOpen_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_UpdateDialogOpen_clicked();

    void on_DeleteRow_clicked();

private:
    Ui::students *ui;
    QSqlQueryModel *qmodel;
    students_insert *insert_dialog;
    students_update *update_dialog;
    int selected_id;
};

#endif // STUDENTS_H
