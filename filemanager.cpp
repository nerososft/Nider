#include "filemanager.h"
#include <QDebug>
#include "filehelper.h"

FileManager::FileManager()
{

}

QString  FileManager::getBufferedFile(QString fileName,QString filePath){
    //this->filePath = filePath;

   //在map中查找file
   std::map<QString, QString>::iterator mit = this->fileBuffer.find(fileName);

   if (mit == this->fileBuffer.end()){
        FileHelper fileHelper;
        QString file = fileHelper.loadCodeFileToString(filePath+fileName);
        std::pair<QString, QString> newPair(fileName,file);

       this->fileBuffer.insert(newPair);
         qDebug()<< "读取文件:" + filePath+fileName+":"+file;
       return file;
   }
   qDebug()<<"使用缓存文件"+fileName;
   return mit->second;
}

 bool FileManager::updateFileBuffer(QString fileName,QString content){
     std::map<QString, QString>::iterator it;
      it = this->fileBuffer.find(fileName);
      if(it == this->fileBuffer.end())
          return false;
          //this->fileBuffer.insert(std::make_pair(fileName, content));
      else {
            it->second = content;
            return true;
      }
 }
