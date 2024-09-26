////////////////////////////////////////////////////////////////////////////////
// File:        QTContactItem.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef UI_QTCONTACTITEM_H
#define UI_QTCONTACTITEM_H
////////////////////////////////////////////////////////////////////////////////

#include "Contact.hpp"
#include <QListWidgetItem>
#include <qlistwidget.h>

namespace Ui {

//------------------------------------------------------------------------------

class QTContactItem : public QListWidgetItem {

public:
  QTContactItem(std::string &str, Contacts::Contact &contact)
      : QListWidgetItem(QString::fromStdString(str)), internalContact(contact) {
  }

  Contacts::Contact internalContact;
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_QTCONTACTITEM_H */
