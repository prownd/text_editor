#include <QtGui/QApplication>
#include "editor.h"
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    editor w;
    w.show();
    return a.exec();
}

