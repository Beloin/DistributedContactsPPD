
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
#include <qlayout.h>

class ApplicationMain : public QMainWindow {

private:
  Ui::QTContacts *pContacts;
  // TODO: Add callback to
  Contacts::ContactsService *service;

  std::string clientName{"Username"};

  QLabel *connectionStatus;

  bool connectionDialog();

public:
  explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

  void handleConnection();
  void refresh();
  void onStatusUpdate(std::string &status);
  // void listen();
};

#endif // TEST_QT5_APPLICATIONMAIN_H
