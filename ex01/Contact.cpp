/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:48:25 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/22 13:22:27 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

#include <cctype>
#include <iomanip>
#include <iostream>

Contact::Contact() : empty(true) {}

Contact::~Contact() {}

void Contact::setName(const std::string &name) {
  this->name = name;
  empty = false;
}

void Contact::setFirstName(const std::string &firstName) {
  this->firstName = firstName;
  empty = false;
}

void Contact::setNickname(const std::string &nickname) {
  this->nickname = nickname;
  empty = false;
}

bool Contact::isValidPhoneNumber(const std::string &phoneNumber) {
  if (phoneNumber.empty()) return false;

  std::string cleaned = phoneNumber;

  // Remove common separators and whitespace
  std::string::size_type pos = 0;
  while ((pos = cleaned.find_first_of(" ()-.", pos)) != std::string::npos) {
    cleaned.erase(pos, 1);
  }

  // Check if it starts with + for international format
  bool hasCountryCode = false;
  if (!cleaned.empty() && cleaned[0] == '+') {
    hasCountryCode = true;
    cleaned = cleaned.substr(1);  // Remove the +
  }

  // Check if all remaining characters are digits
  for (std::string::const_iterator it = cleaned.begin(); it != cleaned.end();
       ++it) {
    if (!std::isdigit(*it)) return false;
  }

  // Validate length based on format
  if (hasCountryCode) {
    // International format: typically 7-15 digits after country code
    return cleaned.length() >= 7 && cleaned.length() <= 15;
  } else {
    // US: 10 digits (with area code), 7 digits (local)
    // Most countries: 7-11 digits
    return cleaned.length() >= 7 && cleaned.length() <= 11;
  }
}

void Contact::setPhoneNumber(const std::string &phoneNumber) {
  this->phoneNumber = phoneNumber;
  empty = false;
}

void Contact::setDarkestSecret(const std::string &darkestSecret) {
  this->darkestSecret = darkestSecret;
  empty = false;
}

void Contact::removeContact() {
  name.clear();
  firstName.clear();
  nickname.clear();
  phoneNumber.clear();
  darkestSecret.clear();
  empty = true;
}

bool Contact::isEmpty() const { return empty; }

static std::string formatField(const std::string &str) {
  if (str.length() > 10) return str.substr(0, 9) + '.';
  return std::string(10 - str.length(), ' ') + str;
}

static void printFieldWithOverflow(const std::string &label,
                                   const std::string &value,
                                   const std::string &labelColor) {
  const size_t maxFieldWidth = 32;
  const size_t labelWidth = 47;

  // Print the first line with the label
  std::cout << BOLD << CYAN << "║ " << labelColor << label;

  if (value.length() <= maxFieldWidth) {
    // Value fits on one line
    std::cout << RESET << value
              << std::string(maxFieldWidth - value.length(), ' ') << BOLD
              << CYAN << " ║\n"
              << RESET;
  } else {
    // Value needs to overflow to next lines
    size_t pos = 0;
    bool firstLine = true;

    while (pos < value.length()) {
      size_t chunkSize = labelWidth;
      if (firstLine) {
        chunkSize = maxFieldWidth;
      }

      std::string chunk = value.substr(pos, chunkSize);

      if (firstLine) {
        std::cout << RESET << chunk
                  << std::string(maxFieldWidth - chunk.length(), ' ') << BOLD
                  << CYAN << " ║\n"
                  << RESET;
        firstLine = false;
      } else {
        // Continuation line with indentation
        std::cout << BOLD << CYAN << "║ " << RESET << " "
                  << chunk  // One space for indentation
                  << std::string(labelWidth - chunk.length(), ' ') << BOLD
                  << CYAN << " ║\n"
                  << RESET;
      }

      pos += chunkSize;
    }
  }
}

void Contact::displayContact(int index) const {
  if (empty) {
    return;
  }

  std::cout << BOLD << CYAN << "║ " << RESET << WHITE << std::setw(2) << index
            << RESET << BOLD << CYAN << " ║ " << RESET << CYAN << "    "
            << formatField(name) << RESET << BOLD << CYAN << " ║ " << RESET
            << YELLOW << "    " << formatField(firstName) << RESET << BOLD
            << CYAN << " ║ " << RESET << MAGENTA << "   "
            << formatField(nickname) << RESET << BOLD << CYAN << " ║" << RESET
            << std::endl;
}

void Contact::displayFullContact() const {
  if (empty) return;

  // Top border
  std::cout << BOLD << CYAN
            << "╔══════════════════════════════════════════════════╗" << RESET
            << "\n";

  // Title
  std::cout << BOLD << CYAN << "║ " << RESET << BOLD << WHITE << UNDERLINE
            << "Contact Details" << RESET << BOLD << WHITE
            << std::string(48 - 15, ' ') << BOLD << CYAN << " ║" << "\n"
            << RESET;

  // Separator
  std::cout << BOLD << CYAN
            << "╠══════════════════════════════════════════════════╣" << RESET
            << "\n";

  // Fields with overflow support
  printFieldWithOverflow("Name:           ", name, BOLD BLUE);
  printFieldWithOverflow("First Name:     ", firstName, BOLD GREEN);
  printFieldWithOverflow("Nickname:       ", nickname, BOLD MAGENTA);
  printFieldWithOverflow("Phone Number:   ", phoneNumber, BOLD YELLOW);
  printFieldWithOverflow("Darkest Secret: ", darkestSecret, BOLD RED);

  // Bottom border
  std::cout << BOLD << CYAN
            << "╚══════════════════════════════════════════════════╝" << RESET
            << "\n";
}

std::string Contact::getName() const { return name; }

std::string Contact::getFirstName() const { return firstName; }

std::string Contact::getFullName() const { return name + " " + firstName; }

std::string Contact::getNickname() const { return nickname; }

std::string Contact::getPhoneNumber() const { return phoneNumber; }

std::string Contact::getDarkestSecret() const { return darkestSecret; }
