#include "QTContacts.hpp"
#include "Contact.hpp"
#include "QTContactItem.hpp"
#include <QAbstractButton>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QListWidgetItem>
#include <QPushButton>
#include <iostream>
#include <qchar.h>
#include <qdialog.h>
#include <qdialogbuttonbox.h>
#include <qformlayout.h>
#include <sstream>

using namespace Ui;

QTContacts::QTContacts(Contacts::ContactsService &service) : service(service) {
  listView = new QListWidget();
  connect(listView, &QListWidget::itemDoubleClicked, this,
          &QTContacts::openDialogMenu);

  auto *itemO1 = new QListWidgetItem("Add contact Name");
  itemO1->setBackground(Qt::lightGray);
  itemO1->setTextAlignment(Qt::AlignCenter);
  listView->addItem(itemO1);

  auto button = new QPushButton("Add Contact");
  connect(button, &QPushButton::released, this, &QTContacts::addContact);

  QBoxLayout::addWidget(listView);

  nameEdit = new QLineEdit();
  numberEdit = new QLineEdit();
  nameEdit->setPlaceholderText("Contact's Name");
  numberEdit->setPlaceholderText("999-999-999");

  auto hbox = new QHBoxLayout();
  hbox->setDirection(LeftToRight);
  hbox->addWidget(nameEdit);
  hbox->addWidget(numberEdit);
  hbox->addWidget(button);
  QBoxLayout::addItem(hbox);
}

QTContacts::~QTContacts() {
  delete listView;
  delete nameEdit;
}

void QTContacts::addContact() {
  const QString &name = nameEdit->text();
  const QString &number = numberEdit->text();
  if ((name.isNull() || name.isEmpty()) ||
      (number.isNull() || number.isEmpty()))
    return;

  auto nameStr = name.toStdString();
  auto numberStr = number.toStdString();
  std::cout << "Creating new Contact{ " << nameStr << ", " << numberStr << " }"
            << std::endl;

  bool res = service.createContact(nameStr, numberStr);
  if (!res) {
    std::cout << "Could not create contact." << std::endl;
    return;
  }

  addInnerContact(nameStr, numberStr);
}

void QTContacts::refresh() {
  listView->clear();
  auto vec = service.refreshReturn();
  for (auto &contact : vec) {
    addInnerContact(contact.name, contact.number);
  }
}

void QTContacts::addInnerContact(std::string &name, std::string number) {
  std::stringstream str;
  str << name << "{ " << number << " }";
  auto da = str.str();
  auto contact = Contacts::Contact{name, number};
  auto *message = new QTContactItem(da, contact);
  message->setBackground(QColor(0x96, 0x96, 0xFF));
  message->setTextAlignment(Qt::AlignLeft);
  listView->addItem(message);
}

void QTContacts::showUpdateDialog(QListWidgetItem *item) {
  auto realItem = (QTContactItem *)item;
  auto &contact = realItem->internalContact;
  auto shouldUpdate = showContactUpdateDialog(contact);
  if (shouldUpdate) {
    service.createContact(contact.name, newNumber);
    refresh();
  }
}

void QTContacts::showDeleteDialog(QListWidgetItem *item) {
  auto realItem = (QTContactItem *)item;
  auto &contact = realItem->internalContact;
  auto shouldDelete = showContactDeleteDialog(contact);
  if (shouldDelete) {
    service.removeContact(contact.name);
    refresh();
  }
}

bool QTContacts::showContactUpdateDialog(Contacts::Contact &contact) {
  QDialog dialog{};
  QFormLayout form(&dialog);

  std::stringstream ss;
  ss << "Change " << contact.name << "'s number:";
  form.addRow(new QLabel(QString::fromStdString(ss.str())));

  auto *newNumberField = new QLineEdit(&dialog);
  newNumberField->setText(QString::fromStdString(contact.number));
  form.addRow(newNumberField);

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  if (dialog.exec() == QDialog::Accepted) {
    if (newNumberField->text().isEmpty()) {
      return false;
    }

    newNumber = newNumberField->text().toStdString();

    return true;
  }

  return false;
}

bool QTContacts::showContactDeleteDialog(Contacts::Contact &contact) {
  QDialog dialog{};
  QFormLayout form(&dialog);

  std::stringstream ss;
  ss << "You sure you want to delete " << contact.name;
  form.addRow(new QLabel(QString::fromStdString(ss.str())));

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  return dialog.exec() == QDialog::Accepted;
}

void QTContacts::openDialogMenu(QListWidgetItem *item) {
  QDialog dialog{};
  QFormLayout form(&dialog);
  QDialogButtonBox buttonBox(Qt::Horizontal, &dialog);
  auto updateButton = QPushButton{"Update"};
  auto deleteButton = QPushButton{"Delete"};
  buttonBox.addButton(&updateButton, QDialogButtonBox::AcceptRole);
  buttonBox.addButton(&deleteButton, QDialogButtonBox::RejectRole);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  auto which = dialog.exec() == QDialog::Accepted;

  if (which) {
    showUpdateDialog(item);
  } else {
    showDeleteDialog(item);
  }
}
