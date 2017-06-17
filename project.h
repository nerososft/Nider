#ifndef PROJECT_H
#define PROJECT_H
#include "projectentity.h"
#include <QJsonObject>
#include <QStandardItemModel>
#include "filetypeicon.h"

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

    FileTypeIcon icon;

};

#endif // PROJECT_H
