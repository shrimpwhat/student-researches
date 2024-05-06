#ifndef STUDENTS_INSERT_H
#define STUDENTS_INSERT_H

#include <QWidget>

namespace Ui {
class students_insert;
}

class students_insert : public QWidget
{
    Q_OBJECT

public:
    explicit students_insert(QWidget *parent = nullptr);
    ~students_insert();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::students_insert *ui;
};


#endif // STUDENTS_INSERT_H
