#ifndef PROJECT_H
#define PROJECT_H
#include "projectentity.h"
#include <QJsonObject>
#include <QStandardItemModel>

class Project
{
public:
    Project(QJsonObject projectOBJ);

    ProjectEntity project;

    QJsonObject projectOBJ;

    void projectObjectToProjectEntity();

    QString getProjectName();

    QString getProjectVersion();

    QStandardItemModel* getTaskUndo();

    QStandardItemModel* getTaskDoing();

    QStandardItemModel* getTaskDone();

    QStandardItem* getSource();

    QStandardItem* getHeaders();

    QStandardItemModel* getProjectTree();

    QStandardItemModel* getMark(QString src);


};

#endif // PROJECT_H
