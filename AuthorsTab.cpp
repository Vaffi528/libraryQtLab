#include "AuthorsTab.h"

Status AuthorsTab::AddRecord() {
    bool isDialogOk;
    QString authorsName = QInputDialog::getText(this, "Add Record",
    "Input author:", QLineEdit::Normal, "", &isDialogOk);

    if (!isDialogOk) {
        qDebug() << "Отмена диалога при добавления автора";
        return Status::REJECT;
    }

    AuthorsDialogData author {0, authorsName};
    Status DBResponse = DataBaseManager::getInstance()->addAuthor(&author);
    if (DBResponse == Status::SUCCESS) {
        qDebug() << "Автор успешно добавлен в БД!";
        return Status::SUCCESS;
    } else if (DBResponse == Status::INVALID_ARG) {
        QMessageBox::information(this, "Добавить запись", "Такое имя уже существует или поле оказалось пустым!");
        qDebug() << "Ошибка: было введено уже существующее имя или поле оказалось пустым!";
        return Status::INVALID_ARG;
    }
    QMessageBox::information(this, "Добавить запись", "Ошибка базы данных при добавлении автора");
    qDebug() << "Ошибка базы данных при добавлении автора!";
    return Status::DB_QUERY_FAILED;

}

Status AuthorsTab::EditRecord() {
    bool isDialogOk;
    QModelIndex selected = tab->currentIndex();
    if (!selected.isValid()){
        QMessageBox::information(this, "Изменить запись", "Выберите запись для изменения");
        qDebug() << "Ошибка: не была выбрана строка для изменения!";
        return Status::INVALID_ARG;
    }
    int row = selected.row();
    QModelIndex col1Cell = tab->model()->index(row,1);
    QModelIndex col0Cell = tab->model()->index(row,0);
    QString authorsName = QInputDialog::getText(this, "Add Record",
                                                "Input author:", QLineEdit::Normal, col1Cell.data().toString(), &isDialogOk);

    if (!isDialogOk) {
        qDebug() << "Отмена диалога при изменении автора";
        return Status::REJECT;
    }

    AuthorsDialogData author {col0Cell.data().toInt(), authorsName};
    Status DBResponse = DataBaseManager::getInstance()->editAuthor(&author);
    if (DBResponse == Status::SUCCESS) {
        qDebug() << "Автор успешно добавлен в БД!";
        return Status::SUCCESS;
    } else if (DBResponse == Status::INVALID_ARG) {
        QMessageBox::information(this, "Изменить запись", "Такое имя уже существует!");
        qDebug() << "Ошибка: было введено уже существующее имя!";
        return Status::INVALID_ARG;
    }
    QMessageBox::information(this, "Изменить запись", "Ошибка базы данных при изменении автора");
    qDebug() << "Ошибка базы данных при изменении автора!";
    return Status::DB_QUERY_FAILED;
}

Status AuthorsTab::RemoveRecord() {
    QModelIndexList selectedItems = tab->selectionModel()->selectedIndexes();
    for (QModelIndex& selected : selectedItems){
        int row = selected.row();
        QModelIndex userId = tab->model()->index(row,0);
        AuthorsDialogData author {userId.data().toInt(), tab->model()->index(row,0).data().toString()};
        Status DBResponse = DataBaseManager::getInstance()->removeAuthor(&author);
        if (DBResponse == Status::DB_QUERY_FAILED) {
            QMessageBox::information(this, "Удалить запись", "Ошибка базы данных при удалении автора");
            qDebug() << "Ошибка базы данных при удалении автора!";
            return Status::DB_QUERY_FAILED;
        }
    }
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Удалить запись", "Выберите запись для удаления");
        qDebug() << "Ошибка: не была выбрана строка для удаления!";
        return Status::INVALID_ARG;
    }
    qDebug() << "Авторы успешно удалены из БД!";
    return Status::SUCCESS;
    }
