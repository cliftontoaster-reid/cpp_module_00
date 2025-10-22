/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:40:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/22 13:22:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

#include "Contact.hpp"

class PhoneBook {
 public:
  static const int MAX_CONTACTS = 8;
  PhoneBook();
  void addContact(const Contact &contact);
  void removeContact(const std::string &name);
  const Contact *getContacts() const;
  int getContactCount() const { return contactCount; }

 private:
  Contact contacts[MAX_CONTACTS];
  int contactCount;
  int i;
};