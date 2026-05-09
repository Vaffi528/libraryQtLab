#ifndef BOOKSTAB_H
#define BOOKSTAB_H

#include "AbstractTab.h"

class BooksTab: public AbstractTab {
    public:
        BooksTab(Ui::MainWindow *ui);
        virtual ~BooksTab() override;
        virtual bool AddRecord() override;
        virtual bool EditRecord() override;
        virtual bool RemoveRecord() override;

    private:
        QTabWidget* tab;
};

#endif // BOOKSTAB_H
