#ifndef DATABASE_H
#define DATABASE_H

#include "headers.h"
#include "DialogsData.h"
#include "CodeStatus.h"

class DataBaseManager {
    public:
        static DataBaseManager* getInstance();

    public:
        Status createTables();

        Status addAuthor(const AuthorsDialogData* data);
        Status addBook(/* const BooksDialogData* data */);
        Status addGenre(const GenresDialogData* data);
        Status assignGenreToBook(const GenresDialogData* data);

        Status editAuthor(const AuthorsDialogData* data);
        Status editBook(/* const BooksDialogData* data */);
        Status editGenre(const GenresDialogData* data);

        Status removeAuthor(const AuthorsDialogData* data);
        Status removeBook(/* const BooksDialogData* data */);
        Status removeGenre(const GenresDialogData* data);

        QVector<QString> getVectorOf(QString tableType);

    private:
        DataBaseManager() = default;
        DataBaseManager(const DataBaseManager&) = delete;
        DataBaseManager& operator=(const DataBaseManager&) = delete;
        ~DataBaseManager() = default;

};

#endif // DATABASE_H
