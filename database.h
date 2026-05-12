#ifndef DATABASE_H
#define DATABASE_H

#include "headers.h"
#include "DialogsData.h"

class DataBaseManager {
    public:
        static DataBaseManager* getInstance();

    public:
        bool createTables();

        bool addAuthor(const AuthorsDialogData* data);
        bool addBook(/* const BooksDialogData* data */);
        bool assignGenreToBook(/* const GenresDialogData* data */);

    private:
        DataBaseManager() = default;
        DataBaseManager(const DataBaseManager&) = delete;
        DataBaseManager& operator=(const DataBaseManager&) = delete;
        ~DataBaseManager() = default;

};

#endif // DATABASE_H
