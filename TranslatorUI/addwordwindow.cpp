#include "addwordwindow.h"
#include "ui_addwordwindow.h"
#include "../TranslatorBase/TranslatorTools.h"
#include "mainwindow.h"

using namespace TranslationTools;

addWordWindow::addWordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWordWindow)
{
    ui->setupUi(this);
    connect(ui->ResetForm,SIGNAL(clicked()),this,SLOT(clearForm()));
    connect(ui->AddWord,SIGNAL(clicked()),this,SLOT(addNewWord()));
    connect(ui->Close,SIGNAL(clicked()),this,SLOT(close()));

}

void addWordWindow::addNewWord()
{
    static ttArray *words = NULL;
    static ttArray *dics = NULL;
    if (words == NULL)
    {
	words = new ttArray(new ttWord,new ttWord,NULL);
	words->operator [](0)->attachMetaData(new ttWordType);
	words->operator [](1)->attachMetaData(new ttWordType);
	words->retain();
    }
    if (dics == NULL)
    {
	dics = new ttArray(pp->getDictionary(),ep->getDictionary(),NULL);
	dics->retain();
    }
    static_cast<ttWord*>(words->operator[](0))->setWord(ui->lineEditP->text().toStdWString());
    static_cast<ttWord*>(words->operator[](1))->setWord(ui->lineEditE->text().toStdWString());
    words->operator [](0)->getMetaData<ttWordType>()->setType(ttWordType::WordType(ui->wordType->currentIndex()+1));
    words->operator [](1)->getMetaData<ttWordType>()->setType(ttWordType::WordType(ui->wordType->currentIndex()+1));
    ttDictionary::addWord(*words,*dics);
}

void addWordWindow::clearForm()
{
    ui->lineEditE->setText("");
    ui->lineEditP->setText("");
    ui->wordType->setCurrentIndex(0);
}

void addWordWindow::close()
{
    hide();
}

addWordWindow::~addWordWindow()
{
    delete ui;
}
