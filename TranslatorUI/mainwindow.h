#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H
