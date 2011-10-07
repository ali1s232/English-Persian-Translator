#ifndef ADDWORDWINDOW_H
#define ADDWORDWINDOW_H

#include <QDialog>

namespace Ui {
    class addWordWindow;
}

class addWordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWordWindow(QWidget *parent = 0);
    ~addWordWindow();

private:
    Ui::addWordWindow *ui;
public slots:
    void addNewWord();
    void clearForm();
    void close();
};

#endif // ADDWORDWINDOW_H
