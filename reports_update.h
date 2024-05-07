#ifndef REPORTS_UPDATE_H
#define REPORTS_UPDATE_H

#include <QWidget>

namespace Ui {
class reports_update;
}

class reports_update : public QWidget
{
    Q_OBJECT

public:
    explicit reports_update(int id, QWidget *parent = nullptr);
    ~reports_update();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::reports_update *ui;
    int id;
};

#endif // REPORTS_UPDATE_H
