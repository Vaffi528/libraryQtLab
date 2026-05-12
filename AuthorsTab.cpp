#include "AuthorsTab.h"

bool AuthorsTab::AddRecord() {
    bool isDialogOk;
    QString authorsName = QInputDialog::getText(this, "Add Record",
    "Input author:", QLineEdit::Normal, "", &isDialogOk);
    AuthorsDialogData author {authorsName};
    if (isDialogOk) {
        bool isDBResponseOk = DataBaseManager::getInstance()->addAuthor(&author);
        if (isDBResponseOk) {
            qDebug() << "Автор успешно добавлен в БД!";
           return true;
        }
        qDebug() << "Ошибка базы данных при добавления автора!";
    }
    qDebug() << "Ошибка диалога при добавления автора!";
    return false;
}
