#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include <map>

class FileManager
{
public:
    FileManager();

    std::map<QString,QString> fileBuffer;

    QString getBufferedFile(QString fileName,QString filePath);

    bool updateFileBuffer(QString fileName,QString content);

};

#endif // FILEMANAGER_H
