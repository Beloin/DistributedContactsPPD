#include "ApplicationMain.h"
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Hello World" << std::endl;
  QApplication a(argc, argv);

  // TODO: Get chat from other software
  ApplicationMain applicationMain;
  applicationMain.show();

  return QApplication::exec();
}
