#include "errorhelper.h"
#include <QMessageBox>

ErrorHelper::ErrorHelper()
{

}

void ErrorHelper::Error(QString error){
    QMessageBox::critical(NULL, "critical", "发生了致命的错误:"+error+"!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
