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
        QVector<QString> getGenresNamesByBookId(bool* ok, int id);
        QString getAuthorNameByAuthorId(int id);
        QString getGenreNameByGenreId(int id);
        QString getBookNameByBookId(int id);

        int getBookIdByBookName(QString name);
        int getBookIdByAuthorId(int id);
        int getAuthorIdByBookId(int id);

        int getGenreIdByGenreName(QString name);
        int getAuthorIdByAuthorName(QString name);

        QVector<QString> getVectorOf(QString tableType);

    private:
        Status addPlainRecord(const QString& name, QString tableName);
        Status editPlainRecord(const QString& name, int id, QString tableName);
        Status removePlainRecord(int id, QString tableName);
        int getIdByX(QString name, QString tableName);
        QString getXById(int id, QString tableName);

    private:
        DataBaseManager() = default;
        DataBaseManager(const DataBaseManager&) = delete;
        DataBaseManager& operator=(const DataBaseManager&) = delete;
        ~DataBaseManager() = default;

};

#endif // DATABASE_H
