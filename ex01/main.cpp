/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:16:06 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/22 15:24:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Contact.hpp"
#include "PhoneBook.hpp"

// Forever we listen to stdin and wait for commands
//
// Commands:
// - ADD: add a contact
// - SEARCH: search for a contact
// - EXIT: exit the program
//
// If the command is not recognized, we print an error message and continue
// listening
//
// If the user tries to add more than 8 contacts, we print an error message and
// continue listening
//
// If the user tries to search for a contact that does not exist, we print an
// error message and continue listening

/// @brief Safely reads a line from input stream, handling errors and EOF.
/// @param in The input stream to read from.
/// @param str The string to store the read line.
inline void safeReadLine(std::istream &in, std::string &str) {
  if (!in.good()) {
    std::cerr << RED << "Cannot read from input, exiting program." << RESET
              << std::endl;
    std::exit(1);
  }

  std::getline(in, str);

  if (in.eof()) {
    std::cerr << CYAN << "An EOF has been reached, exiting program." << RESET
              << std::endl;
    std::exit(0);
  }
}

/// @brief Reads input with retries, ensuring it's not empty, and provides a
/// default if soft-locked.
/// @param in The input stream.
/// @param str The string to store input.
/// @param thing Description of what to enter.
/// @param def Default value if retries fail.
/// @param validator Optional validation function for input.
/// @return True if input was read successfully, false otherwise.
inline bool readThing(std::istream &in, std::string &str, const char *thing,
                      const char *def, bool (*validator)(const std::string &)) {
  int i = 5;
  std::string buffer;
  while (i >= 0) {
    std::cerr << BOLD << "Enter " << thing << ": " << RESET;
    safeReadLine(in, buffer);

    if (!buffer.empty()) {
      if (validator == NULL || validator(buffer)) {
        str.assign(buffer);
        return true;
      }

      std::cerr << YELLOW << "Invalid value for thing '" << thing
                << "', please try again, " << --i << " attempts remaining"
                << RESET << std::endl;
      continue;
    }

    std::cerr << YELLOW << "Thing '" << thing
              << "' cannot be empty, please try again, " << --i
              << " attempts remaining" << RESET << std::endl;
  }

  std::cerr << BOLD << RED << "Soft lock detected, returning default value."
            << RESET << std::endl;
  str = def;
  return false;
}

/// @brief Handles adding a new contact to the phonebook with input validation.
/// @param phonebook The phonebook to add the contact to.
void commandAdd(PhoneBook &phonebook) {
  Contact contact;
  std::string name, firstName, nickname, phoneNumber, darkestSecret;

  readThing(std::cin, name, "last name", "Doe", NULL);
  contact.setName(name);

  readThing(std::cin, firstName, "first name", "Jane", NULL);
  contact.setFirstName(firstName);

  readThing(std::cin, nickname, "nickname", "Unknown", NULL);
  contact.setNickname(nickname);

  readThing(std::cin, phoneNumber, "phone number", "0000000000",
            Contact::isValidPhoneNumber);
  contact.setPhoneNumber(phoneNumber);

  readThing(std::cin, darkestSecret, "darkest secret", "None", NULL);
  contact.setDarkestSecret(darkestSecret);

  phonebook.addContact(contact);
  std::cout << GREEN << "Contact added successfully." << RESET << std::endl;
}

/// @brief Converts a string to an integer, throwing on invalid format.
/// @param str The string to convert.
/// @return The integer value.
int strToInt(const std::string &str) {
  // manually convert string to int
  int result = 0;
  for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
    if (*it < '0' || *it > '9')
      throw std::invalid_argument("Invalid number format");
    result = result * 10 + (*it - '0');
  }
  return result;
}

/// @brief Validates if the input string is a valid index for the phonebook.
/// @param phonebook The phonebook to check against.
/// @param str The input string.
/// @return True if valid, false otherwise.
static bool isValidIndex(const PhoneBook &phonebook, const std::string &str) {
  try {
    int index = strToInt(str);
    return index >= 1 && index <= phonebook.getContactCount();
  } catch (const std::invalid_argument &) {
    return false;
  }
}

/// @brief Displays contacts and allows viewing details of a selected contact.
/// @param phonebook The phonebook to search in.
void commandSearch(const PhoneBook &phonebook) {
  const Contact *contacts = phonebook.getContacts();

  if (phonebook.getContactCount() == 0) {
    std::cerr << YELLOW << "No contacts available to display." << RESET
              << std::endl;
    return;
  }

  std::cout << BOLD << CYAN
            << "╔══════════════════════════════════════════════════════╗\n"
            << "║                     Contact List                     ║\n"
            << "╠════╦════════════════╦════════════════╦═══════════════╣\n"
            << "║ " << WHITE << "No" << RESET << BOLD << CYAN << " ║ " << CYAN
            << "Last Name" << RESET << BOLD << CYAN << "      ║ " << YELLOW
            << "First Name" << RESET << BOLD << CYAN << "     ║ " << MAGENTA
            << "Nickname" << RESET << BOLD << CYAN << "      ║\n"
            << "╠════╬════════════════╬════════════════╬═══════════════╣\n"
            << RESET;

  for (int i = 0; i < phonebook.getContactCount(); i++) {
    contacts[i].displayContact(i + 1);
  }

  std::cout << BOLD << CYAN
            << "╚════╩════════════════╩════════════════╩═══════════════╝\n"
            << RESET;

  std::string input;
  std::cout << "Enter index to view details: ";
  safeReadLine(std::cin, input);

  if (isValidIndex(phonebook, input)) {
    int index = strToInt(input) - 1;
    contacts[index].displayFullContact();
  } else {
    std::cerr << RED << "Invalid index." << RESET << std::endl;
  }
}

/// @brief Main entry point: runs the phonebook application loop.
/// @return Exit status.
int main(void) {
  PhoneBook *phonebook = new PhoneBook();

  std::string command;

  while (true) {
    std::cout << BOLD << "Enter command (ADD, SEARCH, EXIT): " << RESET;
    safeReadLine(std::cin, command);
    while (command.empty()) {
      // If stdout is a terminal, remove the blank line produced by the
      // user pressing Enter with no input. We move the cursor up one line
      // and clear the entire line. If not a TTY (redirected/piped), don't
      // emit escape sequences.
      if (isatty(STDOUT_FILENO)) {
        // Move cursor up 1 line and clear the line
        std::cout << "\033[1A\033[2K" << std::flush;
      }

      // Re-prompt until we get a non-empty command
      std::cout << BOLD << "Enter command (ADD, SEARCH, EXIT): " << RESET;
      safeReadLine(std::cin, command);
    }

    // We sanitize the command to uppercase and remove leading/trailing spaces
    // as well as anything after the first space
    for (std::string::const_iterator it = command.begin(); it != command.end();
         ++it) {
      command[it - command.begin()] = std::toupper(*it);
    }
    command.erase(0, command.find_first_not_of(' '));
    for (size_t pos = command.find(' '); pos != std::string::npos;
         pos = command.find(' ')) {
      command.erase(pos);
    }

    if (command == "ADD") {
      commandAdd(*phonebook);
    } else if (command == "SEARCH") {
      commandSearch(*phonebook);
    } else if (command == "EXIT") {
      std::cout << CYAN << "Exiting program." << RESET << std::endl;
      delete phonebook;
      return 0;
    } else {
      std::cerr << RED << "Unknown command: " << command << RESET << std::endl;
    }
  }

  delete phonebook;
  return 0;
}
