#include "generalproject.h"
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QDebug>
#include <QIcon>

GeneralProject::GeneralProject()
{
    this->model = new QStandardItemModel();
}


void initProject();

void  GeneralProject::loadFolder(QStandardItem* mm,QString forderPath){
    QStandardItem* modeli = new QStandardItem(QIcon(""),forderPath);
    QDir dir(forderPath);
      foreach(QFileInfo mfi ,dir.entryInfoList())
      {
        if(mfi.isFile())
        {
            QStandardItem* item = new QStandardItem(QIcon(""),mfi.absoluteFilePath());
            modeli->appendRow(item);
            qDebug()<< "File :" << mfi.fileName();
        }else
        {
            if(mfi.fileName()=="." || mfi.fileName() == "..")continue;
            qDebug() << "Entry Dir" << mfi.absoluteFilePath();
            loadFolder(modeli,mfi.absoluteFilePath());
        }
      }
      mm->appendRow(modeli);
}

QStandardItemModel* GeneralProject::getCurrentForder(QString folder){
    QStandardItem* item = new QStandardItem(QIcon(""),folder);

     loadFolder(item,folder);

     this->model->appendRow(item);
     return this->model;
}

QStandardItemModel* GeneralProject::loadFile(QString filePath){


}
