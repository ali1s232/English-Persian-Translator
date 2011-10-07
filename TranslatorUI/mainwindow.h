#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../TranslatorBase/TranslatorTools.h"
#include "../PersianParser/PersianParser.h"
#include "../EnglishParser/EnglishParser.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void exitClick();
    void newClick();
    void OpenClick();
    void SaveClick();
    void SpellCheckClick();
    void TranslateClick();
    void HelpClick();
    void OptionsClick();
    void AboutClick();
    void NewWordClick();
};

extern EnglishParser *ep;
extern PersianParser *pp;

#endif // MAINWINDOW_H
