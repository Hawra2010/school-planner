#ifndef DICTIONARYEDITOR_H
#define DICTIONARYEDITOR_H

#include <QDialog>
#include <QListView>
#include <QFormLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringListModel>
#include "schoolplanner.h"

class DictionaryEditor : public QDialog {
    Q_OBJECT

public:
    DictionaryEditor(QWidget* parent, QStringList& list); //constructor that takes the parent and list to be modified

private slots:
    void addElement(void); //listener to add a new element to the dictionary
    void removeElement(void); //listener to remove element from the dictionary
    void closeDialog(void); //listener to close the dialog

private:
    QStringListModel* list_model; //the list model
    QStringList& data; //the main list
    QListView* listview; //listview which is a component where our information will be displayed
};


#endif // DICTIONARYEDITOR_H
