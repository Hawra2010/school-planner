#include "entryeditor.h"

#include <QPushButton>
#include <QButtonGroup>
#include <QPixmap>
#include <QIcon>

EntryEditor::EntryEditor(QObject * parent, SchoolPlanner * schoolPlanner, int row, int column) {


    //initialize the variables
    this -> row = row;
    this -> column = column;
    this -> schoolPlanner = schoolPlanner;


    //initialize the variables
    room = new QLabel();
    classesComboBox = new QComboBox();
    coursesComboBox = new QComboBox();
    teachersComboBox = new QComboBox();

    //add items to the combo boxes
    classesComboBox -> addItems(schoolPlanner -> getGroups());
    coursesComboBox -> addItems(schoolPlanner -> getCourses());
    teachersComboBox -> addItems(schoolPlanner -> getTeachers());


    //unselect options
    classesComboBox -> setCurrentIndex(-1);
    coursesComboBox -> setCurrentIndex(-1);
    teachersComboBox -> setCurrentIndex(-1);


    // get the activity with that time slot and day
    activity = schoolPlanner -> findActivity(row, column);


    // set values and select the options based on the activity
    room -> setText(activity.getRoom() == nullptr ? "" : activity.getRoom());
    classesComboBox -> setCurrentText(activity.getGroup() == nullptr ? "" : activity.getGroup());
    coursesComboBox -> setCurrentText(activity.getCourse() == nullptr ? "" : activity.getCourse());
    teachersComboBox -> setCurrentText(activity.getTeacher() == nullptr ? "" : activity.getTeacher());


    //we are setting a title for our dialog
    setWindowTitle("Edit entry");

    //reset the size
    resize(250, 150);

    //we are creating a form layout
    auto layout = new QFormLayout;

    //resetting our layout to the form layout
    setLayout(layout);


    //adding rows into the form layout (label, component)
    layout -> addRow("Room: ", room);
    layout -> addRow("Class: ", classesComboBox);
    layout -> addRow("Course: ", coursesComboBox);
    layout -> addRow("Teacher: ", teachersComboBox);


    //layout that will hold the buttons
    QHBoxLayout * buttonsHorizontalBoxLayout = new QHBoxLayout;

    //if the activity is not new, then create an unassign button, add it to the box and add a listener
    if (!emptyFieldExists()) {
        QPushButton * btn_unassign = new QPushButton("Unassign");
        buttonsHorizontalBoxLayout -> addWidget(btn_unassign);
        connect(btn_unassign, & QPushButton::released, this, & EntryEditor::unassigned);

        //add icon
        QPixmap pixmap(":/files/resources/delete.png");
        QIcon buttonIcon(pixmap);
        btn_unassign->setIcon(buttonIcon);
    }

    //create a save button, add it to the box and add a listener
    btn_save = new QPushButton("Save");
    buttonsHorizontalBoxLayout -> addWidget(btn_save);
    connect(btn_save, & QPushButton::released, this, & EntryEditor::accepted);

    //add icon
    QPixmap pixmap(":/files/resources/save.png");
    QIcon buttonIcon(pixmap);
    btn_save->setIcon(buttonIcon);


    //create a cancel button, add it to the box and add a listener
    QPushButton * btn_cancel = new QPushButton("Cancel");
    buttonsHorizontalBoxLayout -> addWidget(btn_cancel);
    connect(btn_cancel, & QPushButton::released, this, & EntryEditor::cancelled);

    //add icon
    QPixmap pixmap1(":/files/resources/close.png");
    QIcon buttonIcon1(pixmap1);
    btn_cancel->setIcon(buttonIcon1);



    //add buttons box to the layout
    layout -> addRow(buttonsHorizontalBoxLayout);


    //add an index change listener to the comboboxes to check for the button enability
    connect(classesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxIndexChanged()));
    connect(coursesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxIndexChanged()));
    connect(teachersComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxIndexChanged()));


    //check if the save button should be enabled or disabled
    validateSaveButton();

}



void EntryEditor::validateSaveButton() {
    if (btn_save != nullptr) {
        if (emptyFieldExists()) {
            btn_save -> setEnabled(false);
        } else {
            btn_save -> setEnabled(true);
        }
    }
}

bool EntryEditor::emptyFieldExists() {
    return classesComboBox -> currentIndex() == -1 || coursesComboBox -> currentIndex() == -1 || teachersComboBox -> currentIndex() == -1;
}


void EntryEditor::comboboxIndexChanged() {
    validateSaveButton();
}


void EntryEditor::accepted() {
    schoolPlanner -> removeActivity(activity);
    activity.setSlot(row);
    activity.setDay(column);
    activity.getRoom() = room -> text();
    activity.setTeacher(teachersComboBox -> currentText());
    activity.setCourse(coursesComboBox -> currentText());
    activity.setGroup(classesComboBox -> currentText());
    schoolPlanner -> addActivity(activity);
    schoolPlanner -> setupSchoolPlanner();
    accept();

}

void EntryEditor::cancelled() {
    reject();
}

void EntryEditor::unassigned() {
    schoolPlanner -> removeActivity(activity);
    schoolPlanner -> setupSchoolPlanner();
    accept();
}




int EntryEditor::getRow() {
    return row;
}

int EntryEditor::getColumn() {
    return column;
}
