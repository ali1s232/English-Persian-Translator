/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Jul 15 15:15:27 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *action_New;
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Exit;
    QAction *actionDictionaries;
    QAction *action_Help;
    QAction *action_Dictionaries;
    QAction *action_About;
    QAction *action_Translate;
    QAction *action_Options;
    QAction *action_Spell_Check;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBoxA;
    QPlainTextEdit *TextEditA;
    QPushButton *translateButton;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBoxB;
    QPlainTextEdit *TextEditB;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menu_Help;
    QMenu *menuTranslator;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QString::fromUtf8("action_New"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        actionDictionaries = new QAction(MainWindow);
        actionDictionaries->setObjectName(QString::fromUtf8("actionDictionaries"));
        action_Help = new QAction(MainWindow);
        action_Help->setObjectName(QString::fromUtf8("action_Help"));
        action_Dictionaries = new QAction(MainWindow);
        action_Dictionaries->setObjectName(QString::fromUtf8("action_Dictionaries"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_Translate = new QAction(MainWindow);
        action_Translate->setObjectName(QString::fromUtf8("action_Translate"));
        action_Options = new QAction(MainWindow);
        action_Options->setObjectName(QString::fromUtf8("action_Options"));
        action_Spell_Check = new QAction(MainWindow);
        action_Spell_Check->setObjectName(QString::fromUtf8("action_Spell_Check"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        comboBoxA = new QComboBox(centralWidget);
        comboBoxA->setObjectName(QString::fromUtf8("comboBoxA"));

        verticalLayout_2->addWidget(comboBoxA);

        TextEditA = new QPlainTextEdit(centralWidget);
        TextEditA->setObjectName(QString::fromUtf8("TextEditA"));

        verticalLayout_2->addWidget(TextEditA);


        horizontalLayout_2->addLayout(verticalLayout_2);

        translateButton = new QPushButton(centralWidget);
        translateButton->setObjectName(QString::fromUtf8("translateButton"));
        translateButton->setMaximumSize(QSize(40, 20));

        horizontalLayout_2->addWidget(translateButton);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBoxB = new QComboBox(centralWidget);
        comboBoxB->setObjectName(QString::fromUtf8("comboBoxB"));

        verticalLayout->addWidget(comboBoxB);

        TextEditB = new QPlainTextEdit(centralWidget);
        TextEditB->setObjectName(QString::fromUtf8("TextEditB"));

        verticalLayout->addWidget(TextEditB);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menuTranslator = new QMenu(menuBar);
        menuTranslator->setObjectName(QString::fromUtf8("menuTranslator"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTranslator->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menuFile->addAction(action_New);
        menuFile->addSeparator();
        menuFile->addAction(action_Open);
        menuFile->addAction(action_Save);
        menuFile->addSeparator();
        menuFile->addAction(action_Exit);
        menu_Help->addAction(action_Help);
        menu_Help->addAction(action_About);
        menuTranslator->addAction(action_Spell_Check);
        menuTranslator->addAction(action_Translate);
        menuTranslator->addSeparator();
        menuTranslator->addAction(action_Options);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "new", 0, QApplication::UnicodeUTF8));
        action_New->setText(QApplication::translate("MainWindow", "&New", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        actionDictionaries->setText(QApplication::translate("MainWindow", "&Translate", 0, QApplication::UnicodeUTF8));
        action_Help->setText(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        action_Dictionaries->setText(QApplication::translate("MainWindow", "&Dictionaries", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        action_Translate->setText(QApplication::translate("MainWindow", "&Translate", 0, QApplication::UnicodeUTF8));
        action_Options->setText(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));
        action_Spell_Check->setText(QApplication::translate("MainWindow", "&Spell Check", 0, QApplication::UnicodeUTF8));
        translateButton->setText(QApplication::translate("MainWindow", "=>", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuTranslator->setTitle(QApplication::translate("MainWindow", "Translator", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
