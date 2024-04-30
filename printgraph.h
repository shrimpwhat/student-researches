#ifndef PRINTGRAPH_H
#define PRINTGRAPH_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class printGraph;
}

class printGraph : public QWidget
{
    Q_OBJECT

public:
    explicit printGraph(QWidget *parent = nullptr);
    ~printGraph();

private slots:
    void on_pushButton_clicked();

private:
    Ui::printGraph *ui;
};

#endif // PRINTGRAPH_H
