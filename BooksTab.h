#ifndef BOOKSTAB_H
#define BOOKSTAB_H

#include "AbstractTab.h"
#include "BookDialog.h"

class BooksTab: public AbstractTab {
    public:
        BooksTab(QTableView* tab): AbstractTab(tab) {};
        virtual ~BooksTab() override = default;
        virtual bool AddRecord() override;
        virtual bool EditRecord() override {};
        virtual bool RemoveRecord() override {};
};

#endif // BOOKSTAB_H
