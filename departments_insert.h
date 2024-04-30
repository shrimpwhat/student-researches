#ifndef DEPARTMENTS_INSERT_H
#define DEPARTMENTS_INSERT_H

#include <QWidget>

namespace Ui {
class DepartmentsInsert;
}

class DepartmentsInsert : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentsInsert(QWidget *parent = nullptr);
    ~DepartmentsInsert();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::DepartmentsInsert *ui;
};

#endif // DEPARTMENTS_INSERT_H
