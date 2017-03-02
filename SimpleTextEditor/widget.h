#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QColorDialog>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QFont>
#include <QFontDialog>
#include <QFile>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QVBoxLayout *vbl_1;
    QMenuBar *m_menuBar1;
    QMenu *m_menu, *m_menu1, *m_menu2, *m_menu3;
    QAction *m_openAction, *m_saveAction, *m_exitAction, *m_addImageAction, *m_clearFile;
    QAction *m_addTableAction, *m_addRowAction, *m_addColumnAction, *m_removeRowAction, *m_removeColumnAction;
    QAction *m_changeFontAction, *m_changeColorAction;
    QAction *m_leftAlignAction, *m_rightAlignAction, *m_centerAlignAction, *m_justifyAlignAction;
    QTextEdit *textEdit;
    QTextTable *table;
public slots:
        void addImage();
        void addTable();
        void addTableRow();
        void addTableColumn();
        void removeTableRow();
        void removeTableColumn();
        void saveFile();
        void openFile();
        void clearFile();
        void exitEditor();
        void changeFont();
        void changeColor();
        void textAlignLeft();
        void textAlignRight();
        void textAlignCenter();
        void textAlignJustify();

};



#endif // WIDGET_H
