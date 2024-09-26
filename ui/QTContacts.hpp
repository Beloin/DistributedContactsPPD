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

  Contacts::ContactsService &service;

  void addContact();

  void addInnerContact(std::string &name, std::string number);

  void onContactClick(QListWidgetItem *item);
  bool showContactDialog(Contacts::Contact &contact);
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_CONTACTS_H */
