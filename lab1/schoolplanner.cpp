#include "schoolplanner.h"
#include "ui_schoolplanner.h"

#include "dictionaryeditor.h"
#include "entryeditor.h"


SchoolPlanner::SchoolPlanner(QWidget * parent): QMainWindow(parent), ui(new Ui::SchoolPlanner) {

    //setup the user interface
    ui -> setupUi(this);

    //add action listener to load and a tooltip
    connect(ui -> actionOpen, & QAction::triggered, this, & SchoolPlanner::loadDataFromFileChooser);
    ui -> actionOpen -> setStatusTip(tr("Load data from a file"));


    //add action listener to save as and create a tooltip
    connect(ui -> actionSave, & QAction::triggered, this, & SchoolPlanner::savetoCurrentFile);
    ui -> actionOpen -> setStatusTip(tr("Save data to the currently loaded file"));


    //add action listener to save as and create a tooltip
    connect(ui -> actionSave_as, & QAction::triggered, this, & SchoolPlanner::saveAs);
    ui -> actionOpen -> setStatusTip(tr("Save data to a new file"));


    //add close button action listener and a tool tip
    connect(ui -> actionQuit, & QAction::triggered, this, & QWidget::close);
    ui -> actionQuit -> setStatusTip(tr("Quit the school planner"));



    //add listeners to open all the dictionary editors
    connect(ui -> actionRooms, & QAction::triggered, this, & SchoolPlanner::openRoomsDictionaryEditor);
    connect(ui -> actionTeachers, & QAction::triggered, this, & SchoolPlanner::openTeachersDictionaryEditor);
    connect(ui -> actionCourses, & QAction::triggered, this, & SchoolPlanner::openCoursesDictionaryEditor);
    connect(ui -> actionClasses, & QAction::triggered, this, & SchoolPlanner::openGroupsDictionaryEditor);



}

SchoolPlanner::~SchoolPlanner() {
    delete ui;
}


void SchoolPlanner::on_tableWidget_cellDoubleClicked(int row, int column) {
    qDebug() << "A cell was clicked in row " << row << " column " << column;
    EntryEditor entryEditorDialog(NULL, this, row, column);
    entryEditorDialog.exec();
}

void SchoolPlanner::on_comboBox_currentTextChanged(const QString & arg1) {
    setupSchoolPlanner();
}



void SchoolPlanner::setupSchoolPlanner() {


    //add the rooms to the combobox
    if (ui -> comboBox -> count() == 0) {
        ui -> comboBox -> addItems(rooms);
    }


    //add the activities to the table
    ui -> tableWidget -> clearContents();
    for (Activity activity: activities) {
        if (activity.getRoom() == ui -> comboBox -> currentText()) {
            QTableWidgetItem * item = new QTableWidgetItem(activity.getGroup() + " (" + activity.getCourse() + ")");
            ui -> tableWidget -> setItem(activity.getSlot(), activity.getDay(), item);
        }
    }
}



void SchoolPlanner::loadDataFromFileChooser() {
    auto path = QFileDialog::getOpenFileName(this);
    loadData(path);
}



void SchoolPlanner::loadData(QString path) {

    //clear the lists to reload new information
    clearLists();

    dataFilePath = path;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Error loading file [" << path << "]";
        QMessageBox messageBox;
        messageBox.critical(0, "Error loading file", "Couldn't load the file [" + path + "]");
        messageBox.setFixedSize(500, 200);
        return;
    }

    //read content in json file
    auto data = file.readAll();
    auto jsonDocument = QJsonDocument::fromJson(data);
    file.close();


    QJsonArray jsonRooms = jsonDocument["rooms"].toArray(); //store rooms in a json array
    QJsonArray jsonGroups = jsonDocument["groups"].toArray(); //store groups in a json array
    QJsonArray jsonClasses = jsonDocument["classes"].toArray(); //store classes into a json array
    QJsonArray jsonTeachers = jsonDocument["teachers"].toArray(); //store teachers into a json array
    QJsonArray jsonActivities = jsonDocument["activities"].toArray(); //store avtivities into a json array

    //loop through json rooms array values, and add them to the list
    for (const QJsonValue & value: jsonRooms) {
        rooms.append(value.toString());
    }

    //loop through json groups array values, and add them to the list
    for (const QJsonValue & value: jsonGroups) {
        groups.append(value.toString());
    }

    //loop through json classes array values, and add them to the list
    for (const QJsonValue & value: jsonClasses) {
        courses.append(value.toString());
    }

    //loop through json teachers array values, and add them to the list
    for (const QJsonValue & value: jsonTeachers) {
        teachers.append(value.toString());
    }

    //loop through json activities array values, and add them to the list
    for (const QJsonValue & value: jsonActivities) {
        auto jobject = value.toObject();
        Activity activity(jobject);
        activities.append(activity);
    }

    //set up the table based on the new information we have
    setupSchoolPlanner();
}




