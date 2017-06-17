#include "editor.h"
#include <QDebug>

EditorManager::EditorManager()
{

}



//编辑器关闭文件
void EditorManager::closeFile(QString filename,QString filePath){

}

//文件是否在编辑器打开
bool EditorManager::isFileOpened(QString filename,QString filePath){
    std::map<QString,QString>::iterator fileIterator=this->openedFIle.find(filename);
    std::pair<QString, QString> newPair(filename,filePath );
    if (fileIterator == this->openedFIle.end()){
        return false;
    }
    return true;
}

//编辑器切换已经打开的文件
void EditorManager::switchFile(QString filename,QString filePath){

}


//编辑器打开新文件
void EditorManager::openFile(QString filename,QString filePath){

    std::map<QString,QString>::iterator fileIterator=this->openedFIle.find(filename);
    std::pair<QString, QString> newPair(filename,filePath);
    if (fileIterator == this->openedFIle.end()){
        this->openedFIle.insert(this->openedFIle.begin(),newPair);
         qDebug()<< "编辑器打开新文件:"+filePath+filename;
    }
    qDebug()<<"编辑器已经打开了该文件"+filePath+filename;

    this->fileIndex  = newPair;
}
 std::vector<QString> EditorManager::getOpenedFile(){
     std::map<QString,QString>::iterator fileIterator;

    std::vector<QString> opened;
    for(fileIterator = this->openedFIle.begin();fileIterator!=this->openedFIle.end();fileIterator++){
        opened.insert(opened.begin(),fileIterator->first);
    }
    return opened;
 }
