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

using namespace dqm4hep::net;
using namespace dqm4hep::core;

class ServicePrinter {
public:
  ServicePrinter(const std::string &name, const std::string &printMethod)
      : m_serviceName(name), m_printMethod(printMethod) {
  }
  void print(const Buffer &buffer);
  template <typename T>
  void printT(const Buffer &buffer);

private:
  std::string m_serviceName;
  std::string m_printMethod;
};

template <typename T>
inline void ServicePrinter::printT(const Buffer &buffer) {
  T value;
  memcpy(&value, buffer.begin(), buffer.size());
  std::cout << m_serviceName << " : " << value << std::endl;
}

template <>
inline void ServicePrinter::printT<json>(const Buffer &buffer) {
  json value = json::parse(buffer.begin(), buffer.end());
  std::cout << "=== " << m_serviceName << " ===" << std::endl << value.dump(2) << std::endl;
}

inline void ServicePrinter::print(const Buffer &buffer) {
  const char *ptr = buffer.begin();
  size_t size = buffer.size();

  if (m_printMethod == "str") {
    std::string value(ptr, size);
    std::cout << value << std::endl;
  } else if (m_printMethod == "raw") {
    for (size_t i = 0; i < size; i++) {
      std::cout << std::hex << ptr[i];
      if (!i % 100)
        std::cout << std::endl;
    }
  } else if (m_printMethod == "float")
    this->printT<float>(buffer);
  else if (m_printMethod == "int")
    this->printT<int>(buffer);
  else if (m_printMethod == "uint")
    this->printT<unsigned int>(buffer);
  else if (m_printMethod == "double")
    this->printT<double>(buffer);
  else if (m_printMethod == "short")
    this->printT<short>(buffer);
  else if (m_printMethod == "long")
    this->printT<long>(buffer);
  else if (m_printMethod == "ulong")
    this->printT<unsigned long>(buffer);
  else if (m_printMethod == "ullong")
    this->printT<unsigned long long>(buffer);
  else if (m_printMethod == "json")
    this->printT<json>(buffer);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage : dqm4hep-subscribe-service name [raw|str|type]" << std::endl;
    return 1;
  }

  std::string name(argv[1]);
  std::string printMethod(argc >= 3 ? argv[2] : "raw");

  ServicePrinter printer(name, printMethod);
  Client client;
  client.subscribe(name, &printer, &ServicePrinter::print);

  while (1)
    sleep(1);

  return 0;
}
