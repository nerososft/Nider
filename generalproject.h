#ifndef GENERALPROJECT_H
#define GENERALPROJECT_H
#include  <QString>
#include <QStandardItemModel>


class GeneralProject
{
public:
    GeneralProject();

    void initProject();

    void loadFolder(QStandardItem* mm,QString forderPath);

    QStandardItemModel* getCurrentForder(QString path);


    QStandardItemModel* loadFile(QString filePath);


    QStandardItemModel*  model = new QStandardItemModel();


};

#endif // GENERALPROJECT_H
