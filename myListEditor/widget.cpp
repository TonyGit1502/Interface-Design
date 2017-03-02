#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // layouts
    vbl_1 = new QVBoxLayout();
    vbl_2 = new QVBoxLayout();
    hbl_1 = new QHBoxLayout();
    hbl_2 = new QHBoxLayout();

    //lineEdits
    ln1 = new QLineEdit();
    ln2 = new QLineEdit();
    ln3 = new QLineEdit();
    ln4 = new QLineEdit();
    ln_ID = new QLineEdit();

    //actions & menu
    m_loadTableAction = new QAction("Load Table");
    m_addRecordAction = new QAction("Add record");
    m_deleteRecordAction = new QAction("Delete record");
    addButton1 = new QPushButton("Add the Client table");
    addButton2 = new QPushButton("Add the Product table");
    deleteButton1 = new QPushButton("Delete in the Client table");
    deleteButton2 = new QPushButton("Delete in the Product table");
    m_menuBar = new QMenuBar();
    m_menu1 = new QMenu("Databases manager");
    m_menu2 = new QMenu("Records manager");
            m_menu1->addAction(m_loadTableAction);
            m_menu2->addAction(m_addRecordAction);
            m_menu2->addAction(m_deleteRecordAction);
     m_menuBar->addMenu(m_menu1);
     m_menuBar->addMenu(m_menu2);

    //others
    m_tableWidget1 = new QTableWidget();
    m_tableWidget2 = new QTableWidget();
    m_listWidget = new QListWidget();

    vbl_1->addWidget(m_menuBar);
    vbl_1->addWidget(m_tableWidget1);
    hbl_1->addWidget(m_tableWidget2);
    vbl_1->addLayout(hbl_1);
    this->setLayout(vbl_1);

    //connects
    connect(m_loadTableAction, SIGNAL(triggered()), this, SLOT(loadTable()));
    connect(m_addRecordAction, SIGNAL(triggered()), this, SLOT(openAddWindow()));
    connect(m_deleteRecordAction, SIGNAL(triggered()), this, SLOT(openDeleteWindow()));

    connect(addButton1, SIGNAL(clicked()), this, SLOT(addClientRecord()));
    connect(addButton2, SIGNAL(clicked()), this, SLOT(addProductRecord()));
    connect(deleteButton1, SIGNAL(clicked()), this, SLOT(deleteClientRecord()));
    connect(deleteButton2, SIGNAL(clicked()), this, SLOT(deleteProductRecord()));
    connect(m_tableWidget1, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(changeData(int,int)));
}

Widget::~Widget()
{

}

void Widget::loadTable()
{
    baseName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "",
                                                tr("DataBase (*.mdb *.accdb)"));
    QStringList name;
    name << "SaleID" << "DataSale" << "ClientID" << "ProductID";
    m_tableWidget1->setColumnCount(4);
    m_tableWidget1->setHorizontalHeaderLabels(name);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "db");
    db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                       .arg(baseName));
    db.open();
    if (db.isOpen()) {
        QSqlQuery q(db);
        QString query;
        int countRows = 0;

        query = "SELECT COUNT(saleID) "
                "FROM sale, client, products "
                "WHERE "
                "(sale.clientID = client.clientID) AND "
                "(sale.productID = products.productID) ";


        if (q.exec(query)) {
            while (q.next()) {
                countRows = q.value(0).toInt();
            }
            m_tableWidget1->setRowCount(countRows);

            query = "SELECT * "
                    "FROM Sale ";

            if (q.exec(query)) {
                QTableWidgetItem *item;
                int row = 0;

                while (q.next()) {

                    for(int i = 0; i <= 3; i++) {
                        item = new QTableWidgetItem;
                        item->setText(q.value(i).toString());
                        m_tableWidget1->setItem(row, i, item);
                    }

                    row++;
                }
                db.close();
            }
            else {
                QMessageBox::critical(this, "", "Error!");
            }
        }
        else {
            QMessageBox::critical(this, "", "Error!");
        }
    }
    else {
        QMessageBox::warning(this, ""," Error!");
    }
}

void Widget::openAddWindow()
{
    wgt1 = new QWidget();
    QHBoxLayout *hbl1 = new QHBoxLayout();
    QHBoxLayout *hbl2 = new QHBoxLayout();
    QHBoxLayout *hbl3 = new QHBoxLayout();
    QVBoxLayout *vbl1 = new QVBoxLayout();
    label = new QLabel("ID");
    label1 = new QLabel("FIO");
    label2 = new QLabel("City");
    label3 = new QLabel("Index");
    label4 = new QLabel("ProductName");
    label5 = new QLabel("Characteristics");
    label6 = new QLabel("Price");
    vbl1->addWidget(label);
    vbl1->addWidget(ln_ID);
    hbl1->addWidget(label1);
    hbl1->addWidget(ln1);
    hbl1->addWidget(label4);
    hbl2->addWidget(label2);
    hbl2->addWidget(ln2);
    hbl2->addWidget(label5);
    hbl3->addWidget(label3);
    hbl3->addWidget(ln3);
    hbl3->addWidget(label6);
    vbl1->addLayout(hbl1);
    vbl1->addLayout(hbl2);
    vbl1->addLayout(hbl3);
    vbl1->addWidget(addButton1);
    vbl1->addWidget(addButton2);
    wgt1->setLayout(vbl1);
    wgt1->show();
}

