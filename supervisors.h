#ifndef SUPERVISORS_H
#define SUPERVISORS_H

#include "supervisors_insert.h"
#include "supervisors_update.h"

#include <QSqlQueryModel>
#include <QWidget>

namespace Ui {
class supervisors;
}

class supervisors : public QWidget
{
    Q_OBJECT

public:
    supervisors(QWidget *parent = nullptr);
    ~supervisors();

private slots:
    void on_tableRefreshButton_clicked();

    void on_InsertDialogOpen_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_UpdateDialogOpen_clicked();

    void on_DeleteRow_clicked();

private:
    Ui::supervisors *ui;
    QSqlQueryModel *qmodel;
    supervisors_insert *insert_dialog;
    supervisors_update *update_dialog;
    int selected_id;
};

#endif // SUPERVISORS_H
