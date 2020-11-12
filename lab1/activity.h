#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QJsonObject>


class Activity
{


private:
    QString group; //The activity group
    QString course; //The activity course
    QString teacher; //The activitiy's teacher
    QString room; //room where activity is taking place
    int day; //the day of the week where the activity is taking place
    int slot; //the time slot that the activity is assigned to


public:
    Activity(); //default constructor
    Activity(QString room); //constructor with one parameter (room) for newly created activities
    Activity(const QJsonObject& json); //constructor that takes a json object and fetches/initializes the activity from
    Activity(QString room, QString group, QString course, int day, int slot, QString teacher); //constructor where we pass all the activity information
    Activity(const Activity& copy); //copy constructor

    bool operator ==(const Activity &other) const; //equality check operator for activity


    void save(QJsonObject &json) const; //saves the activity information into a json object

    QString getGroup(); //getter for the current activity's group
    QString getCourse(); //getter for the current activity's course
    QString getTeacher(); //getter for the current activity's teacher
    QString getRoom(); //getter for the current activity's room
    int getDay(); //getter for the current activity's day
    int getSlot(); //getter for the current activity's slot


    void setGroup(QString group); //group setter for the current activity
    void setCourse(QString course); //course setter for the current activity
    void setTeacher(QString teacher); //teacher setter for the current activity
    void setRoom(QString room); //room setter for the current activity
    void setDay(int day); //day setter for the current activity
    void setSlot(int slot); //slot setter for the current activity
};

#endif // ACTIVITY_H
