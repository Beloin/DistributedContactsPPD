#include "QTContacts.hpp"
#include <QAbstractButton>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <qlistwidget.h>
#include <sstream>

using namespace Ui;

QTContacts::QTContacts(Contacts::ContactsService &service) : service(service) {
  listView = new QListWidget();
  // TODO: Add double click to open a context window?
  // connect(listView, &QListWidget::itemClicked, this,
  //         &QTContacts::onContactClick);

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

  std::stringstream str;
  str << nameStr << "{ " << numberStr << " }";
  auto *message = new QListWidgetItem(QString::fromStdString(str.str()));
  message->setBackground(QColor(0x96, 0x96, 0xFF));
  message->setTextAlignment(Qt::AlignLeft);
  listView->addItem(message);
}
