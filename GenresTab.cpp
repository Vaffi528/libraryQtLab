#include "GenresTab.h"

// в связи с дублированием кода из authors tab, возможно, лучше было бы сделать эти методы абстрактными и вызывать их с соответствующими лейблами для
// auhtorsTab и genresTab. Но, т.к. эти методы нигде больше не будут использованы и вряд-ли расширятся, будет проще и быстрее их просто скопировать.
// Хотя это нарушит принцип DRY, я принял такое решение, что в данном случае это не является критичным для моей архитектуры.

bool GenresTab::AddRecord() {
    bool isDialogOk;
    QString genresName = QInputDialog::getText(this, "Add Record",
    "Input genre:", QLineEdit::Normal, "", &isDialogOk);
    GenresDialogData genre {0, genresName};
    if (isDialogOk) {
        Status DBResponse = DataBaseManager::getInstance()->addGenre(&genre);
        if (DBResponse == Status::SUCCESS) {
            qDebug() << "Жанр успешно добавлен в БД!";
           return true;
        } else if (DBResponse == Status::INVALID_ARG) {
            QMessageBox::information(this, "Добавить запись", "Такой жанр уже существует или поле оказалось пустым!");
            qDebug() << "Ошибка: был введен уже существующий жанр или поле оказалось пустым!";
            return false;
        }
        QMessageBox::information(this, "Добавить запись", "Ошибка базы данных при добавлении жанра");
        qDebug() << "Ошибка базы данных при добавлении жанра!";
        return false;
    }
    qDebug() << "Отмена диалога при добавления жанра";
    return false;
}

bool GenresTab::EditRecord() {
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
    QString genresName = QInputDialog::getText(this, "Add Record",
                                                "Input genre:", QLineEdit::Normal, col1Cell.data().toString(), &isDialogOk);

    GenresDialogData genre {col0Cell.data().toInt(), genresName};
    if (isDialogOk) {
        Status DBResponse = DataBaseManager::getInstance()->editGenre(&genre);
        if (DBResponse == Status::SUCCESS) {
            qDebug() << "Жанр успешно добавлен в БД!";
            return true;
        } else if (DBResponse == Status::INVALID_ARG) {
            QMessageBox::information(this, "Изменить запись", "Такой жанр уже существует!");
            qDebug() << "Ошибка: был введен уже существующий жанр!";
            return false;
        }
        QMessageBox::information(this, "Изменить запись", "Ошибка базы данных при изменении жанра");
        qDebug() << "Ошибка базы данных при изменении жанра!";
        return false;
    }
    qDebug() << "Отмена диалога при изменении жанра";
    return false;
}

bool GenresTab::RemoveRecord() {
    QModelIndexList selectedItems = tab->selectionModel()->selectedIndexes();
    for (QModelIndex& selected : selectedItems){
        int row = selected.row();
        QModelIndex genreId = tab->model()->index(row,0);
        GenresDialogData genre {genreId.data().toInt(), tab->model()->index(row,0).data().toString()};
        Status DBResponse = DataBaseManager::getInstance()->removeGenre(&genre);
        if (DBResponse == Status::DB_QUERY_FAILED) {
            QMessageBox::information(this, "Удалить запись", "Ошибка базы данных при удалении жанра");
            qDebug() << "Ошибка базы данных при удалении жанра!";
            return false;
        }
    }
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Удалить запись", "Выберите запись для удаления");
        qDebug() << "Ошибка: не была выбрана строка для удаления!";
        return false;
    }
    qDebug() << "Жанры успешно удалены из БД!";
    return true;
    }
