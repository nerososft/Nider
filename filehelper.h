#ifndef FILEHELPER_H
#define FILEHELPER_H
#include <QString>
#include <QFile>
#include <QDir>

class FileHelper
{
public:
    FileHelper();

    //拷贝文件：
    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);

    //拷贝文件夹：
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);

    QFileInfoList getFileList(QString path,QString houzhui);

    bool createFile(QString file,QString content);

    QString loadFileToString(QString filePath);

    QString loadCodeFileToString(QString filePath);

    bool saveFile(QString filePath,QString content);

};

#endif // FILEHELPER_H
