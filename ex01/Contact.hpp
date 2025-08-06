/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:42:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/08/06 15:02:30 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

class Contact
{
public:
  Contact();
  ~Contact();

  void setName(const std::string &name);
  void setFirstName(const std::string &firstName);
  void setNickname(const std::string &nickname);
  void setPhoneNumber(const std::string &phoneNumber);
  void setDarkestSecret(const std::string &darkestSecret);

  std::string getName() const;
  std::string getFirstName() const;
  std::string getFullName() const;
  std::string getNickname() const;
  std::string getPhoneNumber() const;
  std::string getDarkestSecret() const;

  void displayContact() const;
  void displayFullContact() const;
  void removeContact();
  bool isEmpty() const;

private:
  std::string name;
  std::string firstName;
  std::string nickname;
  std::string phoneNumber;
  std::string darkestSecret;

  bool empty;
};