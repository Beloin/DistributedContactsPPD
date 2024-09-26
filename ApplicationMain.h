
//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H

#include "contacts/ContactsService.hpp"
#include "ui/QTContacts.hpp"
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <thread>

class ApplicationMain : public QMainWindow {

private:
  Ui::QTContacts *pContacts;
  Contacts::ContactsService service;
  QLabel *connectionStatus;

  std::string clientName{"Username"};

  std::string serverAddress;
  std::thread clientListen;

public:
  explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

  void handleConnection();
};

#endif // TEST_QT5_APPLICATIONMAIN_H
