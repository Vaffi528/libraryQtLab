#include "database.h"

DataBaseManager* DataBaseManager::getInstance(){
    static DataBaseManager instance;
    return &instance;
}

Status DataBaseManager::createTables() {
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
        return Status::DB_SETUP_FAILED;
    }

    qDebug() << "Таблицы созданы успешно!";
    return Status::SUCCESS;
};

//AUTHORS
Status DataBaseManager::addAuthor(const AuthorsDialogData* data){
    if (data->name.isEmpty())
        return Status::INVALID_ARG;
    QSqlQuery query;
    query.prepare("SELECT id FROM authors WHERE author = :author");
    query.bindValue(":author", data->name);
    query.exec();
    if (query.next()) {
        return Status::INVALID_ARG;
    }
    query.prepare("INSERT INTO authors(author) VALUES (:name)");
    query.bindValue(":name", data->name);
    bool isAdded = query.exec();
    if (isAdded)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

Status DataBaseManager::editAuthor(const AuthorsDialogData* data) {
    QSqlQuery query;
    query.prepare("SELECT id FROM authors WHERE author = :author");
    query.bindValue(":author", data->name);
    query.exec();
    if (query.next()) {
        return Status::INVALID_ARG;
    }
    query.prepare("UPDATE authors SET author = :author WHERE id = :id");
    query.bindValue(":author", data->name);
    query.bindValue(":id", data->id);
    bool isAdded = query.exec();
    if (isAdded)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

Status DataBaseManager::removeAuthor(const AuthorsDialogData* data) {
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
    query.prepare("SELECT author FROM authors WHERE id = :id");
    query.bindValue(":id", data->id);
    query.exec();
    if (query.next()){
        query.prepare("DELETE FROM authors WHERE id = :id");
        query.bindValue(":id", data->id);
        bool isDeleted = query.exec();
        if (isDeleted)
            return Status::SUCCESS;
        return Status::DB_QUERY_FAILED;
    }
    return Status::DB_QUERY_FAILED;
}


// GENRES
Status DataBaseManager::addGenre(const GenresDialogData* data){
    if (data->name.isEmpty())
        return Status::INVALID_ARG;
    QSqlQuery query;
    query.prepare("SELECT id FROM genres WHERE genre = :genre");
    query.bindValue(":genre", data->name);
    query.exec();
    if (query.next()) {
        return Status::INVALID_ARG;
    }
    query.prepare("INSERT INTO genres(genre) VALUES (:genre)");
    query.bindValue(":genre", data->name);
    bool isAdded = query.exec();
    if (isAdded)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

Status DataBaseManager::editGenre(const GenresDialogData* data) {
    QSqlQuery query;
    query.prepare("SELECT id FROM genres WHERE genre = :genre");
    query.bindValue(":genre", data->name);
    query.exec();
    if (query.next()) {
        return Status::INVALID_ARG;
    }
    query.prepare("UPDATE genres SET genre = :genre WHERE id = :id");
    query.bindValue(":genre", data->name);
    query.bindValue(":id", data->id);
    bool isAdded = query.exec();
    if (isAdded)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

Status DataBaseManager::removeGenre(const GenresDialogData* data) {
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
    query.prepare("SELECT genre FROM genres WHERE id = :id");
    query.bindValue(":id", data->id);
    query.exec();
    if (query.next()){
        query.prepare("DELETE FROM genres WHERE id = :id");
        query.bindValue(":id", data->id);
        bool isDeleted = query.exec();
        if (isDeleted)
            return Status::SUCCESS;
        return Status::DB_QUERY_FAILED;
    }
    return Status::DB_QUERY_FAILED;
}

QVector<QString> DataBaseManager::getVectorOf(QString tableType) {
    QVector<QString> vector;
    QSqlQuery query;

    query.prepare("SELECT " + tableType.chopped(1) + " FROM " + tableType);
    query.exec();
    while (query.next()){
        vector.push_back(query.value(0).toString());
    }
    return vector;
}

// BOOKS
Status DataBaseManager::addBook(const BooksDialogData* data){
    QSqlQuery query;

    int existingBookId = getBookIdByBookName(data->name);
    if (existingBookId != -1)
        return Status::INVALID_ARG;

    query.prepare("INSERT INTO books (author_id, book) VALUES ((SELECT id FROM authors WHERE author = :author), :book)");
    query.bindValue(":author", data->author);
    query.bindValue(":book", data->name);
    bool isInserted = query.exec();

    if (!isInserted)
        return Status::DB_QUERY_FAILED;

    int bookId = query.lastInsertId().toInt();

    return assignGenreToBook(data->genres, bookId);

}

Status DataBaseManager::assignGenreToBook(const QVector<QString>& genres, int bookId){
    QSqlQuery query;
    QString request = "INSERT INTO books_genres (book_id, genre_id) VALUES ";

    for (const QString& genre : genres) {
        request += "(?, (SELECT id FROM genres WHERE genre = ?)), ";
    }

    query.prepare(request.chopped(2));

    int placeholderIndex = 0;
    for (const QString& genre : genres) {
        query.bindValue(placeholderIndex++, bookId);
        query.bindValue(placeholderIndex++, genre);
    }

    bool isInserted = query.exec();
    if (isInserted)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}
// TODO: переименовать
QString DataBaseManager::getAuthorById(int id) {
    QSqlQuery query;
    query.prepare("SELECT author FROM authors WHERE id = :id");
    query.bindValue(":id", id);
    bool isOk = query.exec();
    if (!isOk)
        return QString();
    if (query.next()){
        return query.value(0).toString();
    }
    return QString();

}
// TODO: переименовать
QVector<QString> DataBaseManager::getGenresByBookId(bool* ok, int id) {
    QSqlQuery query;
    query.prepare("SELECT genre_id FROM books_genres WHERE book_id = :id");
    query.bindValue(":id", id);
    *ok = query.exec();
    if (!*ok)
        return QVector<QString>();

    QVector<QString> genres;
    while (query.next()){
        genres.push_back(getGenreById(query.value(0).toInt()));
    }
    return genres;
}
// TODO: переименовать
QString DataBaseManager::getGenreById(int id) {
    QSqlQuery query;
    query.prepare("SELECT genre FROM genres WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    if (query.next())
        return query.value(0).toString();
    return QString();
}

int DataBaseManager::getBookIdByBookName(QString name) {
    QSqlQuery query;
    query.prepare("SELECT id FROM books WHERE book = :book");
    query.bindValue(":book", name);
    query.exec();
    if (query.next())
        return query.value(0).toInt();
    return -1;
}

