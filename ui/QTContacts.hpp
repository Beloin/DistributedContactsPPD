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

private:
  QLineEdit *nameEdit;
  QLineEdit *numberEdit;

  Contacts::ContactsService &service;

  void addContact();
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_CONTACTS_H */
