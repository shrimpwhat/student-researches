#ifndef RESEARCHES_UPDATE_H
#define RESEARCHES_UPDATE_H

#include <QWidget>

namespace Ui {
class researches_update;
}

class researches_update : public QWidget
{
    Q_OBJECT

public:
    explicit researches_update(int id, QWidget *parent = nullptr);
    ~researches_update();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::researches_update *ui;
    int id;
};

#endif // RESEARCHES_UPDATE_H
