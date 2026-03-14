#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "contact.h"

class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addContact();
    void editContact();
    void deleteContact();

private:
    void setupUi();
    void loadContacts();
    void saveContacts();
    void updateTable();

    QTableWidget *tableWidget;
    QList<Contact> contacts;
    QString dataFilePath;
};

#endif // MAINWINDOW_H
