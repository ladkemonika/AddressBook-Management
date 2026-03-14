#include "mainwindow.h"
#include "contactdialog.h"

#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    
    // Determine path for data file
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    dataFilePath = dir.filePath("contacts.json");

    loadContacts();
    updateTable();
}

MainWindow::~MainWindow()
{
    saveContacts();
}

void MainWindow::setupUi()
{
    setWindowTitle(tr("Address Book"));
    resize(600, 400);

    tableWidget = new QTableWidget(0, 4, this);
    tableWidget->setHorizontalHeaderLabels({tr("Name"), tr("Mobile"), tr("Email"), tr("Birthday")});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPushButton *addButton = new QPushButton(tr("Add"), this);
    QPushButton *editButton = new QPushButton(tr("Edit"), this);
    QPushButton *deleteButton = new QPushButton(tr("Delete"), this);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addContact);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editContact);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteContact);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::loadContacts()
{
    QFile loadFile(dataFilePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    contacts.clear();
    QJsonArray jsonArray = loadDoc.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject jsonObject = jsonArray[i].toObject();
        contacts.append(Contact::fromJson(jsonObject));
    }
}

void MainWindow::saveContacts()
{
    QFile saveFile(dataFilePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonArray jsonArray;
    for (const Contact &contact : std::as_const(contacts)) {
        jsonArray.append(contact.toJson());
    }

    QJsonDocument saveDoc(jsonArray);
    saveFile.write(saveDoc.toJson());
}

void MainWindow::updateTable()
{
    tableWidget->setRowCount(0);
    for (int i = 0; i < contacts.size(); ++i) {
        const Contact &contact = contacts.at(i);
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(contact.name));
        tableWidget->setItem(i, 1, new QTableWidgetItem(contact.mobile));
        tableWidget->setItem(i, 2, new QTableWidgetItem(contact.email));
        tableWidget->setItem(i, 3, new QTableWidgetItem(contact.birthday.isValid() ? contact.birthday.toString(Qt::ISODate) : ""));
    }
}

void MainWindow::addContact()
{
    ContactDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        contacts.append(dialog.getContact());
        updateTable();
        saveContacts();
    }
}

void MainWindow::editContact()
{
    int row = tableWidget->currentRow();
    if (row < 0 || row >= contacts.size()) {
        QMessageBox::warning(this, tr("Edit Contact"), tr("Please select a contact to edit."));
        return;
    }

    ContactDialog dialog(this);
    dialog.setContact(contacts.at(row));
    if (dialog.exec() == QDialog::Accepted) {
        contacts[row] = dialog.getContact();
        updateTable();
        saveContacts();
    }
}

void MainWindow::deleteContact()
{
    int row = tableWidget->currentRow();
    if (row < 0 || row >= contacts.size()) {
        QMessageBox::warning(this, tr("Delete Contact"), tr("Please select a contact to delete."));
        return;
    }

    int ret = QMessageBox::question(this, tr("Delete Contact"),
                                    tr("Are you sure you want to delete this contact?"),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        contacts.removeAt(row);
        updateTable();
        saveContacts();
    }
}
