#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>
#include "DialogsData.h"
#include "database.h"

class BookDialog : public QDialog{
    Q_OBJECT

    public:
        explicit BookDialog(QWidget* parent = nullptr, BooksDialogData* book = nullptr);
        static BooksDialogData getBook(bool* ok, QWidget* parent = nullptr, BooksDialogData* book = nullptr);
        void setUpWidgets(BooksDialogData* book = nullptr);
        void setUpPlainWidgets();
        void setUpListWidgets(BooksDialogData* book = nullptr);

    private slots:
        void onOkBtnClicked();

    private:
        BooksDialogData book;
        QLineEdit* bookEdit;
        QComboBox* authorCombo;
        QListWidget* genresList;
        QPushButton* okBtn;
        QPushButton* cancelBtn;
};

#endif // BOOKDIALOG_H
