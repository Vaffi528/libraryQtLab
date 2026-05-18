#ifndef AUTHORSTAB_H
#define AUTHORSTAB_H

#include "AbstractTab.h"

// TODO: зарефакторить + добавить надкласс PlainDataTab
class AuthorsTab: public AbstractTab {
    public:
        AuthorsTab(QTableView* tab): AbstractTab(tab) {};
        virtual ~AuthorsTab() override = default;
        virtual Status AddRecord() override;
        virtual Status EditRecord() override;
        virtual Status RemoveRecord() override;
};

#endif // AUTHORSTAB_H
