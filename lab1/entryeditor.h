#ifndef ENTRYEDITORDIALOG_H
#define ENTRYEDITORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include "schoolplanner.h"

class EntryEditor : public QDialog
{
    Q_OBJECT

private:

    SchoolPlanner * schoolPlanner; //reference to the school planner
    Activity activity; //the activity being modified
    QPushButton *btn_save; //reference to the save button

    QLabel * room; //label to store the room number
    QComboBox * classesComboBox; //combobox that has the classes values
    QComboBox * coursesComboBox; //combobox that has the courses values
    QComboBox * teachersComboBox; //combobox that has the teachers values

    int row; //the activity row (time slot)
    int column; //the activity column (day)

private slots:

     void comboboxIndexChanged(); //listener for combobox value change
     void accepted(); //listener for button save clicked
     void cancelled(); //listener for button cancel clicked
     void unassigned(); //listener for button unassigned clicked

public:

    EntryEditor(QObject *parent = nullptr, SchoolPlanner *schoolPlanner = nullptr, int row = 0, int column = 0); //constructor hich takes reference to the activity and current row/column selected

    void validateSaveButton(); //if any of the fields are left blank, save button will be disabled or else enabled
    bool emptyFieldExists(); //checks whether there are any combo box

    int getRow(); //getter for the activity row (time slot)
    int getColumn(); //getter for the activity column (day)


signals:

};

#endif // ENTRYEDITORDIALOG_H
