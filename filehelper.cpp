#include "filehelper.h"
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <errorhelper.h>
FileHelper::FileHelper()
{

}

//拷贝文件：
bool FileHelper::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

//拷贝文件夹：
bool FileHelper::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}

QFileInfoList FileHelper::getFileList(QString path,QString houzhui){
    QFileInfoList InfoList = QDir( path).entryInfoList();//获取当前目录所有文件
    QFileInfoList SuffixInfoList;//定义放提取文件的List
    //遍历
    foreach(QFileInfo fileInfo, InfoList){

        if(!fileInfo.isFile()) continue;//不是文件继续，只用于加速，可不加
        //qDebug()<<fileInfo.fileName()<<"   "<<fileInfo.suffix();
        //后缀不区分大小写，需要区分直接用“==”
        if(fileInfo.suffix()==houzhui)
        {
            SuffixInfoList << fileInfo;//指定后缀，加入列表
        }
    }
    return SuffixInfoList;
}

bool FileHelper::createFile(QString file,QString content){
    QFile File(file);
    if (!File.open(QIODevice::WriteOnly|QIODevice::Text)) {
        return false;
    }
    QTextStream out(&File);
    out<<content<<endl;
    out.flush();
    File.close();
    return true;
}

QString FileHelper::loadFileToString(QString filepath){
    QString buffer;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){

        ErrorHelper::Error("文件"+filepath+"读取失败");
       return  "";
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        buffer+=line;
    }
    file.close();
    return buffer;
}
QString FileHelper::loadCodeFileToString(QString filepath){
    QString buffer;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){

        ErrorHelper::Error("文件"+filepath+"读取失败");
       return  "";
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        buffer+=line+"\n";
    }
    file.close();
    return buffer;
}


 bool FileHelper::saveFile(QString filePath,QString content){
     QFile File(filePath);
     if (!File.open(QIODevice::WriteOnly|QIODevice::Text)) {
         return false;
     }
     QTextStream out(&File);
     out<<content<<endl;
     out.flush();
     File.close();
     return true;
 }
