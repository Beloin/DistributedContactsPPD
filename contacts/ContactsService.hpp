////////////////////////////////////////////////////////////////////////////////
// File:        ContactsService.hpp
// Author:      MyName
// Description:
////////////////////////////////////////////////////////////////////////////////
#ifndef CONTACTS_CONTACTSSERVICE_H
#define CONTACTS_CONTACTSSERVICE_H
////////////////////////////////////////////////////////////////////////////////

#include "Contact.hpp"
#include "client.h"
#include <functional>
#include <vector>
namespace Contacts {

//------------------------------------------------------------------------------
typedef std::function<void(std::string &)> OnStatusUpdate;

class ContactsService : private Network::Client {

public:
  ContactsService(OnStatusUpdate callback) : callback(callback){};
  ~ContactsService() = default;

  bool connect();

  bool removeContact(std::string &name);
  const bool createContact(std::string name, std::string number);

  bool refresh();
  std::vector<Contact> const &refreshReturn() {
    refresh();
    return getContactList();
  }
  std::vector<Contact> const &getContactList() { return internalContacts; }

  void setName(std::string &name_) { name = name_; }

private:
  OnStatusUpdate callback;

  std::string currentServer;
  std::string lastServer;

  std::vector<Contact> internalContacts;

  bool onceConnected{false};

  std::string name{"ClientName"};
};

//------------------------------------------------------------------------------

} // namespace Contacts
#endif /* CONTACTS_CONTACTSSERVICE_H */
