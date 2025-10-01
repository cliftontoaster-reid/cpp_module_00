/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:40:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/01 15:51:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Contact.hpp"
#include <string>

class PhoneBook
{
public:
  static const int MAX_CONTACTS = 8;
  PhoneBook();
  void addContact(const Contact &contact);
  void removeContact(const std::string &name);
  int searchContact(const std::string &name, Contact results[], int maxResults) const;
  const Contact *getContacts() const;

private:
  Contact contacts[MAX_CONTACTS];
  int contactCount;
};