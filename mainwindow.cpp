#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDirModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "newprojectwindow.h"
#include "settingwindow.h"
#include <QDebug>
#include "filehelper.h"
#include <QJsonObject>
#include "jsonhelper.h"
#include "project.h"
#include <QSpacerItem>
#include <QSignalMapper>
#include <QtCore>
#include <QtGui>
#include "generalproject.h"

QLabel *q;
QPushButton *tor;
void MainWindow::initUi(){

    ui->setupUi(this);
    q = new QLabel("Col:  Row: ");
    this->statusBar()->addWidget(q);

    tor = new QPushButton("");
    tor->setIcon(QIcon(":/icon/tor.png"));
    tor->setStyleSheet("color:white;border:none;background:rgba(51, 51, 51,0);");
    this->statusBar()->addWidget(tor);

    QFile qssfile(":/styles/base.qss");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();


    //setWindowIcon(QIcon("logo.ico"));
    // this->setStyleSheet(qss);


    this->setupEditor();


    this->console = new QTermWidget();
   QFont font = QApplication::font();
   font.setFamily("Terminus");
    font.setPointSize(12);
    this->console->setTerminalFont(font);
    console->setColorScheme(DEFAULT);
    this->console->setScrollBarPosition(QTermWidget::ScrollBarRight);
    this->console->setStyleSheet("background:rgba(0,0,0,0)");
    this->ui->term->addWidget(console);

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initUi();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(20);

    ui->textEdit->setFont(font);

    highlighter = new Highlighter(ui->textEdit->document());

    for(int i = 0;i<9;i++){
        QPushButton* editorTopB = new QPushButton("");
        editorTopB->setStyleSheet("background:rgba(0, 128, 255,0);color:rgb(255, 255, 255);width:100px;border:none;margin:0;padding:4px;margin-left:1px;");
        this->editorTop[i] = editorTopB;
        connect(editorTop[i], SIGNAL(clicked()), this->signalMapper, SLOT(map()));
    }
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onTopClicked(QString)));
    this->editorTop[0]->setStyleSheet("background:rgb(0, 128, 255);color:rgb(255, 255, 255);width:100x;border:none;margin:0;padding:4px;margin-left:1px;");
    this->editorTop[0]->setText("欢迎页");


    for (int i = 0;i<9;i++){
        this->ui->edit_title->addWidget(editorTop[i]);
    }

}

void MainWindow::on_actionNew_Project_triggered()
{
    NewProjectWindow newProjectWindow;
    newProjectWindow.show();
    newProjectWindow.exec();
}

void MainWindow::on_actionSetting_triggered()
{
    SettingWindow setting;
    setting.show();
    setting.exec();
}

void MainWindow::on_actionOpen_Project_triggered()
{
    QFileDialog projectDialog;
    QString path = projectDialog.getOpenFileName(this, tr("Open Nide project"), ".", tr("Nide project Files(*.nproj)"));
    if(path.length() != 0) {
        QFile file(path);
        FileHelper fileHelper;
        JsonHelper jsonHelper;
        QString buffer =  fileHelper.loadFileToString(path);
        this->projectOBJ = jsonHelper.getJsonObjectFromString(buffer);

        this->pp =  new Project(this->projectOBJ);
        this->ui->projectName->setText(this->pp->getProjectName());
        this->ui->listView_undo->setModel(this->pp->getTaskUndo());
        this->ui->listView_doing->setModel(this->pp->getTaskDoing());
        this->ui->listView_done->setModel(this->pp->getTaskDone());
        this->ui->treeViewProject->setModel(this->pp->getProjectTree());



        this->projectPath = QFileInfo(path).absolutePath()+"/";
        projectDialog.close();

    }

}

int num = 0;
void MainWindow::on_textEdit_textChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    int ColNum = cursor.columnNumber();
    int RowNum = cursor.blockNumber();
    QString bottomS = "Col: "+QString::number(ColNum,10)+" Row: "+QString::number(RowNum,10);
    for(int i = 0;i<ColNum;i++){
        bottomS+="   ";
    }

    if(num == 1){
        tor->setIcon(QIcon(":/icon/tor_run.png"));
        num = 0;
    }else{
        tor->setIcon(QIcon(":/icon/tor.png"));
        num++;
    }

    q->setText(bottomS);
}
void MainWindow::EditAddFileTitle(QString filename){
    if(!this->editorManager.isFileOpened(filename,this->projectPath)){
        QPushButton* push = new QPushButton(filename);
        push->setStyleSheet("background:rgb(0, 128, 255);color:rgb(255, 255, 255);border:none;width:100px;margin:0;padding:4px;margin-left:1px;");
        this->ui->edit_title->addWidget(push,0);
    }
}


