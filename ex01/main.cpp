/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:16:06 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/01 15:49:37 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>

// Forever we listen to stdin and wait for commands
//
// Commands:
// - ADD: add a contact
// - SEARCH: search for a contact
// - EXIT: exit the program
//
// If the command is not recognized, we print an error message and continue listening
//
// If the user tries to add more than 8 contacts, we print an error message and continue listening
//
// If the user tries to search for a contact that does not exist, we print an error message and continue listening

void commandAdd(PhoneBook &phonebook)
{
  Contact contact;
  std::string name, firstName, nickname, phoneNumber, darkestSecret;
  std::cout << BOLD << "Enter name: " << RESET;
  std::getline(std::cin, name);
  contact.setName(name);

  std::cout << BOLD << "Enter first name: " << RESET;
  std::getline(std::cin, firstName);
  contact.setFirstName(firstName);
  std::cout << BOLD << "Enter nickname: " << RESET;
  std::getline(std::cin, nickname);
  contact.setNickname(nickname);
  while (true)
  {
    std::cout << BOLD << "Enter phone number: " << RESET;
    std::getline(std::cin, phoneNumber);
    try
    {
      contact.setPhoneNumber(phoneNumber);
      break;
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << RED << e.what() << RESET << std::endl;
    }
  }
  std::cout << BOLD << "Enter darkest secret: " << RESET;
  std::getline(std::cin, darkestSecret);
  contact.setDarkestSecret(darkestSecret);

  try
  {
    phonebook.addContact(contact);
    std::cout << GREEN << "Contact added successfully." << RESET << std::endl;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << RED << e.what() << RESET << std::endl;
  }
}

int strToInt(const std::string &str)
{
  // manually convert string to int
  int result = 0;
  for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
  {
    if (*it < '0' || *it > '9')
      throw std::invalid_argument("Invalid number format");
    result = result * 10 + (*it - '0');
  }
  return result;
}

void commandSearch(const PhoneBook &phonebook)
{
  const Contact *contacts = phonebook.getContacts();

  int count = 0;
  for (int i = 0; i < PhoneBook::MAX_CONTACTS; i++)
  {
    const Contact &contact = contacts[i];
    if (!contact.isEmpty())
    {
      std::cout << "  " << UNDERLINE << ++count << RESET;
      contact.displayContact();
    }
  }

  // We then ask for which ID the user wants to see the details of the contact, if out of range we print an error message
  std::string input;
  std::cout << BOLD << "Enter contact ID to view details (1-" << count << "): " << RESET;
  std::getline(std::cin, input);

  if (input.empty() || !std::isdigit(input[0]))
  {
    std::cerr << RED << "Invalid ID." << RESET << std::endl;
    return;
  }

  int id = strToInt(input) - 1; // Convert to zero-based index
  if (id < 0 || id >= PhoneBook::MAX_CONTACTS || contacts[id].isEmpty())
  {
    std::cerr << RED << "Contact not found." << RESET << std::endl;
    return;
  }

  contacts[id].displayFullContact();
}

int main(void)
{
  PhoneBook *phonebook = new PhoneBook();

  std::string command;

  while (true)
  {
    std::cout << BOLD << "Enter command (ADD, SEARCH, EXIT): " << RESET;
    std::getline(std::cin, command);

    // We sanetize the command to uppercase and remove leading/trailing spaces as well as anything after the first space
    for (std::string::const_iterator it = command.begin(); it != command.end(); ++it)
    {
      command[it - command.begin()] = std::toupper(*it);
    }
    command.erase(0, command.find_first_not_of(' '));
    for (size_t pos = command.find(' '); pos != std::string::npos; pos = command.find(' '))
    {
      command.erase(pos);
    }

    if (command == "ADD")
    {
      commandAdd(*phonebook);
    }
    else if (command == "SEARCH")
    {
      commandSearch(*phonebook);
    }
    else if (command == "EXIT")
    {
      std::cout << CYAN << "Exiting program." << RESET << std::endl;
      delete phonebook;
      return 0;
    }
    else
    {
      std::cerr << RED << "Unknown command: " << command << RESET << std::endl;
    }
  }

  delete phonebook;
  return 0;
}
