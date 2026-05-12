#include "database.h"

DataBaseManager* DataBaseManager::getInstance(){
    static DataBaseManager instance;
    return &instance;
}

bool DataBaseManager::createTables() {
    QSqlQuery query;
    bool isOk1 = query.exec("CREATE TABLE IF NOT EXISTS authors ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "author TEXT NOT NULL)");

    bool isOk2 = query.exec("CREATE TABLE IF NOT EXISTS books ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "author_id INTEGER NOT NULL, "
               "book TEXT NOT NULL, "
               "FOREIGN KEY(author_id) REFERENCES authors(id) ON DELETE CASCADE)");

    bool isOk3 = query.exec("CREATE TABLE IF NOT EXISTS genres ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "genre TEXT NOT NULL)");

    bool isOk4 = query.exec("CREATE TABLE IF NOT EXISTS books_genres ("
               "book_id INTEGER NOT NULL, "
               "genre_id INTEGER NOT NULL, "
               "PRIMARY KEY(book_id, genre_id), "
               "FOREIGN KEY(book_id) REFERENCES books(id) ON DELETE CASCADE, "
               "FOREIGN KEY(genre_id) REFERENCES genres(id) ON DELETE CASCADE)");

    if (!(isOk1 && isOk2 && isOk3 && isOk4)) {
        qDebug() << "Ошибка при создании таблиц!";
        return false;
    }
    qDebug() << "Таблицы созданы успешно!";
    return true;
};

bool DataBaseManager::addAuthor(const AuthorsDialogData* data){
    QSqlQuery query;
    query.prepare("INSERT INTO authors(author) VALUES (:name)");
    query.bindValue(":name", data->name);
    bool isAdded = query.exec();
    if (isAdded)
        return true;
    return false;
}
//bool DataBaseManager::addBook(const BooksDialogData* data);
//bool DataBaseManager::assignGenreToBook(const GenresDialogData* data);
