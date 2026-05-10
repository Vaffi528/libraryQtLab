#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include "ui_mainwindow.h"

class AbstractTab {
    public:
        AbstractTab(Ui::MainWindow *ui): ui(ui) {};
        virtual ~AbstractTab() {};

    public:
        virtual bool AddRecord() = 0;
        virtual bool EditRecord() = 0;
        virtual bool RemoveRecord() = 0;

    public:
        Ui::MainWindow *ui;
};

#endif // ABSTRACTTAB_H
