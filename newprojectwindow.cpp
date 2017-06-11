#include "newprojectwindow.h"
#include "ui_newprojectwindow.h"
#include <QFileDialog>
#include <QStandardItem>
#include <QFile>
#include <QTextStream>
#include "jsonhelper.h"
#include  <iostream>
#include <QMessageBox>
#include <QDir>
#include "filehelper.h"
#include "projectentity.h"

NewProjectWindow::NewProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectWindow)
{
    ui->setupUi(this);


    this->initModelTree();


}

void NewProjectWindow::initModelTree(){
    loadModel(":/model/tree/model.json");
}
void NewProjectWindow::loadModel(const QString filePath){

    FileHelper fileHelper;

    QString buffer = fileHelper.loadFileToString(filePath);

    JsonHelper jsonHelper;
    this->model_array = jsonHelper.getJsonArrayFromString(buffer);

    this->modelTreeModel= new QStandardItemModel(ui->treeView_model);
    QStandardItem*  modelItem;

    for(int i  =0;i<this->model_array.count();i++){

        QJsonObject obj  = this->model_array[i].toObject();
        qDebug()<<"load_model:"<<obj.find("model").value().toString();
        QString item_icon = obj.find("icon").value().toString();
        QString item_model = obj.find("model").value().toString();
        modelItem = new QStandardItem(QIcon(item_icon),item_model);

        this->modelTreeModel->appendRow(modelItem);
    }

    ui->treeView_model->setModel(this->modelTreeModel);

}

NewProjectWindow::~NewProjectWindow()
{
    delete ui;
}

void NewProjectWindow::on_pushButton_2_clicked()
{
    this->close();
}


void NewProjectWindow::on_pushButton_clicked()
{
    if(ui->lineEdit_ProjectName->text()!=""){
    QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        if (dialog.exec()){
            ui->lineEdit_path->clear();
            QString file=dialog.selectedFiles()[0];
            QString path = file+"/"+ui->lineEdit_ProjectName->text();
             ui->lineEdit_path->setText(path);
        }
    }else{
        ui->lineEdit_ProjectName->setFocus();
    }
}

void NewProjectWindow::loadModelFiles(){

}
void NewProjectWindow::copyModelFiles(){

}
void NewProjectWindow::createNewProject(){
    //step 1 : load exist model files from model forder;

    //step 2 :copy loaded model files to new project forder ;

    //step 3 :create project defination file project.nproj;

    //step 4 :load project to Nider

}

void NewProjectWindow::on_treeView_model_clicked(const QModelIndex &index)
{
    this->model_index = index.row();

    ui->project_define->setTitle(this->model_array.at(index.row()).toObject().find("model").value().toString());
    ui->model_desc->setText(this->model_array.at(index.row()).toObject().find("desc").value().toString());

}

void NewProjectWindow::on_pushButton_3_clicked()
{
    QString path = ui->lineEdit_path->text();
    QDir dir(path);
    if(dir.exists()){
           ui->lineEdit_ProjectName->setFocus();
          this->err->Error(ui->lineEdit_path->text()+"已经存在");
   }else{
                      bool isDirCretae = dir.mkdir(path);
                      if(!isDirCretae){
                          this->err->Error("项目目录创建失败");
                      }else{
                           FileHelper fileHelper;
                           QString modelPath = this->model_path+this->model_array.at(this->model_index).toObject().find("model_id").value().toString()+"/";
                           if(!fileHelper.copyDirectoryFiles(modelPath,path,true)){
                               this->err->Error("从模版创建失败");
                           }else{
                               QJsonDocument pn;
                               QJsonObject project;
                               project.insert("version",this->VERSION);
                               project.insert("projectname",ui->lineEdit_ProjectName->text());

                               QJsonArray source;
                               QFileInfoList cpplist = fileHelper.getFileList(path,"cpp");
                               int source_index = 0;
                               foreach(QFileInfo file,cpplist){
                                   QJsonObject ss;
                                   ss.insert("src",file.fileName());

                                   source.insert(source_index,ss);
                                   source_index++;
                               }
                               QJsonArray header;
                               QFileInfoList hlist = fileHelper.getFileList(path,"h");
                               int header_index = 0;
                               foreach(QFileInfo file,hlist){
                                   QJsonObject h;
                                   h.insert("src",file.fileName());
                                   header.insert(header_index,h);
                                   header_index++;
                               }
                               project.insert("source",source);
                               project.insert("header",header);
                               pn.setObject(project);
                               QString projectdefine = QString(pn.toJson());
                               if(!fileHelper.createFile(path+"/"+ui->lineEdit_ProjectName->text()+".nproj",projectdefine)){
                                    this->err->Error("项目创建失败");
                               }else{
                                   this->err->Error("项目"+ui->lineEdit_ProjectName->text()+"创建成功");
                                   this->close();
                               }

                               qDebug()<<path;
                               qDebug()<<"create .nproj file";
                           }
                      }
                }
}
