
#include "editor.h"
#include "ui_editor.h"
#include <QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QPushButton>
//#include<QCFindDialog>
editor::editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::editor)
{
    ui->setupUi(this);
    isSaved=false;
    curFile=tr("Untitled Document.txt");
    setWindowTitle(curFile);
    ui->actionClose->setEnabled(false);

}

editor::~editor()
{
    delete ui;
}

void editor::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void editor::on_actionOpen_triggered()
{
    QString filestr=QFileDialog::getOpenFileName();
    QFile qf(filestr);
    QTextStream qfs(&qf);
    qf.open(QFile::ReadOnly);
    ui->textEdit->setText(qfs.readAll());
    qf.close();;

}
void editor::do_file_new()
{
    do_file_saveOrnot();
    isSaved=false;
    curFile=tr("noname.txt");
    setWindowTitle(curFile);
    ui->textEdit->clear();
}
void editor::do_file_saveOrnot()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle(tr("warring"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr("it''s not saved，save it?"));
        box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        if(box.exec()==QMessageBox::Yes)
        {
            do_file_save();
        }
    }
}
void editor::do_file_save()
{
    if(isSaved)
    {
        saveFile(curFile);
    }else
    {
        do_file_saveas();
    }
}

void editor::do_file_saveas()
{
    QString filename=QFileDialog::getSaveFileName(this,tr("save it"),curFile);
    if(!filename.isEmpty())
    {
        saveFile(filename);
    }
}

bool editor::saveFile(const QString &Filename)
{
    QFile file(Filename);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        //弹出对话框
        QMessageBox::warning(this,"warning","cannot save");
    }
    QTextStream out(&file);
    out<<ui->textEdit->toPlainText();
    isSaved=true;
    curFile=Filename;
    setWindowTitle(curFile);
    ui->actionClose->setEnabled(true);
    return true;
}

void editor::on_actionNew_triggered()
{
    do_file_new();
}

void editor::on_actionSave_triggered()
{
    do_file_save();
}

void editor::on_actionSave_as_triggered()
{
    do_file_saveas();
}

void editor::on_actionExit_triggered()
{
    this->close();
}

void editor::on_actionClose_triggered()
{
    ui->textEdit->clear();
    isSaved=false;
    curFile=tr("未命名.txt");
    setWindowTitle(curFile);
    ui->actionClose->setEnabled(false);
    ui->textEdit->setVisible(false);
}

void editor::on_actionAbout_triggered()
{
    QMessageBox::about(this,"about",tr("write by hanjinpeng，version 0.1. email:545751287@qq.com!"));
}

void editor::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void editor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void editor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void editor::on_actionSelect_triggered()
{
    ui->textEdit->selectAll();
}

void editor::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void editor::on_actionFind_triggered()
{
    QDialog *findDlg=new QDialog(this);
    findDlg->setWindowTitle (tr("find"));
    find_textLineEdit=new QLineEdit(findDlg);
    QPushButton * find_btn=new QPushButton(tr("find next"),findDlg);
    QVBoxLayout* layout=new QVBoxLayout(findDlg);
    layout->addWidget (find_textLineEdit);
    layout->addWidget (find_btn);
    findDlg->show();
    connect (find_btn,SIGNAL(clicked()),this,SLOT(show_findText()));
}
void editor::show_findText ()
{
    QString findText=find_textLineEdit->text ();
    if(!ui->textEdit->find (findText,QTextDocument::FindBackward))
    {
        QMessageBox::warning (this,tr("find"),tr("not found %1").arg (findText));
    }
}
