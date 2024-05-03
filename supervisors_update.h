#ifndef SUPERVISORS_UPDATE_H
#define SUPERVISORS_UPDATE_H

#include <QWidget>

namespace Ui {
class supervisors_update;
}

class supervisors_update : public QWidget
{
    Q_OBJECT

public:
    explicit supervisors_update(int id, QWidget *parent = nullptr);
    ~supervisors_update();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::supervisors_update *ui;
    int id;
};

#endif // SUPERVISORS_UPDATE_H
