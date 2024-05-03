#ifndef SUPERVISORS_INSERT_H
#define SUPERVISORS_INSERT_H

#include <QWidget>

namespace Ui {
class supervisors_insert;
}

class supervisors_insert : public QWidget
{
    Q_OBJECT

public:
    explicit supervisors_insert(QWidget *parent = nullptr);
    ~supervisors_insert();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::supervisors_insert *ui;
};

#endif // SUPERVISORS_INSERT_H
