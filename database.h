#ifndef DATABASE_H
#define DATABASE_H

#include "headers.h"
#include "DialogsData.h"
#include "CodeStatus.h"


// TODO: зарефакторить
class DataBaseManager {
    public:
        static DataBaseManager* getInstance();

    public:
        Status createTables();

        Status addAuthor(const AuthorsDialogData* data);
        Status addBook(const BooksDialogData* data);
        Status addGenre(const GenresDialogData* data);

        Status assignGenreToBook(const BooksDialogData* data);
        Status updateGenreToBookTable(const BooksDialogData* data);

        Status deleteGenreToBookConnectionByIds(int bookId, int genreId);
        Status addGenreToBookConnectionByIds(int bookId, int genreId);

        Status editAuthor(const AuthorsDialogData* data);
        Status editBook(const BooksDialogData* data);
        Status editGenre(const GenresDialogData* data);

        Status removeAuthor(const AuthorsDialogData* data);
        Status removeBook(const BooksDialogData* data);
        Status removeGenre(const GenresDialogData* data);

        // TODO: вместо этих методов сделать пару гибких методов с QVariant
        QString getAuthorById(int id);
        QVector<QString> getGenresByBookId(bool* ok, int id);
        QString getGenreById(int id);
        int getBookIdByBookName(QString name);
        int getBookIdByAuthorId(int id);
        int getAuthorIdByBookId(int id);

        QVector<QString> getVectorOf(QString tableType);

    private:
        DataBaseManager() = default;
        DataBaseManager(const DataBaseManager&) = delete;
        DataBaseManager& operator=(const DataBaseManager&) = delete;
        ~DataBaseManager() = default;

};

#endif // DATABASE_H
