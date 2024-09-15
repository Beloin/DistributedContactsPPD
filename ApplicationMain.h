
//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H

#include "chat/ServerConnection.hpp"
#include "ui/QTChat.hpp"
#include "ui/QTContacts.hpp"
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <thread>

class ApplicationMain : public QMainWindow {

private:
  bool connectionDialog();
  Ui::QTChat *pChat;
  Ui::QTContacts *pContacts;
  Chat::ServerConnection _serverCon{};

  std::string serverAddress;
  std::thread clientListen;

public:
  explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

  void OnMessage(std::string message);
  void handle();
  void listen();
};

#endif // TEST_QT5_APPLICATIONMAIN_H
