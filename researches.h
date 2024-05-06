#ifndef RESEARCHES_H
#define RESEARCHES_H

#include "researches_insert.h"
#include "researches_update.h"

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class researches;
}

class researches : public QWidget
{
    Q_OBJECT

public:
    researches(QWidget *parent = nullptr);
    ~researches();

private slots:
    void on_tableRefreshButton_clicked();

    void on_InsertDialogOpen_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_UpdateDialogOpen_clicked();

    void on_DeleteRow_clicked();

private:
    Ui::researches *ui;
    QSqlQueryModel *qmodel;
    researches_insert *insert_dialog;
    researches_update *update_dialog;
    int selected_id;
};

#endif // RESEARCHES_H
