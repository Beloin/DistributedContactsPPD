#include "ApplicationMain.h"
#include "network/know_servers.h"
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

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
  // setFixedSize(1200, 800);
  setFixedSize(720, 480);
  setLayoutDirection(Qt::RightToLeft);
  auto scene = new QGraphicsScene{this};
  auto button = new QPushButton("Connect");
  connect(button, &QPushButton::released, this, &ApplicationMain::handleConnection);

  auto mainWidget = new QWidget();
  auto hbox = new QHBoxLayout();
  hbox->addWidget(button);

  auto vbox = new QVBoxLayout();
  vbox->addItem(hbox);

  auto mainHorizontalBox = new QHBoxLayout();
  mainHorizontalBox->addItem(vbox);

  mainWidget->setLayout(mainHorizontalBox);
  setCentralWidget(mainWidget);
}
void ApplicationMain::handleConnection() {
  // TODO: Auto connect to the list of know servers...
  auto ok2 = connectionDialog();
  if (ok2) {
  }
}

bool ApplicationMain::connectionDialog() {
  QDialog dialog(this);
  QFormLayout form(&dialog);

  form.addRow(new QLabel("End. do Servidor:"));

  auto *serverAddressField = new QLineEdit(&dialog);
  serverAddressField->setText("localhost");
  form.addRow(serverAddressField);

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  knowServers;
  if (dialog.exec() == QDialog::Accepted) {
    if (serverAddressField->text().isEmpty()) {
      return false;
    }

    serverAddress = serverAddressField->text().toStdString();
    return true;
  }

  return false;
}

void ApplicationMain::listen()
{

}

