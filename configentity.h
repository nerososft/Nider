#ifndef CONFIGENTITY_H
#define CONFIGENTITY_H
#include <QString>
class VEditor{
public:
       bool Enable;
};
class VProject{
public:
       bool Enable;
};
class VClass{
public:
       bool Enable;
};
class VTask{
public:
       bool Enable;
};
class VMark{
public:
       bool Enable;
};
class VDebug{
public:
       bool Enable;
};
class NView{
public:
       VProject vproject;
       VEditor veditor;
       VClass vclass;
       VTask task;
       VMark mark;
       VDebug debug;
};
class ConfigEntity
{
public:
    ConfigEntity();

    NView view;

    QString globleTheme;
    QString editorTheme;


};

#endif // CONFIGENTITY_H
