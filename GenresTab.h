#ifndef GENRESTAB_H
#define GENRESTAB_H

#include "AbstractTab.h"

class GenresTab: public AbstractTab {
    public:
        GenresTab(QTableView* tab): AbstractTab(tab) {};
        virtual ~GenresTab() override = default;
        virtual Status AddRecord() override;
        virtual Status EditRecord() override;
        virtual Status RemoveRecord() override;
};

#endif // GENRESTAB_H
