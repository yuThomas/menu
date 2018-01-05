/********************************************************************************
** Form generated from reading UI file 'menuwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWIDGET_H
#define UI_MENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWidget
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *AppListWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *condLineEdit;

    void setupUi(QWidget *MenuWidget)
    {
        if (MenuWidget->objectName().isEmpty())
            MenuWidget->setObjectName(QStringLiteral("MenuWidget"));
        MenuWidget->resize(563, 660);
        MenuWidget->setMinimumSize(QSize(563, 660));
        MenuWidget->setMaximumSize(QSize(563, 660));
        verticalLayout = new QVBoxLayout(MenuWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        AppListWidget = new QListWidget(MenuWidget);
        AppListWidget->setObjectName(QStringLiteral("AppListWidget"));
        QFont font;
        font.setPointSize(12);
        AppListWidget->setFont(font);
        AppListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        AppListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        AppListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        AppListWidget->setIconSize(QSize(24, 24));
        AppListWidget->setViewMode(QListView::ListMode);
        AppListWidget->setSortingEnabled(true);

        verticalLayout->addWidget(AppListWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(MenuWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        condLineEdit = new QLineEdit(MenuWidget);
        condLineEdit->setObjectName(QStringLiteral("condLineEdit"));

        horizontalLayout->addWidget(condLineEdit);

        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MenuWidget);

        QMetaObject::connectSlotsByName(MenuWidget);
    } // setupUi

    void retranslateUi(QWidget *MenuWidget)
    {
        MenuWidget->setWindowTitle(QApplication::translate("MenuWidget", "Applications", 0));
        label->setText(QApplication::translate("MenuWidget", "Search", 0));
    } // retranslateUi

};

namespace Ui {
    class MenuWidget: public Ui_MenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWIDGET_H
