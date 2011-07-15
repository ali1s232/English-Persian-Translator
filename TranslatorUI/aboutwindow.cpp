#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(doneClick()));
}

void AboutWindow::doneClick()
{
    hide();
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
