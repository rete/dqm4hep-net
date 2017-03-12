  /// \file dqm4hep-send-request.cc
/*
 *
 * dqm4hep-send-request.cc source template automatically generated by a class generator
 * Creation date : sam. d�c. 3 2016
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#include "dqm4hep/Client.h"

#include "json/json.h"

using namespace dqm4hep::net;

class ServicePrinter
{
public:
  template <typename T>
  void print(const T &value);
};

template <typename T>
inline void ServicePrinter::print(const T &value)
{
  // Json::StyledWriter writer;
  // std::cout << writer.write(value) << std::endl;
  std::cout << value << std::endl;
}

template <>
inline void ServicePrinter::print(const Json::Value &value)
{
  Json::StyledWriter writer;
  std::cout << writer.write(value) << std::endl;
}

int main(int argc, char **argv)
{
  if(argc != 3)
  {
    std::cout << "Usage : dqm4hep-subscribe-service serviceType type name" << std::endl;
    return 1;
  }

  std::string serviceType(argv[1]);
  std::string name(argv[2]);

  ServicePrinter printer;
  Client client;

  if(serviceType == "int")
    client.subscribe<int>(name, &printer, &ServicePrinter::print<int>);
  else if(serviceType == "float")
    client.subscribe<float>(name, &printer, &ServicePrinter::print<float>);
  else if(serviceType == "double")
    client.subscribe<double>(name, &printer, &ServicePrinter::print<double>);
  else if(serviceType == "string")
    client.subscribe<std::string>(name, &printer, &ServicePrinter::print<std::string>);
  else if(serviceType == "json")
    client.subscribe<Json::Value>(name, &printer, &ServicePrinter::print<Json::Value>);

  while(1)
    sleep(1);

  return 0;
}
