#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>
#include "DialogsData.h"
#include "database.h"

class BookDialog : public QDialog{
    Q_OBJECT

    public:
        explicit BookDialog(QWidget* parent = nullptr);
        static BooksDialogData getBook(bool* ok, QWidget* parent = nullptr);
        void setUpWidgets();

    private slots:
        void onOkBtnClicked();

    private:
        BooksDialogData book;
        QLineEdit* bookEdit;
        QComboBox* authorCombo;
        QListWidget* genresList;
        QPushButton* okBtn;
};

#endif // BOOKDIALOG_H
