#include "BookDialog.h"

BookDialog::BookDialog (QWidget* parent): QDialog(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    setUpWidgets();

    mainLayout->addWidget(bookEdit);
    mainLayout->addWidget(authorCombo);
    mainLayout->addWidget(genresList);
    mainLayout->addWidget(okBtn);

    connect(okBtn, &QPushButton::clicked, this, &BookDialog::onOkBtnClicked);
}

void BookDialog::setUpWidgets() {
    bookEdit = new QLineEdit(this);
    authorCombo = new QComboBox(this);
    genresList = new QListWidget(this);
    okBtn = new QPushButton(this);
    okBtn->setText("Ok");

    authorCombo->addItems(DataBaseManager::getInstance()->getVectorOf("authors"));
    genresList->addItems(DataBaseManager::getInstance()->getVectorOf("genres"));

    for (int i = 0; i < genresList->count(); ++i) {
        QListWidgetItem* item = genresList->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }
}

void BookDialog::onOkBtnClicked() {
    book.id = 0;
    book.name = bookEdit->text();
    book.author = authorCombo->currentText();

    for (int i = 0; i < genresList->count(); ++i) {
        QListWidgetItem* item = genresList->item(i);
        if (item->checkState() == Qt::Checked) {
            book.genres.append(item->text());
        }
    }

    accept();
}

BooksDialogData BookDialog::getBook(bool* ok, QWidget* parent) {
    BookDialog dialog(parent);
    int status = dialog.exec();
    if (ok)
        *ok = (status == QDialog::Accepted);

    if (status == QDialog::Accepted)
        return dialog.book;

    return BooksDialogData();
}
