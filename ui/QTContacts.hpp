////////////////////////////////////////////////////////////////////////////////
// File:        contacts.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef UI_CONTACTS_H
#define UI_CONTACTS_H
////////////////////////////////////////////////////////////////////////////////

#include "ContactsService.hpp"
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>

namespace Ui {

//------------------------------------------------------------------------------

class QTContacts : public QVBoxLayout {

public:
  QTContacts(Contacts::ContactsService &service);
  ~QTContacts();

  QListWidget *listView;
  std::string contactName;

  void refresh();

private:
  QLineEdit *nameEdit;
  QLineEdit *numberEdit;

  std::string newNumber;

  Contacts::ContactsService &service;

  void addContact();

  void addInnerContact(std::string &name, std::string number);

  void openDialogMenu(QListWidgetItem *item);
  void showUpdateDialog(QListWidgetItem *item);
  void showDeleteDialog(QListWidgetItem *item);
  bool showContactUpdateDialog(Contacts::Contact &contact);
  bool showContactDeleteDialog(Contacts::Contact &contact);
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_CONTACTS_H */
