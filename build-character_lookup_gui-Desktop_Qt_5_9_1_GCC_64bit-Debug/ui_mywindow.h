/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *imageLabel;
    QLabel *characterLabel;
    QLabel *actorLabel;
    QLabel *wikiLabel;

    void setupUi(QWidget *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName(QStringLiteral("MyWindow"));
        MyWindow->resize(800, 600);
        verticalLayout = new QVBoxLayout(MyWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        imageLabel = new QLabel(MyWindow);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        verticalLayout->addWidget(imageLabel);

        characterLabel = new QLabel(MyWindow);
        characterLabel->setObjectName(QStringLiteral("characterLabel"));

        verticalLayout->addWidget(characterLabel);

        actorLabel = new QLabel(MyWindow);
        actorLabel->setObjectName(QStringLiteral("actorLabel"));

        verticalLayout->addWidget(actorLabel);

        wikiLabel = new QLabel(MyWindow);
        wikiLabel->setObjectName(QStringLiteral("wikiLabel"));

        verticalLayout->addWidget(wikiLabel);


        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QWidget *MyWindow)
    {
        MyWindow->setWindowTitle(QApplication::translate("MyWindow", "Form", Q_NULLPTR));
        imageLabel->setText(QApplication::translate("MyWindow", "TextLabel", Q_NULLPTR));
        characterLabel->setText(QApplication::translate("MyWindow", "TextLabel", Q_NULLPTR));
        actorLabel->setText(QApplication::translate("MyWindow", "TextLabel", Q_NULLPTR));
        wikiLabel->setText(QApplication::translate("MyWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
