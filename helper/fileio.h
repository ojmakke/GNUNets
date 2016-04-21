/*
 * fileio.hpp
 *
 *  Created on : Mar 28, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "The the programming tool ever is coffee"
 *      Email  : ojmakke@yahoo.com

This file is part of GNU Nets also known as GNUNets

GNU Nets is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

GNU Nets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with GNU Nets.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FILEIO_H_
#define FILEIO_H_

#include <fstream>
#include <iostream>
#include <string.h>

#include "../helper/console_printer.h"

#define DELIMITER ','

namespace FileIO
{
  unsigned int char_count(std::string string, char c)
  {
    unsigned int counter = 0;
    for(size_t ii = 0; ii < string.length(); ii++)
      {
        if(string.at(ii) == c)
          {
            counter++;
          }
      }
    return counter;
  }

  // This also modifies the string and returns the rest
  std::string get_first_entry(std::string *str, char d)
  {
    // Get the string from the beginning until delimiter, not including it.
    std::string dstr = "";
    dstr.push_back(d);
    std::string substr = str->substr(0, str->find(dstr));
    *str = str->substr(str->find(dstr)+1, str->length());
    return substr;
  }

  // Returns 0 if fails. Otherwise, returns lines read
//  template<typename T>
  int get_text_1D(std::string filename,
                             unsigned int dimension,
                             double*** you_own_data)
  {
    double **data;
    std::string line_read;
    std::ifstream infile(filename);
    if(!infile.is_open())
      {
        ConsolePrinter::instance().feedback_rewrite(
              "Cannot open file               ");
        return 0; // error
      }
    unsigned int line_count = 0;
    // Verification loop
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,line_read); // Saves the line in STRING.
        if(line_read.compare("") == 0)
          {
            continue;
          }
        else if(line_read.at(0) == '#')
          {
            continue;
          }
        else if(char_count(line_read, ',') != dimension - 1)
          {
            ConsolePrinter::instance().feedback_rewrite(
                  "Incorrect dimension              ");
            return 0;
          }
        line_count++;
    }

    data = new double*[line_count];

    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    line_count = 0;
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,line_read);
        if(line_read.compare("") == 0)
          {
            continue;
          }
        else if(line_read.at(0) == '#')
          {
            continue;
          }
        // Parse the line into the input
        data[line_count] = new double[dimension];
        std::string entry = line_read;
        for(size_t ii = 0; ii < dimension; ii++)
        {
          entry = get_first_entry(&line_read, DELIMITER);
          data[line_count][ii] = atof(entry.c_str());
        }
        line_count++;
    }
    infile.close();
  //  system ("pause");
    *you_own_data = data;

    return line_count;
  }
}

#endif /* FILEIO_H_ */

