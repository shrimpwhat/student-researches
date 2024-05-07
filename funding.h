#ifndef FUNDING_H
#define FUNDING_H

#include "funding_insert.h"
#include "funding_update.h"
#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class funding;
}

class funding : public QWidget
{
    Q_OBJECT

public:
    funding(QWidget *parent = nullptr);
    ~funding();

private slots:
    void on_tableRefreshButton_clicked();

    void on_InsertDialogOpen_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_UpdateDialogOpen_clicked();

    void on_DeleteRow_clicked();

private:
    Ui::funding *ui;
    QSqlQueryModel *qmodel;
    funding_insert *insert_dialog;
    funding_update *update_dialog;
    int selected_id;
};

#endif // FUNDING_H
