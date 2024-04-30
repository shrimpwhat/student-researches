#include "printgraph.h"
#include "ui_printgraph.h"

printGraph::printGraph(QWidget *parent)
    : QWidget(parent), ui(new Ui::printGraph) {
  ui->setupUi(this);
  ui->widget->plotLayout()->insertRow(0);
  ui->widget->plotLayout()->addElement(
      0, 0, new QCPTextElement(ui->widget, "График выручки"));


  QVector<double> dx, dy;
  double minX, minY, maxX, maxY;
  minX = 0;
  minY = 0;
  maxX = 0;
  maxY = 0;
  QSqlQuery *query = new QSqlQuery();

  if (query->exec("SELECT * FROM chart")) {
    while (query->next()) {
      if (minX >= query->value(0).toDouble())
        minX = query->value(0).toDouble();
      if (minY >= query->value(1).toDouble())
        minY = query->value(1).toDouble();
      if (maxX <= query->value(0).toDouble())
        maxX = query->value(0).toDouble();
      if (maxY <= query->value(1).toDouble())
        maxY = query->value(1).toDouble();
      // Добавление координат в вектора
      dx << query->value(0).toDouble();
      dy << query->value(1).toDouble();
    }
    QCPBars *bar = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
    bar->setName("Значение");
    QSharedPointer<QCPAxisTickerFixed> ticker(new QCPAxisTickerFixed);
    bar->setBrush(QColor(255, 0, 0, 255));
    bar->setData(dx, dy); // координаты точек
    bar->setWidth(0.25);  // толщина линий
    ui->widget->xAxis->setLabel("Месяц");
    ui->widget->yAxis->setLabel("Выручка");
    ui->widget->xAxis->setRange(minX, maxX + 0.20);
    ui->widget->yAxis->setRange(minY, maxY + 1);
    ui->widget->xAxis->setTicker(ticker);
    ui->widget->yAxis->setTicker(ticker);
  }
}

printGraph::~printGraph() { delete ui; }

void printGraph::on_pushButton_clicked() {
  QString fn = QFileDialog::getSaveFileName(this, "Сохранить PDF", "./", "Pdf (*.pdf)");
  if (!fn.isEmpty()) {
    QPrinter print;
    ui->widget->savePdf(fn);
  }
}
