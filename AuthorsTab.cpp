#include "AuthorsTab.h"

bool AuthorsTab::AddRecord() {
    bool isDialogOk;
    QString authorsName = QInputDialog::getText(this, "Add Record",
    "Input author:", QLineEdit::Normal, "", &isDialogOk);
    AuthorsDialogData author {0, authorsName};
    if (isDialogOk) {
        Status DBResponse = DataBaseManager::getInstance()->addAuthor(&author);
        if (DBResponse == Status::SUCCESS) {
            qDebug() << "Автор успешно добавлен в БД!";
           return true;
        } else if (DBResponse == Status::INVALID_ARG) {
            QMessageBox::information(this, "Добавить запись", "Такое имя уже существует!");
            qDebug() << "Ошибка: было введено уже существующее имя!";
            return false;
        }
        QMessageBox::information(this, "Добавить запись", "Ошибка базы данных при добавлении автора");
        qDebug() << "Ошибка базы данных при добавлении автора!";
        return false;
    }
    qDebug() << "Отмена диалога при добавления автора";
    return false;
}

bool AuthorsTab::EditRecord() {
    bool isDialogOk;
    QModelIndex selected = tab->currentIndex();
    if (!selected.isValid()){
        QMessageBox::information(this, "Изменить запись", "Выберите запись для изменения");
        qDebug() << "Ошибка: не была выбрана строка для удаления!";
        return false;
    }
    int row = selected.row();
    QModelIndex col1Cell = tab->model()->index(row,1);
    QModelIndex col0Cell = tab->model()->index(row,0);
    QString authorsName = QInputDialog::getText(this, "Add Record",
                                                "Input author:", QLineEdit::Normal, col1Cell.data().toString(), &isDialogOk);

    AuthorsDialogData author {col0Cell.data().toInt(), authorsName};
    if (isDialogOk) {
        Status DBResponse = DataBaseManager::getInstance()->editAuthor(&author);
        if (DBResponse == Status::SUCCESS) {
            qDebug() << "Автор успешно добавлен в БД!";
            return true;
        } else if (DBResponse == Status::INVALID_ARG) {
            QMessageBox::information(this, "Изменить запись", "Такое имя уже существует!");
            qDebug() << "Ошибка: было введено уже существующее имя!";
            return false;
        }
        QMessageBox::information(this, "Изменить запись", "Ошибка базы данных при изменении автора");
        qDebug() << "Ошибка базы данных при изменении автора!";
        return false;
    }
    qDebug() << "Отмена диалога при изменении автора";
    return false;
}
