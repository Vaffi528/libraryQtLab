#include "BookDialog.h"

BookDialog::BookDialog (QWidget* parent, BooksDialogData* book): QDialog(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    setUpWidgets(book);

    mainLayout->addWidget(bookEdit);
    mainLayout->addWidget(authorCombo);
    mainLayout->addWidget(genresList);

    QHBoxLayout* btnLayout = new QHBoxLayout(this);

    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);

    mainLayout->addLayout(btnLayout);

    connect(okBtn, &QPushButton::clicked, this, &BookDialog::onOkBtnClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &BookDialog::reject);
}

void BookDialog::setUpWidgets(BooksDialogData* book) {
    setUpPlainWidgets();
    if (book)
        bookEdit->setText(book->author);
    setUpListWidgets(book);
}

void BookDialog::setUpPlainWidgets() {
    bookEdit = new QLineEdit(this);
    okBtn = new QPushButton(this);
    cancelBtn = new QPushButton(this);
    okBtn->setText("Ok");
    cancelBtn->setText("Cancel");
}

void BookDialog::setUpListWidgets(BooksDialogData* book) {
    authorCombo = new QComboBox(this);
    genresList = new QListWidget(this);

    authorCombo->addItems(DataBaseManager::getInstance()->getVectorOf("authors"));
    genresList->addItems(DataBaseManager::getInstance()->getVectorOf("genres"));

    if (book) {
        for (int i = 0; i < genresList->count(); ++i) {
            QListWidgetItem* item = genresList->item(i);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            if (book->genres.contains(item->text()))
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
        }
    } else {
        for (int i = 0; i < genresList->count(); ++i) {
            QListWidgetItem* item = genresList->item(i);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void BookDialog::onOkBtnClicked() {
    if (bookEdit->text().isEmpty()) {
        QMessageBox::information(this, "Пустое поле", "Поле ввода имени автора оказалось пустым");
        return;
    }

    if (authorCombo->count() == 0) {
        QMessageBox::information(this, "Пустой список", "Похоже, Вы еще не добавили ни одного автора");
        return;
    }

    book.id = 0;
    book.name = bookEdit->text();
    book.author = authorCombo->currentText();

    for (int i = 0; i < genresList->count(); ++i) {
        QListWidgetItem* item = genresList->item(i);
        if (item->checkState() == Qt::Checked) {
            book.genres.append(item->text());
        }
    }

    if (book.genres.isEmpty()) {
        QMessageBox::information(this, "Пустой список", "Похоже, Вы не выбрали жанр для книги");
        return;
    }

    accept();
}

BooksDialogData BookDialog::getBook(bool* ok, QWidget* parent, BooksDialogData* book) {
    BookDialog dialog(parent, book);
    int status = dialog.exec();
    if (ok)
        *ok = (status == QDialog::Accepted);

    if (status == QDialog::Accepted)
        return dialog.book;

    return BooksDialogData();
}
