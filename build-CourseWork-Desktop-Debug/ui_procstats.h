/********************************************************************************
** Form generated from reading UI file 'procstats.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCSTATS_H
#define UI_PROCSTATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_ProcStats
{
public:
    QCustomPlot *widget;

    void setupUi(QDialog *ProcStats)
    {
        if (ProcStats->objectName().isEmpty())
            ProcStats->setObjectName(QString::fromUtf8("ProcStats"));
        ProcStats->resize(400, 300);
        widget = new QCustomPlot(ProcStats);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 381, 281));

        retranslateUi(ProcStats);

        QMetaObject::connectSlotsByName(ProcStats);
    } // setupUi

    void retranslateUi(QDialog *ProcStats)
    {
        ProcStats->setWindowTitle(QCoreApplication::translate("ProcStats", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcStats: public Ui_ProcStats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCSTATS_H
