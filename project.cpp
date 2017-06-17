#include "project.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

Project::Project(QJsonObject projectOBJ)
{
    this->projectOBJ = projectOBJ;
    projectObjectToProjectEntity();
    this->icon.InitFileIcon(":/icon/icons.png");
}

void Project::projectObjectToProjectEntity(){
    //projectname
    QString projectName = this->projectOBJ.find("projectname").value().toString();

    //version
    QString version = this->projectOBJ.find("version").value().toString();

    //source
    std::vector<Source> v_sources;
    QJsonArray sources = this->projectOBJ.find("source").value().toArray();
        foreach(QJsonValue source_v,sources){
            QJsonObject source = source_v.toObject();
            Source p_source;
            //src
            QString src = source.find("src").value().toString();
            //mark
            std::vector<Mark> v_mark;
            QJsonArray marks = source.find("mark").value().toArray();
            foreach(QJsonValue mark_v,marks){
                QJsonObject mark  = mark_v.toObject();
                QString id = mark.find("id").value().toString();
                QString level = mark.find("level").value().toString();
                QString content = mark.find("content").value().toString();
                QString row = mark.find("row").value().toString();
                QString date = mark.find("date").value().toString();
                QString author = mark.find("author").value().toString();
                Mark markItem;
                markItem.id = id;
                markItem.content = content;
                markItem.author = author;
                markItem.row = row;
                markItem.date  = date;
                markItem.level = level;
                v_mark.push_back(markItem);
            }
            p_source.mark = v_mark;
            p_source.src = src;

            v_sources.push_back(p_source);
        }

    //header
     std::vector<Source> v_headers;
    QJsonArray headers = this->projectOBJ.find("header").value().toArray();
        foreach(QJsonValue header_v, headers){
            QJsonObject header = header_v.toObject();
            Source p_header;
            //src
            QString src = header.find("src").value().toString();
            //mark
            std::vector<Mark> v_mark;
            QJsonArray marks = header.find("mark").value().toArray();
            foreach(QJsonValue mark_v,marks){
                QJsonObject mark = mark_v.toObject();
                QString id = mark.find("id").value().toString();
                QString level = mark.find("level").value().toString();
                QString content = mark.find("content").value().toString();
                QString row = mark.find("row").value().toString();
                QString date = mark.find("date").value().toString();
                QString author = mark.find("author").value().toString();
                Mark markItem;
                markItem.id = id;
                markItem.content = content;
                markItem.author = author;
                markItem.row = row;
                markItem.date  = date;
                markItem.level = level;
                v_mark.push_back(markItem);
            }
            p_header.mark = v_mark;
            p_header.src = src;

            v_headers.push_back(p_header);
        }

    //task
    Task p_task;
    QJsonObject task = this->projectOBJ.find("task").value().toObject();
        //undo
        QJsonArray undos = task.find("undo").value().toArray();
        std::vector<TaskItem> v_undos;
        foreach(QJsonValue undo_v,undos){
            QJsonObject undo= undo_v.toObject();
            QString id = undo.find("id").value().toString();
            QString content = undo.find("content").value().toString();
            QString level = undo.find("level").value().toString();
            QString date = undo.find("date").value().toString();
            QString author = undo.find("author").value().toString();
            TaskItem taskItemUndo;
            taskItemUndo.id = id;
            taskItemUndo.content = content;
            taskItemUndo.level = level;
            taskItemUndo.date = date;
            taskItemUndo.author = author;

            v_undos.push_back(taskItemUndo);
        }
        //doing
        QJsonArray doings = task.find("doing").value().toArray();
        std::vector<TaskItem> v_doings;
        foreach(QJsonValue doing_v,doings){
            QJsonObject doing = doing_v.toObject();
            QString id = doing.find("id").value().toString();
            QString content = doing.find("content").value().toString();
            QString level = doing.find("level").value().toString();
            QString date = doing.find("date").value().toString();
            QString author = doing.find("author").value().toString();
            TaskItem taskItemDoing;
            taskItemDoing.id = id;
            taskItemDoing.content = content;
            taskItemDoing.level = level;
            taskItemDoing.date = date;
            taskItemDoing.author = author;

            v_doings.push_back(taskItemDoing);
         }
        //done
        QJsonArray dones = task.find("done").value().toArray();
        std::vector<TaskItem> v_dones;
        foreach(QJsonValue done_v,dones){
            QJsonObject done = done_v.toObject();
            QString id = done.find("id").value().toString();
            QString content = done.find("content").value().toString();
            QString level = done.find("level").value().toString();
            QString date = done.find("date").value().toString();
            QString author = done.find("author").value().toString();
            TaskItem taskItemDone;
            taskItemDone.id = id;
            taskItemDone.content = content;
            taskItemDone.level = level;
            taskItemDone.date = date;
            taskItemDone.author = author;

            v_dones.push_back(taskItemDone);
         }
        p_task.undo = v_undos;
        p_task.doing = v_doings;
        p_task.done = v_dones;


        this->project.header = v_headers;
        this->project.source = v_sources;
        this->project.projectname = projectName;
        this->project.version = version;
        this->project.task = p_task;
}


