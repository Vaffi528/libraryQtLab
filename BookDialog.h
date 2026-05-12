#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>

class BookDialog : public QDialog{
    Q_OBJECT

    public:
        //explicit BookDialog(QWidget* parent = nullptr);

    //signals:
    //    void sentAuthorData(){};

    private slots:
        void onOkBtnClicked(){};
};

#endif // BOOKDIALOG_H
