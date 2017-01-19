/// \file Client.h
/*
 *
 * Client.h header template automatically generated by a class generator
 * Creation date : dim. d�c. 4 2016
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


#ifndef CLIENT_H
#define CLIENT_H

#include "dqm4hep/RequestHandler.h"
#include "dqm4hep/ServiceHandler.h"
#include "dqm4hep/Service.h"

#include "json/json.h"

#include "dic.hxx"

namespace dqm4hep {

  namespace net {

    /** Client class
     */
    class Client
    {
    public:
      /** Constructor
       */
      Client();

      /** Destructor
       */
      ~Client();

      /** Query server information
       */
      void queryServerInfo(const std::string &serverName, Json::Value &serverInfo) const;

      /** Send a request. Do not wait for any response
       */
      void sendRequest(const std::string &type, const std::string &name, const Json::Value &request) const;

      /** Send a request. Wait for the server response
       */
      template <typename Response>
      void sendRequest(const std::string &type, const std::string &name, const Json::Value &request, Response &response) const;

      /** Subscribe to target service
       */
      template <typename T, typename S, typename U>
      void subscribe(const std::string &serviceType, const std::string &serviceName, S *pController, U function);

      /** Whether this client already registered a service subscription
       */
      bool hasSubscribed(const std::string &serviceType, const std::string &serviceName) const;

    private:
      typedef std::map<std::string, BaseServiceHandler *>      ServiceHandlerMap;
      ServiceHandlerMap            m_serviceHandlerMap;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename Response>
    inline void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request, Response &response) const
    {
      throw std::runtime_error("Client::sendRequest(): response type not supported !");
    }

    template <>
    inline void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request, int &response) const
    {
      std::string rpcName(BaseRequestHandler::getFullRequestHandlerName(type, name));
      std::string emptyJson("{}");
      DimRpcInfo rpcInfo(const_cast<char*>(rpcName.c_str()), response);

      Json::Value message;
      message["response"] = true;
      message["request"] = request;
      Json::FastWriter writer;
      std::string messageStr(writer.write(message));

      rpcInfo.setData(const_cast<char*>(messageStr.c_str()));
      response = rpcInfo.getInt();
    }

    template <>
    inline void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request, float &response) const
    {
      std::string rpcName(BaseRequestHandler::getFullRequestHandlerName(type, name));
      std::string emptyJson("{}");
      DimRpcInfo rpcInfo(const_cast<char*>(rpcName.c_str()), response);

      Json::Value message;
      message["response"] = true;
      message["request"] = request;
      Json::FastWriter writer;
      std::string messageStr(writer.write(message));

      rpcInfo.setData(const_cast<char*>(messageStr.c_str()));
      response = rpcInfo.getFloat();
    }

    template <>
    inline void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request, double &response) const
    {
      std::string rpcName(BaseRequestHandler::getFullRequestHandlerName(type, name));
      std::string emptyJson("{}");
      DimRpcInfo rpcInfo(const_cast<char*>(rpcName.c_str()), response);

      Json::Value message;
      message["response"] = true;
      message["request"] = request;
      Json::FastWriter writer;
      std::string messageStr(writer.write(message));

      rpcInfo.setData(const_cast<char*>(messageStr.c_str()));
      response = rpcInfo.getDouble();
    }

    template <>
    inline void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request, std::string &response) const
    {
      std::string rpcName(BaseRequestHandler::getFullRequestHandlerName(type, name));
      std::string emptyJson("{}");
      DimRpcInfo rpcInfo(const_cast<char*>(rpcName.c_str()), (char*)"");

      Json::Value message;
      message["response"] = true;
      message["request"] = request;
      Json::FastWriter writer;
      std::string messageStr(writer.write(message));

      rpcInfo.setData(const_cast<char*>(messageStr.c_str()));
      response = rpcInfo.getString();
    }

    template <>
    inline void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request, Buffer &response) const
    {
      std::string rpcName(BaseRequestHandler::getFullRequestHandlerName(type, name));
      std::string emptyJson("{}");
      DimRpcInfo rpcInfo(const_cast<char*>(rpcName.c_str()), (void*)nullptr, 0);

      Json::Value message;
      message["response"] = true;
      message["request"] = request;
      Json::FastWriter writer;
      std::string messageStr(writer.write(message));

      rpcInfo.setData(const_cast<char*>(messageStr.c_str()));
      Buffer *pBuffer = (Buffer*)rpcInfo.getData();

      if(!pBuffer || !pBuffer->m_pBuffer || pBuffer->m_bufferSize == 0)
        return;

      response.m_pBuffer = pBuffer->m_pBuffer;
      response.m_bufferSize = pBuffer->m_bufferSize;
    }

    template <>
    inline void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request, Json::Value &response) const
    {
      std::string rpcName(BaseRequestHandler::getFullRequestHandlerName(type, name));
      std::string emptyJson("{}");
      DimRpcInfo rpcInfo(const_cast<char*>(rpcName.c_str()), const_cast<char*>(emptyJson.c_str()));

      Json::Value message;
      message["response"] = true;
      message["request"] = request;
      Json::FastWriter writer;
      std::string messageStr(writer.write(message));

      rpcInfo.setData(const_cast<char*>(messageStr.c_str()));
      char *jsonStr = rpcInfo.getString();

      if(!jsonStr)
        return;

      Json::Reader reader;
      reader.parse(jsonStr, response);
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T, typename S, typename U>
    inline void Client::subscribe(const std::string &type, const std::string &name, S *pController, U function)
    {
      const std::string fullName(BaseService::getFullServiceName(type, name));
      auto findIter = m_serviceHandlerMap.find(fullName);

      if(findIter != m_serviceHandlerMap.end())
        return;

      auto inserted = m_serviceHandlerMap.insert(ServiceHandlerMap::value_type(fullName, nullptr));

      if(inserted.second)
      {
        inserted.first->second = new ServiceHandlerT<T,S>(this, type, name, pController, function);
      }
      else
        throw;
    }

  }

}

#endif  //  CLIENT_H