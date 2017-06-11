#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = 0);
    ~SettingWindow();

private slots:
    void on_setting_cancel_clicked();

private:
    Ui::SettingWindow *ui;
};

#endif // SETTINGWINDOW_H
