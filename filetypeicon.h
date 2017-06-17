#ifndef FILETYPEICON_H
#define FILETYPEICON_H
#include <QImage>
#include <map>
#include <QString>
#include <QIcon>


class FileTypeIcon
{
public:
    FileTypeIcon();

    QImage* image;

    std::map<QString,QIcon> iconTable;




    void LoadFileIcon(QString path);


    void InitFileIcon(QString path);


    QIcon getIcon(QString Filetype);



};

#endif // FILETYPEICON_H
