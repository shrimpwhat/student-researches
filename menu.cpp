#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}
