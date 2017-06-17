#include "filetypeicon.h"
#include <QPixelFormat>
#include <QPixmap>
int ICON_WIDTH  = 50;
FileTypeIcon::FileTypeIcon()
{

}
void FileTypeIcon::LoadFileIcon(QString path){
    this->image = new QImage(path);
}


void FileTypeIcon::InitFileIcon(QString path){
    this->LoadFileIcon(path);

   QIcon cpp =  QIcon(QPixmap::fromImage(this->image->copy(600,100,ICON_WIDTH,ICON_WIDTH)));
    std::pair<QString, QIcon> newPair("cpp",cpp );

   this->iconTable.insert(newPair);

}

QIcon FileTypeIcon::getIcon(QString Filetype){
    //this->iconTable.find(Filetype)->second;
    return QIcon(QPixmap::fromImage(this->image->copy(600,100,ICON_WIDTH,ICON_WIDTH)));
}
