#include "ApplicationMain.h"
#include "network/know_servers.h"
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

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
  // setFixedSize(1200, 800);
  setFixedSize(720, 480);
  setLayoutDirection(Qt::RightToLeft);
  auto scene = new QGraphicsScene{this};
  auto button = new QPushButton("Connect");

  auto refreshButton = new QPushButton("Refresh");
  // button->setFixedSize(QSize{100, 25});
  connect(button, &QPushButton::released, this,
          &ApplicationMain::handleConnection);

  connectionStatus = new QLabel("Disconnected");

  auto mainWidget = new QWidget();
  auto hbox = new QHBoxLayout();
  hbox->addWidget(button);

  // Only show after connection
  // hbox->addWidget(refreshButton);

  pContacts = new Ui::QTContacts(service);
  auto vbox = new QVBoxLayout();
  vbox->addItem(hbox);
  vbox->addItem(pContacts);

  auto mainHorizontalBox = new QHBoxLayout();
  mainHorizontalBox->addItem(vbox);

  mainWidget->setLayout(mainHorizontalBox);
  setCentralWidget(mainWidget);
}
void ApplicationMain::handleConnection() {
  // TODO: Auto connect to the list of know servers...
  service.connect();
}

