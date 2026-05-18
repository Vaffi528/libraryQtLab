#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include "ui_mainwindow.h"
#include "headers.h"
#include "database.h"

class AbstractTab: public QDialog {
    public:
    AbstractTab(QTableView* tab): tab(tab) {};
        virtual ~AbstractTab() {};

    public:
        virtual Status AddRecord() = 0;
        virtual Status EditRecord() = 0;
        virtual Status RemoveRecord() = 0;

    public:
        QTableView* tab;
};

#endif // ABSTRACTTAB_H
