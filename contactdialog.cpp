#include "contactdialog.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>

ContactDialog::ContactDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
}

ContactDialog::~ContactDialog()
{
}

void ContactDialog::setupUi()
{
    setWindowTitle(tr("Contact Details"));

    nameEdit = new QLineEdit(this);
    mobileEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    birthdayEdit = new QDateEdit(this);
    birthdayEdit->setCalendarPopup(true);
    birthdayEdit->setDisplayFormat("yyyy-MM-dd");
    birthdayEdit->setDate(QDate::currentDate());

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Name:"), nameEdit);
    formLayout->addRow(tr("&Mobile:"), mobileEdit);
    formLayout->addRow(tr("&Email:"), emailEdit);
    formLayout->addRow(tr("&Birthday:"), birthdayEdit);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void ContactDialog::setContact(const Contact &contact)
{
    nameEdit->setText(contact.name);
    mobileEdit->setText(contact.mobile);
    emailEdit->setText(contact.email);
    if (contact.birthday.isValid()) {
        birthdayEdit->setDate(contact.birthday);
    } else {
        birthdayEdit->setDate(QDate::currentDate());
    }
}

Contact ContactDialog::getContact() const
{
    Contact contact;
    contact.name = nameEdit->text();
    contact.mobile = mobileEdit->text();
    contact.email = emailEdit->text();
    contact.birthday = birthdayEdit->date();
    return contact;
}
