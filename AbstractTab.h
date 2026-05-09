#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include "ui_mainwindow.h"

class AbstractTab {
    public:
        virtual ~AbstractTab();

    public:
        virtual bool AddRecord();
        virtual bool EditRecord();
        virtual bool RemoveRecord();
};

#endif // ABSTRACTTAB_H