void MainWindow::onTopClicked(QString index){


    if(this->fileIndex!=""){
        FileHelper filehelper;
        if(!filehelper.saveFile(this->projectPath+this->fileIndex,this->ui->textEdit->toPlainText())){
            this->ui->textBrowser_output->setText(this->ui->textBrowser_output->toPlainText()+"\n"+"文件"+this->projectPath+this->fileIndex+"保存失败");
        }else{
            if(!this->fileManager.updateFileBuffer(this->fileIndex,this->ui->textEdit->toPlainText())){
                this->ui->textBrowser_output->setText(this->ui->textBrowser_output->toPlainText()+"\n"+"buffer"+this->projectPath+this->fileIndex+"更新失败");
            }
        }
        this->ui->textBrowser_output->setText(this->ui->textBrowser_output->toPlainText()+"\n"+"文件"+this->projectPath+this->fileIndex+"保存成功");

    }
    this->fileIndex = index;

    renderTitle(index);
    this->ui->textEdit->setText(fileManager.getBufferedFile(index,this->projectPath));
}

void MainWindow::renderTitle(QString file){
    std::vector<QString> opened = this->editorManager.getOpenedFile();
    int finalcount = (opened.size()>=9 ? 9: opened.size());

    for(int i = 0; i<finalcount;i++){
        this->editorTop[i]->setText(opened.at(i));
        if(opened.at(i)==file){

            this->editorTop[i]->setStyleSheet("background:rgb(0, 128, 255);color:rgb(255, 255, 255);width:100px;border:none;margin:0;padding:4px;margin-left:1px;");
        }else{

            this->editorTop[i]->setStyleSheet("background:rgb(45, 45, 48);color:rgb(255, 255, 255);width:100px;border:none;margin:0;padding:4px;margin-left:1px;");
        }
        QString ff = editorTop[i]->text();
        this->signalMapper->setMapping(editorTop[i], ff);

    }

}


void MainWindow::on_treeViewProject_clicked(const QModelIndex &index)
{
    QString str;

    str = QStringLiteral("%1").arg(index.data().toString());

    if(str!="Sources"&&str!="Headers"){


        //this->EditAddFileTitle(str);
        this->editorManager.openFile(str,this->projectPath);

        if(this->fileIndex!=""){
            FileHelper filehelper;
            if(!filehelper.saveFile(this->projectPath+this->fileIndex,this->ui->textEdit->toPlainText())){
                this->ui->textBrowser_output->setText(this->ui->textBrowser_output->toPlainText()+"\n"+"文件"+this->projectPath+this->fileIndex+"保存失败");
            }else{
                if(!this->fileManager.updateFileBuffer(this->fileIndex,this->ui->textEdit->toPlainText())){
                    this->ui->textBrowser_output->setText(this->ui->textBrowser_output->toPlainText()+"\n"+"buffer"+this->projectPath+this->fileIndex+"更新失败");
                }
            }
            this->ui->textBrowser_output->setText(this->ui->textBrowser_output->toPlainText()+"\n"+"文件"+this->projectPath+this->fileIndex+"保存成功");
        }
        this->fileIndex = str;


        this->ui->textEdit->setFontPointSize(20);

        this->ui->textEdit->setText(fileManager.getBufferedFile(str,this->projectPath));
        if(this->projectPath!=""){
            this->ui->markList->setModel(this->pp->getMark(str));
        }
        renderTitle(str);

    }





}

void MainWindow::on_actionOpenFolder_triggered()
{
    QFileDialog projectDialog;
    QString path = projectDialog.getExistingDirectory(this,"打开目录","~/");
    if(path.length() != 0) {
        GeneralProject gen;
        this->ui->treeViewProject->setModel(gen.getCurrentForder(path));



    }
}
