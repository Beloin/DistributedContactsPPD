#include "ContactsService.hpp"
#include "Contact.hpp"
#include "converters.h"
#include "know_servers.h"
#include <cstdint>
#include <iostream>
#include <sstream>

using namespace Contacts;

bool ContactsService::connect() {
  if (onceConnected) {
    disconnect();
    std::stringstream strstream;
    strstream << "Lost connection to " << lastServer;
    auto status = strstream.str();
    callback(status);
  }

  bool connected{false};
  for (auto &server : knowServers) {
    auto f = server.find(":");
    auto host = server.substr(0, f);
    auto port = server.substr(f + 1);
    int r = ConnectTo(host, port);

    if (r) {
      std::cout << "Could not connect to " << host << std::endl;
      continue;
    } else {
      std::stringstream strstream;
      strstream << "Connected to " << host;
      auto status = strstream.str();
      std::cout << status << std::endl;
      callback(status);
      if (lastServer == "")
        lastServer = host;
      else
        lastServer = currentServer;

      currentServer = host;

      onceConnected = true;
      connected = true;

      // Initial connection setup
      char buffer[256];
      buffer[0] = 2;
      int wrote = internalSendBytes(buffer, 1);
      if (wrote == 0) {
        std::cout << "Disconnected from " << currentServer << std::endl;
        return false;
      }
      createPaddedString(buffer, name);

      wrote = internalSendBytes(buffer, 256);
      if (wrote == 0) {
        std::cout << "Disconnected from " << currentServer << std::endl;
        return false;
      }

      break;
    }
  }

  return connected;
}

#define loss_retry(name, number)                                               \
  if (wrote == 0) {                                                            \
    std::cout << "Lost connection to " << currentServer << std::endl;          \
    bool ta = connect();                                                       \
    if (ta) {                                                                  \
      return createContact(name, number);                                      \
    } else {                                                                   \
      return false;                                                            \
    }                                                                          \
  }

const bool ContactsService::createContact(std::string name,
                                          std::string number) {
  char buffer[256];
  buffer[0] = 1;
  int wrote = internalSendBytes(buffer, 1);
  loss_retry(name, number);
  // if (read == 0) {
  //   std::cout << "Lost connection to " << currentServer << std::endl;
  //   bool ta = connect();
  //   if (ta) {
  //     return createContact(name, number);
  //   } else {
  //     return false;
  //   }
  // }

  createPaddedString(buffer, name);
  wrote = internalSendBytes(buffer, 256);
  if (wrote == 0) {
    std::cout << "Lost connection to " << currentServer << std::endl;
    bool ta = connect();
    if (ta) {
      return createContact(name, number);
    } else {
      return false;
    }
  }

  createPaddedString(buffer, number, 20);
  wrote = internalSendBytes(buffer, 20);
  if (wrote == 0) {
    std::cout << "Lost connection to " << currentServer << std::endl;
    bool ta = connect();
    if (ta) {
      return createContact(name, number);
    } else {
      return false;
    }
  }

  return true;
}

bool ContactsService::refresh() {
  if (!IsConnected()) {
    return false;
  }

  char buffer[256];
  buffer[0] = 3;
  int wrote = internalSendBytes(buffer, 1);
  if (wrote == 0) {
    std::cout << "Lost connection to " << currentServer << std::endl;
    connect();
    return false;
  }

  int read = internalReadBytes((unsigned char *)buffer, 4);
  if (read == 0) {
    std::cout << "Lost connection to " << currentServer << std::endl;
    connect();
    return false;
  }
  uint32_t v = convert4(buffer);
  internalContacts.resize(v);
  if (v == 0)
    return true;

  for (size_t i = 0; i < v; i++) {
    read = internalReadBytes((unsigned char *)buffer, 256);
    if (read == 0) {
      std::cout << "Lost connection to " << currentServer << std::endl;
      connect();
      return false;
    }
    std::string name = parseNullTerminatedString(buffer);

    read = internalReadBytes((unsigned char *)buffer, 20);
    if (read == 0) {
      std::cout << "Lost connection to " << currentServer << std::endl;
      connect();
      return false;
    }
    std::string number = parseNullTerminatedString(buffer);

    internalContacts[i] = Contact{name, number};
  }

  return true;
}

bool ContactsService::removeContact(std::string &name) {
  char buffer[256];
  buffer[0] = 2;
  int wrote = internalSendBytes(buffer, 1);
  if (wrote == 0) {
    std::cout << "Lost connection to " << currentServer << std::endl;
    connect();
    return false;
  }

  createPaddedString(buffer, name);
  wrote = internalSendBytes(buffer, 256);
  if (wrote == 0) {
    std::cout << "Lost connection to " << currentServer << std::endl;
    connect();

    return false;
  }

  return true;
}
