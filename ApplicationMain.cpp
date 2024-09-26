#include "ApplicationMain.h"
#include "ContactsService.hpp"
#include "ui/QTContacts.hpp"
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QDir>
#include <QFormLayout>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <qicon.h>
#include <qsize.h>

#include <iostream>

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
  // setFixedSize(1200, 800);
  service = new Contacts::ContactsService{
      [this](std::string &v) { this->onStatusUpdate(v); }};

  setFixedSize(720, 480);
  setLayoutDirection(Qt::RightToLeft);
  auto scene = new QGraphicsScene{this};
  auto button = new QPushButton("Connect");

  // button->setFixedSize(QSize{100, 25});
  connect(button, &QPushButton::released, this,
          &ApplicationMain::handleConnection);

  connectionStatus = new QLabel("Disconnected");

  auto mainWidget = new QWidget();
  auto hbox = new QHBoxLayout();
  hbox->addWidget(button);
  auto refreshButton = new QPushButton("Refresh");
  connect(refreshButton, &QPushButton::released, this,
          &ApplicationMain::refresh);
  hbox->addWidget(refreshButton);

  pContacts = new Ui::QTContacts(*service);
  auto vbox = new QVBoxLayout();
  vbox->addWidget(connectionStatus);
  vbox->addItem(hbox);
  vbox->addItem(pContacts);

  auto mainHorizontalBox = new QHBoxLayout();
  mainHorizontalBox->addItem(vbox);

  mainWidget->setLayout(mainHorizontalBox);
  setCentralWidget(mainWidget);
}
void ApplicationMain::handleConnection() {
  auto ok2 = connectionDialog();
  if (ok2) {
    service->setName(clientName);
    auto connected = service->connect();
    if (connected) {
      pContacts->refresh();
    }
  }
}

bool ApplicationMain::connectionDialog() {
  QDialog dialog(this);
  QFormLayout form(&dialog);

  form.addRow(new QLabel("Your name:"));

  auto *distribuserField = new QLineEdit(&dialog);
  distribuserField->setText("Distribuser");
  form.addRow(distribuserField);

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  if (dialog.exec() == QDialog::Accepted) {
    if (distribuserField->text().isEmpty()) {
      return false;
    }

    clientName = distribuserField->text().toStdString();
    return true;
  }

  return false;
}

// void ApplicationMain::listen() {}

void ApplicationMain::onStatusUpdate(std::string &status) {
  connectionStatus->setText(QString::fromStdString(status));
}

void ApplicationMain::refresh() {
  pContacts->refresh();
}
