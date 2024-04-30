#ifndef DEPARTMENTS_UPDATE_H
#define DEPARTMENTS_UPDATE_H

#include <QWidget>

namespace Ui {
class DepartmentsUpdate;
}

class DepartmentsUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentsUpdate(int id, QWidget *parent = nullptr);
    ~DepartmentsUpdate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DepartmentsUpdate *ui;
    int id;
};

#endif // DEPARTMENTS_UPDATE_H
