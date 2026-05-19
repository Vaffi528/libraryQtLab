#ifndef BOOKSTAB_H
#define BOOKSTAB_H

#include "AbstractTab.h"
#include "BookDialog.h"

class BooksTab: public AbstractTab {
    public:
        BooksTab(QTableView* tab): AbstractTab(tab) {};
        virtual ~BooksTab() override = default;
        virtual Status AddRecord() override;
        virtual Status EditRecord() override;
        virtual Status RemoveRecord() override;
};

#endif // BOOKSTAB_H
