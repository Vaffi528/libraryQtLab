#ifndef AUTHORSTAB_H
#define AUTHORSTAB_H

#include "AbstractTab.h"

class AuthorsTab: public AbstractTab {
    public:
        AuthorsTab(QTableView* tab): AbstractTab(tab) {};
        virtual ~AuthorsTab() override = default;
        virtual bool AddRecord() override;
        virtual bool EditRecord() override {};
        virtual bool RemoveRecord() override {};
};

#endif // AUTHORSTAB_H
