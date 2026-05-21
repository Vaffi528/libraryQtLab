#ifndef PLAINDATATAB_H
#define PLAINDATATAB_H

#include "AbstractTab.h"

class PlainDataTab: public AbstractTab {
    public:
        PlainDataTab(QTableView* tab): AbstractTab(tab) {};
        virtual ~PlainDataTab() override = default;
        virtual Status AddRecord(QString tabName);
        virtual Status EditRecord(QString tabName);
        virtual Status RemoveRecord(QString tabName);
};

#endif // PLAINDATATAB_H
