#ifndef PROJECTENTITY_H
#define PROJECTENTITY_H
#include <QString>
#include <vector>
class TaskItem{
    public:
        QString id;
        QString content;
        QString level;
        QString date;
        QString author;
};
class Task{
    public:
        std::vector<TaskItem> undo;
        std::vector<TaskItem> doing;
        std::vector<TaskItem> done;
};
class Mark{
    public:
        QString id;
        QString level;
        QString content;
        QString row;
        QString date;
        QString author;
};
class Source{
    public:
       QString src;
       std::vector<Mark> mark;
};

class ProjectEntity
{
    public:
        ProjectEntity();

        QString version;
        QString projectname;
        std::vector<Source> source;
        std::vector<Source> header;
        Task task;
};

#endif // PROJECTENTITY_H
