
//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H

#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <thread>

class ApplicationMain : public QMainWindow {

private:
  bool connectionDialog();

  std::string serverAddress;
  std::thread clientListen;

public:
  explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

  void handleConnection();
  void listen();
};

#endif // TEST_QT5_APPLICATIONMAIN_H