void Widget::openDeleteWindow()
{
    wgt2 = new QWidget();
    QVBoxLayout *vbl1 = new QVBoxLayout();
    QLabel *label1 = new QLabel("ID");
    vbl1->addWidget(label1);
    vbl1->addWidget(ln4);
    vbl1->addWidget(deleteButton1);
    vbl1->addWidget(deleteButton2);
    wgt2->setLayout(vbl1);
    wgt2->show();
}

void Widget::addClientRecord()
{    
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "db");
    db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                       .arg(baseName));
    db.open();
    if (db.isOpen()) {
        QSqlQuery q(db);
        QString query;
        int id = ln_ID->text().toInt();
        QString FIO = ln1->text();
        QString City = ln2->text();
        int Index = ln3->text().toInt();
                query = QString("INSERT INTO Client "
                                "(ClientID, FIO, City, Index) "
                                "VALUES"
                                "(%1, '%2', '%3', %4);")
                        .arg(id)
                        .arg(FIO)
                        .arg(City)
                        .arg(Index);
        q.exec(query);

        QMessageBox::information(this, "", "Complete");
        db.close();
        wgt1->close();
    }
}

void Widget::deleteClientRecord()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "db");
    db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                       .arg(baseName));
    db.open();
    if (db.isOpen()) {
            int id = ln4->text().toInt();
            QSqlQuery q(db);
            QString query;
            query = QString("DELETE FROM Client WHERE ClientID=%1").arg(id);
            q.exec(query);
            QMessageBox::information(this, "", "Complete!");
            db.close();
            wgt2->close();
    }
    else
        QMessageBox::information(this, "", "Error!");
}


void Widget::addProductRecord()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "db");
    db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                       .arg(baseName));
    db.open();
    if (db.isOpen()) {
        QSqlQuery q(db);
        QString query;
        int id = ln_ID->text().toInt();
        QString productName = ln1->text();
        QString characters = ln2->text();
        int price = ln3->text().toInt();
                query = QString("INSERT INTO Products "
                                "(ProductID, ProductName, Characteristics, Price) "
                                "VALUES"
                                "(%1, '%2', '%3', %4);")
                        .arg(id)
                        .arg(productName)
                        .arg(characters)
                        .arg(price);
        q.exec(query);
        QMessageBox::information(this, "", "Complete");
        db.close();
        wgt1->close();
    }
}

void Widget::deleteProductRecord()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "db");
    db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                       .arg(baseName));
    db.open();
    if (db.isOpen()) {
            int id = ln4->text().toInt();
            QSqlQuery q(db);
            QString query;
            query = QString("DELETE FROM Products WHERE ProductID=%1").arg(id);
            q.exec(query);
            QMessageBox::information(this, "", "Complete!");
            db.close();
            wgt2->close();
    }
    else
        QMessageBox::information(this, "", "Error!");
}

void Widget::changeData(int row, int column)
{
    if(column==2){
            m_tableWidget2->setColumnCount(4);
            QStringList clientName;
            clientName<<"ClientID"<<"FIO"<<"City"<<"Index";
            m_tableWidget2->setHorizontalHeaderLabels(clientName);
            QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "db");
            db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                               .arg(baseName));
            db.open();
            if (db.isOpen()) {
                QSqlQuery q(db);
                QString query;

                int countRows = 0;

                query = "SELECT COUNT(*) "
                        "FROM Client ";

                if (q.exec(query)) {
                    while (q.next()) {
                        countRows = q.value(0).toInt();
                    }
                m_tableWidget2->setRowCount(countRows);
                }

                query = "SELECT * FROM Client";
                if (q.exec(query)) {
                    QTableWidgetItem *item;
                    int row = 0;

                    while (q.next()) {

                        for(int i = 0; i <= 3; i++) {
                            item = new QTableWidgetItem;
                            item->setText(q.value(i).toString());
                            m_tableWidget2->setItem(row, i, item);
                        }
                        row++;
                    }
                    db.close();
                }
            }
    }
    else if(column==3){
        m_tableWidget2->setColumnCount(4);
        QStringList clientName;
        clientName<<"ProductID"<<"ProductName"<<"Characteristics"<<"Price";
        m_tableWidget2->setHorizontalHeaderLabels(clientName);
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "db");
        db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                           .arg(baseName));
        db.open();
        if (db.isOpen()) {
            QSqlQuery q(db);
            QString query;
            int countRows = 0;

            query = "SELECT COUNT(*) "
                    "FROM Products ";

            if (q.exec(query)) {
                while (q.next()) {
                    countRows = q.value(0).toInt();
                }
            m_tableWidget2->setRowCount(countRows);
            }

            query = "SELECT * FROM Products";
            if (q.exec(query)) {
                QTableWidgetItem *item;
                int row = 0;

                while (q.next()) {

                    for(int i = 0; i <= 3; i++) {
                        item = new QTableWidgetItem;
                        item->setText(q.value(i).toString());
                        m_tableWidget2->setItem(row, i, item);
                    }

                    row++;
                }
                db.close();
            }
        }
    }
}

