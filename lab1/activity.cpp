#include "activity.h"

Activity::Activity()
{

}


Activity::Activity(QString room)
{
this->room = room;
}


Activity::Activity(QString room, QString group, QString course, int day, int slot, QString teacher){
    this->room = room;
    this->group = group;
    this->course = course;
    this->day = day;
    this->slot = slot;
    this->teacher = teacher;
}


Activity::Activity(const QJsonObject& json) {
    qDebug() << json;
    this->course = json["class"].toString();
    this->day = json["day"].toInt();
    this->group = json["group"].toString();
    this->room = json["room"].toString();
    this->slot = json["slot"].toInt();
    this->teacher = json["teacher"].toString();
}

Activity::Activity(const Activity& activity) {
    this->room = activity.room;
    this->group = activity.group;
    this->course = activity.course;
    this->day = activity.day;
    this->slot = activity.slot;
    this->teacher = activity.teacher;
}


bool Activity::operator ==(const Activity &other) const
   {
       return teacher == other.teacher
           && course == other.course
           && group == other.group
           && room == other.room
           && day == other.day
           && slot == other.slot;
   }


void Activity::save(QJsonObject &json) const{
        json["teacher"] = teacher;
        json["class"] = course;
        json["group"] = group;
        json["room"] = room;
        json["slot"] = slot;
        json["day"] = day;
}

QString Activity::getGroup(){
    return group;
}

QString Activity::getCourse(){
    return course;
}

QString Activity::getTeacher(){
    return teacher;
}

QString Activity::getRoom(){
    return room;
}

int Activity::getDay(){
    return day;
}

int Activity::getSlot(){
    return slot;
}

void Activity::setGroup(QString group){
    this->group = group;
}

void Activity::setCourse(QString course){
    this->course = course;
}

void Activity::setTeacher(QString teacher){
    this->teacher = teacher;
}

void Activity::setRoom(QString room){
    this->room = room;
}

void Activity::setDay(int day){
    this->day = day;
}

void Activity::setSlot(int slot){
    this->slot = slot;
}
