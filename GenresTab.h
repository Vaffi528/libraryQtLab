#ifndef GENRESTAB_H
#define GENRESTAB_H

#include "AbstractTab.h"

class GenresTab: public AbstractTab {
    public:
        GenresTab(Ui::MainWindow *ui);
        virtual ~GenresTab() override;
        virtual bool AddRecord() override;
        virtual bool EditRecord() override;
        virtual bool RemoveRecord() override;

    private:
        QTabWidget* tab;
};

#endif // GENRESTAB_H
