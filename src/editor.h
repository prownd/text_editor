#ifndef EDITOR_H
#define EDITOR_H
#include <QMainWindow>
#include<QLineEdit>

namespace Ui {
    class editor;
}

class editor : public QMainWindow {
    Q_OBJECT
public:
    editor(QWidget *parent = 0);
    ~editor();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::editor *ui;
    bool isSaved;
    QString curFile;
    void do_file_new();
    void do_file_saveOrnot();
    void do_file_save();
    void do_file_saveas();
    bool saveFile(const QString & Filename);
    QLineEdit * find_textLineEdit;

private slots:
    void on_actionAbout_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionUndo_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionSelect_triggered();
    void on_actionCut_triggered();
    void on_actionFind_triggered();
    void show_findText();
};



#endif // EDITOR_H