void SchoolPlanner::savetoCurrentFile() {
    save(dataFilePath);
}



void SchoolPlanner::saveAs() {
    auto fileName = QFileDialog::getSaveFileName(this);
    save(fileName);
}


void SchoolPlanner::save(QString filePath) {
    QFile saveFile(filePath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Error loading the save file [" << dataFilePath << "]";
        QMessageBox messageBox;
        messageBox.critical(0, "Error loading file", "Couldn't load the save file [" + dataFilePath + "]");
        messageBox.setFixedSize(500, 200);
        return;
    }

    QJsonObject jsonRoot;
    QJsonArray jsonRooms; //json array to store all the rooms
    QJsonArray jsonGroups; //json array to store all the groups
    QJsonArray jsonClasses; //json array to store all the classes
    QJsonArray jsonTeachers; //json array to store all the teachers
    QJsonArray jsonActivities; //json array to store all the activities


    //add all the rooms to the json rooms array
    for (const QString & value: rooms) {
        jsonRooms.append(value);
    }

    //add all the groups to the json rooms array
    for (const QString & value: groups) {
        jsonGroups.append(value);
    }

    //add all the courses to the json rooms array
    for (const QString & value: courses) {
        jsonClasses.append(value);
    }

    //add all the teachers to the json rooms array
    for (const QString & value: teachers) {
        jsonTeachers.append(value);
    }

    //add all the activities to the json rooms array
    for (const Activity & value: activities) {
        QJsonObject jsonValue;
        value.save(jsonValue);
        jsonActivities.append(jsonValue);
    }

    //assign the avalues from the arrays to the json root
    jsonRoot["rooms"] = jsonRooms;
    jsonRoot["groups"] = jsonGroups;
    jsonRoot["classes"] = jsonClasses;
    jsonRoot["teachers"] = jsonTeachers;
    jsonRoot["activities"] = jsonActivities;

    //save the information
    saveFile.write(QJsonDocument(jsonRoot).toJson());

    //we are done with writing, close the file
    saveFile.close();
}

void SchoolPlanner::clearLists() {
    rooms.clear(); //clear the rooms list
    groups.clear(); //clear the groups list
    courses.clear(); //clear the courses list
    teachers.clear(); //clear the teachers list
    activities.clear(); //clear the activities list
}

void SchoolPlanner::addActivity(Activity activity) {
    activities.append(activity);
}

void SchoolPlanner::removeActivity(Activity activity) {
    activities.removeAll(activity);
}

Activity SchoolPlanner::findActivity(int row, int column) {
    //loop through all activities
    for (Activity activity: activities) {
        //if we find a match, then return the activity
        if (activity.getSlot() == row && activity.getDay() == column) {
            return activity;
        }
    }
    //if not found, then create an activity with the current chosen room number
    return Activity(ui -> comboBox -> currentText());
}




void SchoolPlanner::openRoomsDictionaryEditor(void) {
    DictionaryEditor dictioaryEditor(this, rooms);
    dictioaryEditor.setWindowTitle(tr("Edit dictionary"));
    dictioaryEditor.exec();
}

void SchoolPlanner::openGroupsDictionaryEditor(void) {
    DictionaryEditor dictioaryEditor(this, groups);
    dictioaryEditor.setWindowTitle(tr("Groups dictionary Editor"));
    dictioaryEditor.exec();
}

void SchoolPlanner::openCoursesDictionaryEditor(void) {
    DictionaryEditor dictioaryEditor(this, courses);
    dictioaryEditor.setWindowTitle(tr("Courses dictionary editor"));
    dictioaryEditor.exec();
}

void SchoolPlanner::openTeachersDictionaryEditor(void) {
    DictionaryEditor dictioaryEditor(this, teachers);
    dictioaryEditor.setWindowTitle(tr("Teacher dictionary editor"));
    dictioaryEditor.exec();
}


void SchoolPlanner::setRooms(QStringList rooms) {
    this -> rooms = rooms;
}

void SchoolPlanner::setGroups(QStringList groups) {
    this -> groups = groups;
}


void SchoolPlanner::setCourses(QStringList courses) {
    this -> courses = courses;
}


void SchoolPlanner::setTeachers(QStringList teachers) {
    this -> teachers = teachers;
}

void SchoolPlanner::setActivities(QList < Activity > activities) {
    this -> activities = activities;
}


QStringList SchoolPlanner::getRooms() {
    return rooms;
}

QStringList SchoolPlanner::getGroups() {
    return groups;
}

QStringList SchoolPlanner::getCourses() {
    return courses;
}

QStringList SchoolPlanner::getTeachers() {
    return teachers;
}


QList < Activity > SchoolPlanner::getActivities() {
    return activities;
}


