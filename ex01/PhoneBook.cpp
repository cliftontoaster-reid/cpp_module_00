/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:42:54 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/08/06 14:47:06 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void PhoneBook::addContact(const Contact &contact)
{
  int i = 0;
  // start at index and loop until we find an empty slot
  while (i < 8 && !contacts[i].isEmpty())
    i++;
  // if we found an empty slot, add the contact
  if (i < 8)
  {
    contacts[i] = contact;
    contactCount++;
    return;
  }
  std::__throw_runtime_error("PhoneBook is full");
}

const Contact *PhoneBook::getContacts() const
{
  return contacts;
}

void PhoneBook::removeContact(const std::string &name)
{
  for (int i = 0; i < 8; i++)
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

int stringLevenshtein(const std::string &s1, const std::string &s2)
{
  int len1 = s1.length();
  int len2 = s2.length();

  // Handle edge cases
  if (len1 == 0)
    return len2;
  if (len2 == 0)
    return len1;

  // Use a fixed-size array with reasonable maximum (assuming names won't exceed 1000 chars)
  const int MAX_LEN = 1000;
  if (len2 >= MAX_LEN)
    return len1 + len2; // If string is too long, return a large distance

  int distances[2][MAX_LEN];

  // Initialize first row
  for (int j = 0; j <= len2; j++)
    distances[0][j] = j;

  // Fill the matrix
  for (int i = 1; i <= len1; i++)
  {
    int curr = i % 2;
    int prev = 1 - curr;

    distances[curr][0] = i;

    for (int j = 1; j <= len2; j++)
    {
      int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

      int deletion = distances[prev][j] + 1;
      int insertion = distances[curr][j - 1] + 1;
      int substitution = distances[prev][j - 1] + cost;

      distances[curr][j] = std::min(deletion, std::min(insertion, substitution));
    }
  }

  return distances[len1 % 2][len2];
}

/// We first search for exact matches (of their lower case values) and then similar ones for each of these cases
///
/// - first name
/// - last name
/// - full name
bool isMatching(const Contact &contact, const std::string &search)
{
  std::string contactFirstNameLower = contact.getFirstName();
  std::string contactLastNameLower = contact.getName();

  for (size_t j = 0; j < contactFirstNameLower.length(); j++)
    contactFirstNameLower[j] = std::tolower(contactFirstNameLower[j]);
  for (size_t j = 0; j < contactLastNameLower.length(); j++)
    contactLastNameLower[j] = std::tolower(contactLastNameLower[j]);

  std::string contactFullNameLower = contactFirstNameLower + " " + contactLastNameLower;

  std::string searchNameLower = search;
  for (size_t j = 0; j < searchNameLower.length(); j++)
    searchNameLower[j] = std::tolower(searchNameLower[j]);

  if (contactFirstNameLower == search)
    return true;
  if (contactLastNameLower == search)
    return true;
  if (contactFullNameLower == search)
    return true;

  // If we reach here, we check for similarity using Levenshtein distance
  if (stringLevenshtein(contactFirstNameLower, searchNameLower) <= 2 ||
      stringLevenshtein(contactLastNameLower, searchNameLower) <= 2 ||
      stringLevenshtein(contactFullNameLower, searchNameLower) <= 2)
  {
    return true;
  }

  return false;
}

int PhoneBook::searchContact(const std::string &name, Contact results[], int maxResults) const
{
  int count = 0;
  for (int i = 0; i < 8 && count < maxResults; i++)
  {
    if (!contacts[i].isEmpty() && isMatching(contacts[i], name))
    {
      results[count] = contacts[i];
      count++;
    }
  }

  return count; // Return the number of matches found
}