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
#include <QPushButton>
#include <QSignalMapper>

#include "lib/qtermwidget.h"

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

     void onTopClicked(QString index);


     void on_actionOpenFolder_triggered();

private:
    Ui::MainWindow *ui;

    std::map<QString,HighLightType> codeTable;
    std::map<HighLightType,QColor>* codeColor;
    std::map<int,std::map<HighLightType,std::map<int,int>>>* allHighLightTable;

     Highlighter* highlighter;

    void initUi();

    void  setupEditor();

    void renderTitle(QString file);

    QPushButton* editorTop[9];

    QJsonObject projectOBJ;
    ProjectEntity project;

    Project* pp;

    FileManager fileManager;
    EditorManager editorManager;
    QString projectPath = "";

    QSignalMapper *signalMapper = new QSignalMapper(this);



    void EditAddFileTitle(QString filename);

    QString fileIndex = "";

    int topIndex = 0;

    QTermWidget *console;

};

#endif // MAINWINDOW_H
