#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //  layouts
    vbl_1 = new QVBoxLayout();

    //  actions
    m_addImageAction = new QAction("Add Image");
    m_addTableAction = new QAction("Create Table");
    m_addRowAction = new QAction("Add Table Row");
    m_addColumnAction = new QAction("Add Table Column");
    m_removeRowAction = new QAction("Remove Table Row");
    m_removeColumnAction = new QAction("Remove Table Column");
    m_openAction = new QAction("Open");
    m_saveAction = new QAction("Save");
    m_clearFile = new QAction("Clear file");
    m_exitAction = new QAction("Close SimpleTextEditor");
    m_changeColorAction = new QAction("Change color");
    m_changeFontAction = new QAction("Change font");
    m_leftAlignAction = new QAction("Left");
    m_rightAlignAction = new QAction("Right");
    m_centerAlignAction = new QAction("Center");
    m_justifyAlignAction = new QAction("Justify");


    //  menuBar
    m_menuBar1 = new QMenuBar();
    m_menu = new QMenu("File");
    m_menu1 = new QMenu("Table");
    m_menu2 = new QMenu("Image");
    m_menu3 = new QMenu("Exit");
        m_menu->addAction(m_openAction);
        m_menu->addAction(m_saveAction);
        m_menu->addAction(m_clearFile);
        QMenu *submenu = new QMenu("Alignment");
        m_menu->addMenu(submenu);
                submenu->addAction(m_leftAlignAction);
                submenu->addAction(m_rightAlignAction);
                submenu->addAction(m_centerAlignAction);
                submenu->addAction(m_justifyAlignAction);
        m_menu->addAction(m_changeColorAction);
        m_menu->addAction(m_changeFontAction);
        m_menu1->addAction(m_addTableAction);
        QMenu *submenu1 = new QMenu("Add");
        m_menu1->addMenu(submenu1);
                submenu1->addAction(m_addRowAction);
                submenu1->addAction(m_addColumnAction);
        QMenu *submenu2 = new QMenu("Remove");
        m_menu1->addMenu(submenu2);
                submenu2->addAction(m_removeRowAction);
                submenu2->addAction(m_removeColumnAction);
        m_menu2->addAction(m_addImageAction);
        m_menu3->addAction(m_exitAction);
    m_menuBar1->addMenu(m_menu);
    m_menuBar1->addMenu(m_menu1);
    m_menuBar1->addMenu(m_menu2);
    m_menuBar1->addMenu(m_menu3);

    //   textEdit
    textEdit = new QTextEdit();
    textEdit->setStyleSheet("background:#000; color: #fff;");
    vbl_1->addWidget(m_menuBar1);
    vbl_1->addWidget(textEdit);
    m_menuBar1->setStyleSheet("background: dark orange;");
    this->setLayout(vbl_1);
    this->setWindowTitle("SimpleTextEditor");

    //  connects
    connect(m_addImageAction,SIGNAL(triggered()), this, SLOT(addImage()));
    connect(m_addTableAction, SIGNAL(triggered()), this, SLOT(addTable()));
    connect(m_openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(m_saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(exitEditor()));
    connect(m_changeColorAction, SIGNAL(triggered()), this, SLOT(changeColor()));
    connect(m_changeFontAction, SIGNAL(triggered()), this, SLOT(changeFont()));
    connect(m_clearFile, SIGNAL(triggered()), this, SLOT(clearFile()));
    //  alignment
    connect(m_leftAlignAction, SIGNAL(triggered()), this, SLOT(textAlignLeft()));
    connect(m_rightAlignAction, SIGNAL(triggered()), this, SLOT(textAlignRight()));
    connect(m_centerAlignAction, SIGNAL(triggered()), this, SLOT(textAlignCenter()));
    connect(m_justifyAlignAction, SIGNAL(triggered()), this, SLOT(textAlignJustify()));

    //  table
    connect(m_addRowAction, SIGNAL(triggered()), this, SLOT(addTableRow()));
    connect(m_addColumnAction, SIGNAL(triggered()), this, SLOT(addTableColumn()));
    connect(m_removeRowAction, SIGNAL(triggered()), this, SLOT(removeTableRow()));
    connect(m_removeColumnAction, SIGNAL(triggered()), this, SLOT(removeTableColumn()));

}

Widget::~Widget()
{

}

void Widget::addImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "", tr("Images (*.png *.bmp *.jpg)"));
    QTextCursor cursor(textEdit->textCursor());
    cursor.insertImage(fileName);
}

void Widget::addTable()
{
    QTextCursor cursor(textEdit->textCursor());
    table = cursor.insertTable(4,4);
}

void Widget::addTableRow()
{
    table->appendRows(1);
}

void Widget::addTableColumn()
{
    table->appendColumns(1);
}

void Widget::removeTableRow()
{
    table->removeRows(table->rows()-1, 1);
}

void Widget::removeTableColumn()
{
    table->removeColumns(table->columns()-1, 1);
}

void Widget::saveFile()
{
    QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("C:/Users/Anton/Desktop/print.pdf");
        textEdit->document()->print(&printer);
}

void Widget::openFile()
{
    textEdit->clear();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Files (*.txt *.docx *.cpp)"));
    QFile file;
    file.setFileName(fileName);
    if (file.open(QIODevice::ReadOnly)){
        QString text = QString::fromLocal8Bit(file.readAll());
        file.close();
        textEdit->setPlainText(text);
    }
}

void Widget::clearFile()
{
    textEdit->clear();
}

void Widget::exitEditor()
{
        this->close();
}

void Widget::changeFont()
{
    QTextCharFormat tcharFormat = textEdit->textCursor().charFormat();
    tcharFormat.setFont(QFontDialog::getFont(0, this->font()));
    textEdit->textCursor().setCharFormat(tcharFormat);
}

void Widget::changeColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if (color.isValid()){
        textEdit->setTextColor(color);
    }
}

void Widget::textAlignLeft()
{
    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft );
    cursor.mergeBlockFormat(textBlockFormat);
    textEdit->setTextCursor(cursor);
}

void Widget::textAlignRight()
{
    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(textBlockFormat);
    textEdit->setTextCursor(cursor);
}

void Widget::textAlignCenter()
{
    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    textEdit->setTextCursor(cursor);
}

void Widget::textAlignJustify()
{
    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(textBlockFormat);
    textEdit->setTextCursor(cursor);
}
