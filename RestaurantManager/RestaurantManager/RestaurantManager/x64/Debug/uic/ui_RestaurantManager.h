/********************************************************************************
** Form generated from reading UI file 'RestaurantManager.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTMANAGER_H
#define UI_RESTAURANTMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StylePlannerClass
{
public:
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *StylePlannerClass)
    {
        if (StylePlannerClass->objectName().isEmpty())
            StylePlannerClass->setObjectName("StylePlannerClass");
        StylePlannerClass->resize(913, 573);
        centralWidget = new QWidget(StylePlannerClass);
        centralWidget->setObjectName("centralWidget");
        StylePlannerClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(StylePlannerClass);
        mainToolBar->setObjectName("mainToolBar");
        StylePlannerClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StylePlannerClass);
        statusBar->setObjectName("statusBar");
        StylePlannerClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(StylePlannerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 913, 21));
        StylePlannerClass->setMenuBar(menuBar);

        retranslateUi(StylePlannerClass);

        QMetaObject::connectSlotsByName(StylePlannerClass);
    } // setupUi

    void retranslateUi(QMainWindow *StylePlannerClass)
    {
        StylePlannerClass->setWindowTitle(QCoreApplication::translate("StylePlannerClass", "StylePlanner", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StylePlannerClass: public Ui_StylePlannerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTMANAGER_H
