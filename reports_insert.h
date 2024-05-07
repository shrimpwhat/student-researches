#ifndef REPORTS_INSERT_H
#define REPORTS_INSERT_H

#include <QWidget>

namespace Ui {
class reports_insert;
}

class reports_insert : public QWidget
{
    Q_OBJECT

public:
    explicit reports_insert(QWidget *parent = nullptr);
    ~reports_insert();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::reports_insert *ui;
};

#endif // REPORTS_INSERT_H
