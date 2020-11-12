#ifndef SCHOOLPLANNER_H
#define SCHOOLPLANNER_H

#include <QMainWindow>
#include <QComboBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QFile>
#include <QJsonObject>
#include <QFileDialog>
#include <QMessageBox>


#include "activity.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SchoolPlanner; }
QT_END_NAMESPACE

class SchoolPlanner : public QMainWindow
{
    Q_OBJECT


private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column); //signal for when a cell is double clicked from table
    void on_comboBox_currentTextChanged(const QString &arg1); //signal when a combobox value is changed

private:
    Ui::SchoolPlanner *ui; //reference to the user interface of this file
    QStringList rooms; //stores all of the rooms we have
    QStringList groups; //stores all of the groups we have
    QStringList courses; //stores all of the courses we have
    QStringList teachers; //stores all of the teachers we have
    QList<Activity> activities; //stores all of the activities we have
    QString dataFilePath; //link to the currently opened file where we are reading the data from

public:
    SchoolPlanner(QWidget *parent = nullptr); //main constructor
    ~SchoolPlanner(); //destructors

    void addActivity(Activity activity);
    void removeActivity(Activity activity);

    void loadData(QString path); //loads file from a given path
    void loadDataFromFileChooser(); //loads a file from the file chooser
    void setupSchoolPlanner(); //sets up the rooms and table
    void savetoCurrentFile(); //saves to the currently loaded file
    void saveAs(); //saves to a new file
    void save(QString filePath); //save file to this specific path
    void clearLists(); //clear all the information
    Activity findActivity(int row, int column); //find activity by row/column which is slot/day

    void openRoomsDictionaryEditor(); //opens a dictiory dialog to edit the rooms
    void openTeachersDictionaryEditor(); //opens a dictiory dialog to edit the teachers
    void openCoursesDictionaryEditor(); //opens a dictiory dialog to edit the courses
    void openGroupsDictionaryEditor(); //opens a dictiory dialog to edit the groups

    void setRooms(QStringList rooms); //setter for rooms
    void setGroups(QStringList groups); //setter for groups
    void setCourses(QStringList courses); //setter for courses
    void setTeachers(QStringList teachers); //setter for teachers
    void setActivities(QList<Activity> activities); //setter for activities

    QStringList getRooms(); //getter for rooms
    QStringList getGroups(); //getter for groups
    QStringList getCourses() ; //getter for courses
    QStringList getTeachers(); //getter for teachers
    QList<Activity> getActivities(); //getter for activities
};
#endif // SCHOOLPLANNER_H
