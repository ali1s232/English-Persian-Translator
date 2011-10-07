#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include "addwordwindow.h"
#include <QFileDialog>
#include <fstream>

PersianParser *pp = NULL;
EnglishParser *ep = NULL;
using namespace TranslationTools;
using namespace std;
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
    connect(ui->action_Add_new_word,SIGNAL(triggered()),this,SLOT(NewWordClick()));
    if (pp == NULL)
	pp = new PersianParser;
    if (ep == NULL)
	ep = new EnglishParser;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pp;
    delete ep;
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
    QString filename = QFileDialog::getSaveFileName(this);
    ofstream out(filename.toAscii(),ios_base::binary);
    out.put(0xff).put(0xfe);
    out.write((char*)ui->TextEditB->toPlainText().toStdWString().c_str(),ui->TextEditB->toPlainText().length() * 2);
    out.close();
}

void MainWindow::OpenClick()
{
    QString filename = QFileDialog::getOpenFileName(this);
    ifstream in(filename.toAscii(),ios_base::binary);
    wchar_t* x;
    in.seekg(0,ios_base::end);
    int filesize = in.tellg() - 2;
    in.seekg(0,ios_base::beg);
    in.ignore(2);
    x = new wchar_t[filesize + 1];
    in.read((char*)x,filesize);
    x[filesize / 2] = 0;
    ui->TextEditA->setPlainText(QString::fromWCharArray(x));
    delete x;

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
    wstring s = ui->TextEditA->toPlainText().toStdWString();
    ttArray* array;
    if (ui->comboBoxA->currentIndex() == 0)
	array = pp->parse(s);
    else
	array = ep->parse(s);

    if (ui->comboBoxB->currentIndex() == 0)
	s = ep->translate(array);
    else
	s = pp->translate(array);

    ui->TextEditB->setPlainText(QString::fromStdWString(s));
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


void MainWindow::NewWordClick()
{
    static addWordWindow* newWord = new addWordWindow;
    newWord->show();
    newWord->activateWindow();
}
