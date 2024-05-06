#ifndef STUDENTS_RESEARCHES_H
#define STUDENTS_RESEARCHES_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class students_researches;
}

class students_researches : public QWidget
{
    Q_OBJECT

public:
    students_researches(int student_id, QWidget *parent = nullptr);
    ~students_researches();

private slots:
    void on_tableRefreshButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_DeleteRow_clicked();

    void on_InsertDialogOpen_clicked();

private:
    Ui::students_researches *ui;
    QSqlQueryModel *qmodel;
    int student_id;
    int selected_id;

    void update_comboBox();
};

#endif // STUDENTS_RESEARCHES_H
