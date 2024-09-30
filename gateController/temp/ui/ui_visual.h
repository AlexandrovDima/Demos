/********************************************************************************
** Form generated from reading UI file 'visual.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUAL_H
#define UI_VISUAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_visual
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_do_work;
    QLabel *l_iam_getresult;
    QLabel *l_iam_tryset;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *l_soc_stay;

    void setupUi(QWidget *visual)
    {
        if (visual->objectName().isEmpty())
            visual->setObjectName("visual");
        visual->resize(515, 150);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(visual->sizePolicy().hasHeightForWidth());
        visual->setSizePolicy(sizePolicy);
        visual->setMinimumSize(QSize(515, 150));
        visual->setMaximumSize(QSize(600, 170));
        verticalLayout = new QVBoxLayout(visual);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_2 = new QGroupBox(visual);
        groupBox_2->setObjectName("groupBox_2");
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName("horizontalLayout");
        pb_do_work = new QPushButton(groupBox_2);
        pb_do_work->setObjectName("pb_do_work");
        pb_do_work->setMinimumSize(QSize(40, 0));
        pb_do_work->setCheckable(true);

        horizontalLayout->addWidget(pb_do_work);

        l_iam_getresult = new QLabel(groupBox_2);
        l_iam_getresult->setObjectName("l_iam_getresult");
        l_iam_getresult->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(l_iam_getresult);

        l_iam_tryset = new QLabel(groupBox_2);
        l_iam_tryset->setObjectName("l_iam_tryset");
        l_iam_tryset->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(l_iam_tryset);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(visual);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        l_soc_stay = new QLabel(groupBox);
        l_soc_stay->setObjectName("l_soc_stay");

        horizontalLayout_2->addWidget(l_soc_stay);


        verticalLayout->addWidget(groupBox);


        retranslateUi(visual);

        QMetaObject::connectSlotsByName(visual);
    } // setupUi

    void retranslateUi(QWidget *visual)
    {
        visual->setWindowTitle(QCoreApplication::translate("visual", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("visual", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\262\320\276\321\200\320\276\321\202\320\260\320\274\320\270", nullptr));
        pb_do_work->setText(QCoreApplication::translate("visual", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\262\320\276\321\200\320\276\321\202\320\260", nullptr));
        l_iam_getresult->setText(QCoreApplication::translate("visual", "---", nullptr));
        l_iam_tryset->setText(QCoreApplication::translate("visual", "---", nullptr));
        groupBox->setTitle(QCoreApplication::translate("visual", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \321\201\320\276\320\272\320\265\321\202\320\260", nullptr));
        l_soc_stay->setText(QCoreApplication::translate("visual", "---", nullptr));
    } // retranslateUi

};

namespace Ui {
    class visual: public Ui_visual {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUAL_H
