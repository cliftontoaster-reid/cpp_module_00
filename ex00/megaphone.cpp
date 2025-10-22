/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:42:19 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/22 13:22:36 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  if (argc < 2)
    std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
  else {
    for (int i = 1; i < argc; i++) {
      // create new string and convert to uppercase
      std::string upper_str;
      for (const char *c = argv[i]; *c; c++) {
        upper_str += std::toupper(*c);
      }
      std::cout << upper_str;
    }
    std::cout << std::endl;
  }
  return (0);
}
