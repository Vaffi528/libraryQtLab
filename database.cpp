#include "database.h"

DataBaseManager* DataBaseManager::getInstance(){
    static DataBaseManager instance;
    return &instance;
}

Status DataBaseManager::createTables() {
    QSqlQuery query;
    bool isOk1 = query.exec("CREATE TABLE IF NOT EXISTS authors ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "author TEXT NOT NULL UNIQUE)");

    bool isOk2 = query.exec("CREATE TABLE IF NOT EXISTS books ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "author_id INTEGER NOT NULL, "
               "book TEXT NOT NULL, "
               "FOREIGN KEY(author_id) REFERENCES authors(id) ON DELETE CASCADE)");

    bool isOk3 = query.exec("CREATE TABLE IF NOT EXISTS genres ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "genre TEXT NOT NULL UNIQUE)");

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

// GENERAL METHODS
Status DataBaseManager::addPlainRecord(const QString& name, QString tableName) {
    if (name.isEmpty())
        return Status::INVALID_ARG;

    int id = getIdByX(name, tableName);
    if (id != -1)
        return Status::INVALID_ARG;

    QSqlQuery query;
    query.prepare("INSERT INTO " + tableName + "(" + tableName.chopped(1) + ") VALUES (:name)");
    query.bindValue(":name", name);
    bool isAdded = query.exec();
    if (isAdded)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

Status DataBaseManager::editPlainRecord(const QString& name, int id, QString tableName) {
    if (name.isEmpty())
        return Status::INVALID_ARG;

    int existingId = getIdByX(name, tableName);
    if (existingId != -1)
        return Status::INVALID_ARG;

    QSqlQuery query;
    query.prepare("UPDATE " + tableName + " SET " + tableName.chopped(1) + " = :name WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    bool isAdded = query.exec();
    if (isAdded)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

Status DataBaseManager::removePlainRecord(int id, QString tableName) {
    QString name = getXById(id, tableName);
    if (!name.isEmpty()){
        QSqlQuery query;
        query.prepare("DELETE FROM " + tableName + " WHERE id = :id");
        query.bindValue(":id", id);
        bool isDeleted = query.exec();
        if (isDeleted)
            return Status::SUCCESS;
        return Status::DB_QUERY_FAILED;
    }
    return Status::DB_QUERY_FAILED;
}

int DataBaseManager::getIdByX(QString name, QString tableName) {
    QSqlQuery query;
    query.prepare("SELECT id FROM " + tableName + " WHERE " + tableName.chopped(1) + " = :X");
    query.bindValue(":X", name);
    query.exec();
    if (query.next())
        return query.value(0).toInt();
    return -1;
}

QString DataBaseManager::getXById(int id, QString tableName) {
    QSqlQuery query;
    query.prepare("SELECT " + tableName.chopped(1) + " FROM " + tableName + " WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    if (query.next())
        return query.value(0).toString();
    return QString();
}

//AUTHORS
Status DataBaseManager::addAuthor(const AuthorsDialogData* data){
    return addPlainRecord(data->name, "authors");
}

Status DataBaseManager::editAuthor(const AuthorsDialogData* data) {
    return editPlainRecord(data->name, data->id, "authors");
}

Status DataBaseManager::removeAuthor(const AuthorsDialogData* data) {
    return removePlainRecord(data->id, "authors");
}


// GENRES
Status DataBaseManager::addGenre(const GenresDialogData* data){
    return addPlainRecord(data->name, "genres");
}

Status DataBaseManager::editGenre(const GenresDialogData* data) {
    return editPlainRecord(data->name, data->id, "genres");
}

Status DataBaseManager::removeGenre(const GenresDialogData* data) {
    return removePlainRecord(data->id, "genres");
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

    BooksDialogData bookCopy;

    bookCopy = *data;
    bookCopy.id = bookId;

    return assignGenreToBook(&bookCopy);

}

Status DataBaseManager::editBook(const BooksDialogData* data){
    QSqlQuery query;

    int existingBookId = getBookIdByBookName(data->name);
    if (existingBookId != -1 && existingBookId != data->id)
        return Status::INVALID_ARG;

    query.prepare("UPDATE books SET author_id = (SELECT id FROM authors WHERE author = :author), book = :book WHERE id = :id");
    query.bindValue(":author", data->author);
    query.bindValue(":book", data->name);
    query.bindValue(":id", data->id);
    bool isInserted = query.exec();

    if (!isInserted)
        return Status::DB_QUERY_FAILED;

    return updateGenreToBookTable(data);
}

Status DataBaseManager::removeBook(const BooksDialogData* data) {
    return removePlainRecord(data->id, "books");
}

Status DataBaseManager::assignGenreToBook(const BooksDialogData* data){
    if (data->genres.isEmpty())
        return Status::SUCCESS;

    QSqlQuery query;
    QString request = "INSERT INTO books_genres (book_id, genre_id) VALUES ";

    for (const QString& genre : data->genres) {
        request += "(?, (SELECT id FROM genres WHERE genre = ?)), ";
    }

    query.prepare(request.chopped(2));

    int placeholderIndex = 0;
    for (const QString& genre : data->genres) {
        query.bindValue(placeholderIndex++, data->id);
        query.bindValue(placeholderIndex++, genre);
    }

    bool isInserted = query.exec();
    if (isInserted)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

Status DataBaseManager::updateGenreToBookTable(const BooksDialogData* data){
    QSqlQuery query;
    int bookId = data->id;
    QVector<QString> genresCopy = data->genres;

    // сразу проверка пересечения множества genresCopy и множества жанров до изменения
    query.prepare("SELECT genre_id FROM books_genres WHERE book_id = :book_id");
    query.bindValue(":book_id", bookId);
    query.exec();

    while(query.next()){
        int genreId = query.value(0).toInt();
        QString genre = getGenreNameByGenreId(genreId);
        if (genresCopy.contains(genre)){
            genresCopy.removeAll(genre);
        } else {
            deleteGenreToBookConnectionByIds(bookId, genreId);
        }
    }

    // далее добавление элементов разности множества genresCopy и множества жанров до изменения
    for (const QString& genre : genresCopy) {
        int genreId = getGenreIdByGenreName(genre);

        if (genreId == -1) {
            qDebug() << "Предупреждение: в БД не оказалось жарна" << genre;
            continue;
        }

        Status status = addGenreToBookConnectionByIds(bookId, genreId);
        if (status != Status::SUCCESS){
            return Status::DB_QUERY_FAILED;
        }
    }

    return Status::SUCCESS;
}

Status DataBaseManager::deleteGenreToBookConnectionByIds(int bookId, int genreId){
    QSqlQuery query;
    query.prepare("DELETE FROM books_genres WHERE book_id = :book_id AND genre_id = :genre_id");
    query.bindValue(":book_id", bookId);
    query.bindValue(":genre_id", genreId);
    bool isDeleted = query.exec();
    if (isDeleted)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}
Status DataBaseManager::addGenreToBookConnectionByIds(int bookId, int genreId) {
    QSqlQuery query;
    query.prepare("INSERT INTO books_genres (book_id, genre_id) VALUES (:book_id, :genre_id)");
    query.bindValue(":book_id", bookId);
    query.bindValue(":genre_id", genreId);
    bool isAdded = query.exec();
    if (isAdded)
        return Status::SUCCESS;
    return Status::DB_QUERY_FAILED;
}

// TODO: переименовать
QString DataBaseManager::getAuthorNameByAuthorId(int id) {
    return getXById(id, "authors");
}

int DataBaseManager::getAuthorIdByBookId(int id) {
    QSqlQuery query;
    query.prepare("SELECT author_id FROM books WHERE id = :id");
    query.bindValue(":id", id);
    bool isOk = query.exec();
    if (!isOk)
        return 0;
    if (query.next()){
        return query.value(0).toInt();
    }
    return 0;

}

QVector<QString> DataBaseManager::getGenresNamesByBookId(bool* ok, int id) {
    QSqlQuery query;
    query.prepare("SELECT genre_id FROM books_genres WHERE book_id = :id");
    query.bindValue(":id", id);
    *ok = query.exec();
    if (!*ok)
        return QVector<QString>();

    QVector<QString> genres;
    while (query.next()){
        genres.push_back(getGenreNameByGenreId(query.value(0).toInt()));
    }
    return genres;
}

QString DataBaseManager::getBookNameByBookId(int id) {
    return getXById(id, "books");
}

QString DataBaseManager::getGenreNameByGenreId(int id) {
    return getXById(id, "genres");
}

int DataBaseManager::getBookIdByBookName(QString name) {
    return getIdByX(name, "books");
}

int DataBaseManager::getBookIdByAuthorId(int id){
    QSqlQuery query;
    query.prepare("SELECT id FROM books WHERE author_id = :author_id");
    query.bindValue(":author_id", id);
    query.exec();
    if (query.next())
        return query.value(0).toInt();
    return -1;
}

int DataBaseManager::getAuthorIdByAuthorName(QString name) {
    return getIdByX(name, "authors");
}

int DataBaseManager::getGenreIdByGenreName(QString name) {
    return getIdByX(name, "genres");
}


