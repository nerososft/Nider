#ifndef EDITOR_H
#define EDITOR_H
#include <map>
#include <QString>
#include <vector>

class EditorManager
{
public:

    EditorManager();

    std::map<QString,QString> openedFIle;

    std::pair<QString,QString> fileIndex;

    //编辑器打开新文件
    void openFile(QString filename,QString filePath);

    //编辑器关闭文件
    void closeFile(QString filename,QString filePath);

    //文件是否在编辑器打开
    bool isFileOpened(QString filename,QString filePath);

    //编辑器切换已经打开的文件
    void switchFile(QString filename,QString filePath);

    std::vector<QString> getOpenedFile();


};

#endif // EDITOR_H
