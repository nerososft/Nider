#ifndef TASK_H
#define TASK_H
#include <QString>
enum TASK_LEVEL {
    LEVEL_0 = 0,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5
};
class TaskManager
{
public:
    TaskManager();

    bool createTask(TASK_LEVEL level,QString content);
    bool doneTask(QString taskID);
    bool removeTask(QString taskID);
    bool undoTask(QString taskID);
};

#endif // TASK_H
