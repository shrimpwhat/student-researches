#ifndef FUNDING_UPDATE_H
#define FUNDING_UPDATE_H

#include <QWidget>

namespace Ui {
class funding_update;
}

class funding_update : public QWidget
{
    Q_OBJECT

public:
    explicit funding_update(int id, QWidget *parent = nullptr);
    ~funding_update();

private slots:
    void on_InsertSubmit_clicked();

private:
    Ui::funding_update *ui;
    int id;
};

#endif // FUNDING_UPDATE_H
