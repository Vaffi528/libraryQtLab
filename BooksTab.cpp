#include "BooksTab.h"

Status BooksTab::AddRecord() {
    bool isGot;
    BooksDialogData book = BookDialog::getBook(&isGot, this);
    if (!isGot) {
        return Status::REJECT;
    }

    Status DBResponse = DataBaseManager::getInstance()->addBook(&book);

    if (DBResponse == Status::SUCCESS) {
        qDebug() << "Книга успешно добавлена в БД!";
        return Status::SUCCESS;
    } else if (DBResponse == Status::INVALID_ARG) { // TODO: исправить, не работает корректно
        QMessageBox::information(this, "Добавить запись", "Такое имя уже существует или поле оказалось пустым!");
        qDebug() << "Ошибка: было введено уже существующее имя или поле оказалось пустым!";
    }

    qDebug() << "Ошибка базы данных при добавлении книги!";
    return Status::DB_QUERY_FAILED;
}

Status BooksTab::EditRecord() {
    QModelIndex selected = tab->currentIndex();
    DataBaseManager* manager = DataBaseManager::getInstance();

    if (!selected.isValid()){
        QMessageBox::information(this, "Изменить запись", "Выберите запись для изменения");
        qDebug() << "Ошибка: не была выбрана строка для изменения!";
        return Status::INVALID_ARG;
    }
    int row = selected.row();
    int pk = tab->model()->index(row,0).data().toInt();
    int authorId = manager->getAuthorIdByBookId(pk);

    QString bookName = tab->model()->index(row,2).data().toString();

    BooksDialogData book;
    book.id = pk;
    book.name = bookName;

    bool isGenresGot;
    book.author = manager->getAuthorNameByAuthorId(authorId);
    book.genres = manager->getGenresNamesByBookId(&isGenresGot, pk);

    if (!isGenresGot){
        qDebug() << "Ошибка базы данных при изменении книги!";
        return Status::DB_QUERY_FAILED;
    }

    bool isGot;
    BooksDialogData newBook = BookDialog::getBook(&isGot, this, &book);
    if (!isGot) {
        return Status::REJECT;
    }

    Status DBResponse = DataBaseManager::getInstance()->editBook(&newBook);
    if (DBResponse == Status::SUCCESS) {
        qDebug() << "Книга успешно изменена!";
        return Status::SUCCESS;
    } else if (DBResponse == Status::INVALID_ARG) {
        QMessageBox::information(this, "Изменить запись", "Такое имя уже существует!");
        qDebug() << "Ошибка: было введено уже существующее имя!";
        return Status::INVALID_ARG;
    }

    QMessageBox::information(this, "Изменить запись", "Ошибка базы данных при изменении книги");
    qDebug() << "Ошибка базы данных при изменении книги!";
    return Status::DB_QUERY_FAILED;

}

Status BooksTab::RemoveRecord() {
    QModelIndexList selectedItems = tab->selectionModel()->selectedIndexes();
    for (QModelIndex& selected : selectedItems){
        int row = selected.row();
        QModelIndex bookId = tab->model()->index(row,0);
        BooksDialogData book {bookId.data().toInt(), QString(), QString(), QVector<QString>()};
        Status DBResponse = DataBaseManager::getInstance()->removeBook(&book);
        if (DBResponse == Status::DB_QUERY_FAILED) {
            QMessageBox::information(this, "Удалить запись", "Ошибка базы данных при удалении книги");
            qDebug() << "Ошибка базы данных при удалении книги!";
            return Status::DB_QUERY_FAILED;
        }
    }
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Удалить запись", "Выберите запись для удаления");
        qDebug() << "Ошибка: не была выбрана строка для удаления!";
        return Status::INVALID_ARG;
    }
    qDebug() << "Книги успешно удалены из БД!";
    return Status::SUCCESS;
}
