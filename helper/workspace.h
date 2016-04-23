/*
 * workspace.h
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "We must construct additional GNU software"
 *
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

#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <vector>

#include "console_printer.h"
#include "interpreter/parser.h"
#include "../networks/fullhidden.h"

class Workspace
{
  friend class ConsolePrinter;
  friend class Parser;
public:

  void start();
  static Workspace& instance();
  ~Workspace();

private:
  bool hasStarted;
  double input_scale; // divide input by this
  double output_scale; // multiply output by this

  std::vector<FullHidden<double> *> networks;
  FullHidden<double> *current_network;

  Workspace();
  Workspace(Workspace const&);
  void operator=(Workspace const&);
  bool activate_network(int net_id);
  void execute(Parser& parser);
};

#endif // WORKSPACE_H
