#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

#include <QDialog>
#include <map>
#include <string>
#include "errorhelper.h"
#include <QStandardItemModel>
#include <QJsonArray>

namespace Ui {
class NewProjectWindow;
}

class NewProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectWindow(QWidget *parent = 0);
    ~NewProjectWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_treeView_model_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::NewProjectWindow *ui;

    std::map<std::string,std::string>  modelMap;

    void loadModel(const  QString filePath);


    void initModelTree();

    ErrorHelper *err = new ErrorHelper();

    QJsonArray  model_array;

    QStandardItemModel* modelTreeModel;

    QString VERSION  = "0.0.3";
    int model_index = 0;
    QString model_path = ":/model/model/";

    void loadModelFiles();
    void copyModelFiles();
    void createNewProject();

};

#endif // NEWPROJECTWINDOW_H
