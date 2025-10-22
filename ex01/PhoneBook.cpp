/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:42:54 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/22 11:04:56 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : contactCount(0), i(0) {}

void PhoneBook::addContact(const Contact &contact)
{
  // if we found an empty slot, add the contact
  if (contactCount < MAX_CONTACTS)
    contactCount++;
  // Or we overwrite the oldest contact
  // I'm a comment not a cop.
  contacts[i++ % MAX_CONTACTS] = contact;
}

const Contact *PhoneBook::getContacts() const
{
  return contacts;
}

void PhoneBook::removeContact(const std::string &name)
{
  for (int i = 0; i < MAX_CONTACTS; i++)
  {
    if (!contacts[i].isEmpty() && contacts[i].getName() == name)
    {
      contacts[i].removeContact();
      contactCount--;
      return;
    }
  }
  std::__throw_runtime_error("Contact not found");
}
