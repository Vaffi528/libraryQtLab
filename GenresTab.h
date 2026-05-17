#ifndef GENRESTAB_H
#define GENRESTAB_H

#include "AbstractTab.h"

class GenresTab: public AbstractTab {
    public:
        GenresTab(QTableView* tab): AbstractTab(tab) {};
        virtual ~GenresTab() override = default;
        virtual bool AddRecord() override;
        virtual bool EditRecord() override;
        virtual bool RemoveRecord() override;

};

#endif // GENRESTAB_H
