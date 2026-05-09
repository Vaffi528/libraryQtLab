#ifndef AUTHORSTAB_H
#define AUTHORSTAB_H

#include "AbstractTab.h"

class AuthorsTab: public AbstractTab {
    public:
        AuthorsTab(Ui::MainWindow *ui);
        virtual ~AuthorsTab() override;
        virtual bool AddRecord() override;
        virtual bool EditRecord() override;
        virtual bool RemoveRecord() override;

    private:
        QTabWidget* tab;
};

#endif // AUTHORSTAB_H
