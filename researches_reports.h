#ifndef RESEARCHES_REPORTS_H
#define RESEARCHES_REPORTS_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class researches_reports;
}

class researches_reports : public QWidget
{
    Q_OBJECT

public:
    researches_reports(int research_id, QWidget *parent = nullptr);
    ~researches_reports();

private slots:
    void on_tableRefreshButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_DeleteRow_clicked();

    void on_InsertDialogOpen_clicked();

private:
    Ui::researches_reports *ui;
    QSqlQueryModel *qmodel;
    int research_id;
    int selected_id;

    void update_comboBox();
};

#endif // RESEARCHES_REPORTS_H
