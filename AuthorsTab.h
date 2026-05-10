#ifndef AUTHORSTAB_H
#define AUTHORSTAB_H

#include "AbstractTab.h"

class AuthorsTab: public AbstractTab {
    public:
        AuthorsTab(Ui::MainWindow *ui): AbstractTab(ui) {};
        virtual ~AuthorsTab() override {};
        virtual bool AddRecord() override {};
        virtual bool EditRecord() override {};
        virtual bool RemoveRecord() override {};
};

#endif // AUTHORSTAB_H
