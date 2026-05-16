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
            QMessageBox::information(this, "Добавить запись", "Такое имя уже существует или поле оказалось пустым!");
            qDebug() << "Ошибка: было введено уже существующее имя или поле оказалось пустым!";
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
        qDebug() << "Ошибка: не была выбрана строка для изменения!";
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

bool AuthorsTab::RemoveRecord() {
    QModelIndexList selectedItems = tab->selectionModel()->selectedIndexes();
    for (QModelIndex& selected : selectedItems){
        int row = selected.row();
        QModelIndex userId = tab->model()->index(row,0);
        AuthorsDialogData author {userId.data().toInt(), tab->model()->index(row,0).data().toString()};
        Status DBResponse = DataBaseManager::getInstance()->removeAuthor(&author);
        if (DBResponse == Status::DB_QUERY_FAILED) {
            QMessageBox::information(this, "Удалить запись", "Ошибка базы данных при удалении автора");
            qDebug() << "Ошибка базы данных при удалении автора!";
            return false;
        }
    }
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Удалить запись", "Выберите запись для удаления");
        qDebug() << "Ошибка: не была выбрана строка для удаления!";
        return false;
    }
    qDebug() << "Авторы успешно удалены из БД!";
    return true;
    }
