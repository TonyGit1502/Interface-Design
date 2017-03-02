#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QLabel>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QListWidget *m_listWidget;
    QTableWidget *m_tableWidget1, *m_tableWidget2;
    QPushButton *addOpenWindow, *addDeleteWindow;
    QPushButton *addButton1, *addButton2, *deleteButton1, *deleteButton2;
    QVBoxLayout *vbl_1, *vbl_2;
    QHBoxLayout *hbl_1, *hbl_2;
    QAction *m_loadTableAction, *m_addRecordAction, *m_deleteRecordAction;
    QMenuBar *m_menuBar;
    QMenu *m_menu1, *m_menu2;
    QLabel *label, *label1, *label2, *label3, *label4, *label5, *label6;
    QLineEdit *ln1, *ln2, *ln3, *ln4, *ln_ID;
    QWidget *wgt1, *wgt2;

    QString baseName;
    QStringList columnName;

public slots:
        void loadTable();
        void openAddWindow();
        void openDeleteWindow();
        void addClientRecord();
        void deleteClientRecord();
        void addProductRecord();
        void deleteProductRecord();
        void changeData(int row,int column);

};

#endif // WIDGET_H
