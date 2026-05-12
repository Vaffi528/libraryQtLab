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
        virtual bool AddRecord() = 0;
        virtual bool EditRecord() = 0;
        virtual bool RemoveRecord() = 0;

    public:
        QTableView* tab;
};

#endif // ABSTRACTTAB_H
