#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include "headers.h"

struct AuthorsDialogData {
    int id;
    QString name;
};

struct BooksDialogData {
    int id;
    QString name;
    QString author;
    QVector<QString> genres;
};

struct GenresDialogData {
    int id;
    QString name;
};

#endif // DIALOGDATA_H
