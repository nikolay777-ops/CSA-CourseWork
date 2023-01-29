/********************************************************************************
** Form generated from reading UI file 'processorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSORWIDGET_H
#define UI_PROCESSORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessorWidget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *ProcessorWidget)
    {
        if (ProcessorWidget->objectName().isEmpty())
            ProcessorWidget->setObjectName(QString::fromUtf8("ProcessorWidget"));
        ProcessorWidget->resize(400, 300);
        pushButton = new QPushButton(ProcessorWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 70, 75, 23));
        pushButton_2 = new QPushButton(ProcessorWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(110, 70, 75, 23));
        pushButton_3 = new QPushButton(ProcessorWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(190, 70, 75, 23));

        retranslateUi(ProcessorWidget);

        QMetaObject::connectSlotsByName(ProcessorWidget);
    } // setupUi

    void retranslateUi(QWidget *ProcessorWidget)
    {
        ProcessorWidget->setWindowTitle(QCoreApplication::translate("ProcessorWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("ProcessorWidget", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ProcessorWidget", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ProcessorWidget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcessorWidget: public Ui_ProcessorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSORWIDGET_H
