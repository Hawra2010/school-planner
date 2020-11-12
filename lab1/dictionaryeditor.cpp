#include "dictionaryeditor.h"

DictionaryEditor::DictionaryEditor(QWidget* parent, QStringList& list) : QDialog(parent), data(list) {

    //create a list model that will store all of our dictionary information
    list_model = new QStringListModel;
    list_model->setStringList(data);

    //create a listview to store our information that will be viewed
    listview = new QListView;
    listview->setModel(list_model);

    //create a layout for the window and set it
    auto layout = new QVBoxLayout;
    setLayout(layout);


    //create a layout for the buttons
    QHBoxLayout *button_layout = new QHBoxLayout;

    //add the list view and the buttons layout to the window
    layout->addWidget(listview);
    layout->addLayout(button_layout);

    //create the buttons
    auto btn_add = new QPushButton(tr("Add New"));
    auto btn_remove = new QPushButton(tr("Remove"));
    auto btn_close = new QPushButton(tr("Close"));

    //add buttons to widget
    button_layout->addWidget(btn_add);
    button_layout->addWidget(btn_remove);
    button_layout->addWidget(btn_close);


    //add icon to the delete button
    QPixmap deletePixmap(":/files/resources/delete.png");
    QIcon deletebUttonIcon(deletePixmap);
    btn_remove->setIcon(deletebUttonIcon);


    //add icon to the close button
    QPixmap closePixmap(":/files/resources/close.png");
    QIcon closeButtonIcon(closePixmap);
    btn_close->setIcon(closeButtonIcon);


    //add icon to the add button
    QPixmap addPixmap(":/files/resources/add.png");
    QIcon addButtonIcon(addPixmap);
    btn_add->setIcon(addButtonIcon);


    //create a listener to the buttons
    connect(btn_add, &QPushButton::released, this, &DictionaryEditor::addElement);
    connect(btn_remove, &QPushButton::released, this, &DictionaryEditor::removeElement);
    connect(btn_close, &QPushButton::released, this, &DictionaryEditor::closeDialog);
}

void DictionaryEditor::addElement(void) {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add a new element to the dictionary"), tr("Value:"), QLineEdit::Normal, tr(""), &ok);
    //if confirmed and the test is not empty, append to the list and update the list
    if (ok && !text.isEmpty()) {
        data.append(text);
        list_model->setStringList(data);
    }
}

void DictionaryEditor::removeElement(void) {
    //get the currently selected indexes
    auto selected = listview->selectionModel()->selectedIndexes();
    //loop through all of the selected indexes
    for(auto iter = selected.begin(); iter != selected.end(); iter++) {
        //remove from the list
        data.removeAt(iter->row());
    }
    //reset the list
    list_model->setStringList(data);
}

void DictionaryEditor::closeDialog(void) {
    accept();
}
