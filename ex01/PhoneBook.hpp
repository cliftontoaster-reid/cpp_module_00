/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:40:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/08/06 14:47:26 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Contact.hpp"
#include <string>

class PhoneBook
{
public:
  void addContact(const Contact &contact);
  void removeContact(const std::string &name);
  int searchContact(const std::string &name, Contact results[], int maxResults) const;
  const Contact *getContacts() const;

private:
  Contact contacts[8];
  int contactCount;
};