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
    bool isDialogOk;
    QModelIndex selected = tab->currentIndex();
    if (!selected.isValid()){
        QMessageBox::information(this, "Изменить запись", "Выберите запись для изменения");
        qDebug() << "Ошибка: не была выбрана строка для изменения!";
        return Status::INVALID_ARG;
    }
    int row = selected.row();
    int pk = tab->model()->index(row,0).data().toInt();
    int authorId = tab->model()->index(row,1).data().toInt();
    QString bookName = tab->model()->index(row,1).data().toString();

    BooksDialogData book;
    book.id = pk;
    book.name = bookName;

    bool isGenresGot;
    book.author = DataBaseManager::getInstance()->getAuthorById(authorId);
    book.genres = DataBaseManager::getInstance()->getGenresByBookId(&isGenresGot, pk);

    if (!isGenresGot){
        qDebug() << "Ошибка базы данных при изменении книги!";
        return Status::DB_QUERY_FAILED;
    }

    bool isGot;
    BooksDialogData newBook = BookDialog::getBook(&isGot, this, &book);
    if (!isGot) {
        return Status::REJECT;
    }

    // TODO: доделать метод

}
