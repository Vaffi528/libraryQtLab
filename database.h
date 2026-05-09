#ifndef DATABASE_H
#define DATABASE_H

#include "headers.h"

class DataBaseManager {
    public:
        bool createTables();

        bool addAuthor();
        bool addBook();
        bool assignGenreToBook();
};

#endif // DATABASE_H
