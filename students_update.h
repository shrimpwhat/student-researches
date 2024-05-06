#ifndef STUDENTS_UPDATE_H
#define STUDENTS_UPDATE_H

#include <QWidget>

namespace Ui {
class students_update;
}

class students_update : public QWidget
{
    Q_OBJECT

public:
    explicit students_update(int id, QWidget *parent = nullptr);
    ~students_update();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::students_update *ui;
    int id;
};

#endif // STUDENTS_UPDATE_H
