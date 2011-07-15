#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_New,SIGNAL(triggered()),this,SLOT(newClick()));
    connect(ui->action_Exit,SIGNAL(triggered()),this,SLOT(exitClick()));
    connect(ui->action_Open,SIGNAL(triggered()),this,SLOT(OpenClick()));
    connect(ui->action_Save,SIGNAL(triggered()),this,SLOT(SaveClick()));
    connect(ui->action_Spell_Check,SIGNAL(triggered()),this,SLOT(SpellCheckClick()));
    connect(ui->action_Translate,SIGNAL(triggered()),this,SLOT(TranslateClick()));
    connect(ui->action_Options,SIGNAL(triggered()),this,SLOT(OptionsClick()));
    connect(ui->action_Help,SIGNAL(triggered()),this,SLOT(HelpClick()));
    connect(ui->action_About,SIGNAL(triggered()),this,SLOT(AboutClick()));
    connect(ui->translateButton,SIGNAL(clicked()),this,SLOT(TranslateClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitClick()
{
    qApp->exit(0);
}

void MainWindow::newClick()
{
    ui->TextEditA->document()->clear();
    ui->TextEditB->document()->clear();
}

void MainWindow::SaveClick()
{
    QFileDialog saveDialog;
    saveDialog.show();
}

void MainWindow::OpenClick()
{
    QFileDialog loadDialog;
    loadDialog.show();
}

void MainWindow::SpellCheckClick()
{
    QDialog dialog;
    dialog.show();
}

void MainWindow::TranslateClick()
{
    //QDialog dialog;
    //dialog.show();
    ui->TextEditB->setPlainText(ui->TextEditA->toPlainText());
}

void MainWindow::OptionsClick()
{
    QDialog dialog;
    dialog.show();
}

void MainWindow::HelpClick()
{
    QDialog dialog;
    dialog.show();
}

void MainWindow::AboutClick()
{
    static AboutWindow* about = new AboutWindow;
    about->show();
    about->activateWindow();
}

