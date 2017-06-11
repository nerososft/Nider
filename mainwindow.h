#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "highlighttype.h"
#include <map>
#include "highlighter.h"
#include <QJsonObject>
#include "projectentity.h"
#include "filemanager.h"
#include "editor.h"
#include "project.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:


public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:






     void on_actionNew_Project_triggered();

     void on_actionSetting_triggered();

     void on_actionOpen_Project_triggered();

     void on_textEdit_textChanged();

     void on_treeViewProject_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    std::map<QString,HighLightType> codeTable;
    std::map<HighLightType,QColor>* codeColor;
    std::map<int,std::map<HighLightType,std::map<int,int>>>* allHighLightTable;

     Highlighter* highlighter;

    void initUi();

    void  setupEditor();


    QJsonObject projectOBJ;
    ProjectEntity project;

    Project* pp;

    FileManager fileManager;
    EditorManager editorManager;
    QString projectPath;

    void EditAddFileTitle(QString filename);


};

#endif // MAINWINDOW_H
