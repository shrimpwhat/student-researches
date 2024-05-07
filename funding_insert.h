#ifndef FUNDING_INSERT_H
#define FUNDING_INSERT_H

#include <QWidget>

namespace Ui {
class funding_insert;
}

class funding_insert : public QWidget
{
    Q_OBJECT

public:
    explicit funding_insert(QWidget *parent = nullptr);
    ~funding_insert();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::funding_insert *ui;
};

#endif // FUNDING_INSERT_H