QString Project::getProjectName(){
    return this->project.projectname;
}

QString Project::getProjectVersion(){
    return this->project.version;
}

QStandardItemModel* Project::getTaskUndo(){
    QStandardItemModel* model = new QStandardItemModel();

    foreach(TaskItem item,this->project.task.undo){
        QStandardItem*  itemProject = new QStandardItem(QIcon(":/icon/level_"+item.level+".png"),item.content);
         model->appendRow(itemProject);
    }

    return model;
}

QStandardItemModel* Project::getTaskDoing(){
    QStandardItemModel* model = new QStandardItemModel();

    foreach(TaskItem item,this->project.task.doing){
        QStandardItem*  itemProject = new QStandardItem(QIcon(":/icon/level_"+item.level+".png"),item.content);
         model->appendRow(itemProject);
    }

    return model;
}

QStandardItemModel* Project::getTaskDone(){
    QStandardItemModel* model = new QStandardItemModel();

    foreach(TaskItem item,this->project.task.done){
        QStandardItem*  itemProject = new QStandardItem(QIcon(":/icon/level_"+item.level+".png"),item.content);
         model->appendRow(itemProject);
    }

    return model;
}

QStandardItem* Project::getSource(){
    QStandardItem*  source = new QStandardItem(QIcon(":/icon/open_file.png"),"Sources");

    foreach(Source item,this->project.source){
        QStandardItem*  itemProject = new QStandardItem(this->icon.getIcon("cpp"),item.src);
        source->appendRow(itemProject);
    }
    return source;
}

QStandardItem* Project::getHeaders(){
    QStandardItem*  header = new QStandardItem(QIcon(":/icon/open_file.png"),"Headers");

    foreach(Source item,this->project.header){
        QStandardItem*  itemProject = new QStandardItem(this->icon.getIcon("cpp"),item.src);
        header->appendRow(itemProject);
    }
    return header;
}

QStandardItemModel* Project::getProjectTree(){
    QStandardItemModel* model = new QStandardItemModel();

    model->appendRow(getSource());
    model->appendRow(getHeaders());

    return model;
}

QStandardItemModel* Project::getMark(QString src){
    QStandardItemModel*  mark = new QStandardItemModel();

    foreach(Source item,this->project.source){
        if(item.src==src){
            foreach(Mark mark_item,item.mark){
                QStandardItem*  itemProject = new QStandardItem(QIcon(":/icon/mark_"+mark_item.level+".png"),mark_item.content);
                mark->appendRow(itemProject);
            }
        }else{
            continue;
        }
    }

    foreach(Source item,this->project.header){
        if(item.src==src){
            foreach(Mark mark_item,item.mark){
                QStandardItem*  itemProject = new QStandardItem(QIcon(":/icon/mark_"+mark_item.level+".png"),mark_item.content);
                mark->appendRow(itemProject);
            }
        }else{
            continue;
        }
    }

    return mark;
}
