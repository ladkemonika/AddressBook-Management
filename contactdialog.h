#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>
#include "contact.h"

class QLineEdit;
class QDateEdit;
class QDialogButtonBox;

class ContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactDialog(QWidget *parent = nullptr);
    ~ContactDialog();

    void setContact(const Contact &contact);
    Contact getContact() const;

private:
    QLineEdit *nameEdit;
    QLineEdit *mobileEdit;
    QLineEdit *emailEdit;
    QDateEdit *birthdayEdit;
    QDialogButtonBox *buttonBox;

    void setupUi();
};

#endif // CONTACTDIALOG_H
