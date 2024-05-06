#ifndef RESEARCHES_INSERT_H
#define RESEARCHES_INSERT_H

#include <QWidget>

namespace Ui {
class researches_insert;
}

class researches_insert : public QWidget
{
    Q_OBJECT

public:
    explicit researches_insert(QWidget *parent = nullptr);
    ~researches_insert();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::researches_insert *ui;
};


#endif // RESEARCHES_INSERT_H
