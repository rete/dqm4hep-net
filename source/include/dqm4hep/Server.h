/// \file Server.h
/*
 *
 * Server.h header template automatically generated by a class generator
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


#ifndef SERVER_H
#define SERVER_H

#include "dqm4hep/Service.h"
#include "dqm4hep/RequestHandler.h"

#include "dis.hxx"

namespace dqm4hep {

  namespace net {

    /** Server class
     */
    class Server
    {
    public:
      /** Constructor
       */
      Server(const std::string &name);

      /** Destructor
       */
      ~Server();

      /** Start serving services and handling requests
       */
      void start();

      /** Stop serving services and handling requests
       */
      void stop();

      /** Close all service and request handlers.
       *  Called from destructor
       */
      void clear();

      /** Create a new service of concrete implementation T
       */
      template <typename T>
      T *createService(const std::string &type, const std::string &name);

      /** Create a new request handler
       */
      template <typename T, typename S>
      RequestHandler *createRequestHandler(const std::string &type, const std::string &name,
          T *pController, S function);

      /**
       */
      bool isServiceRegistered(const std::string &type, const std::string &name) const;

      /**
       */
      bool isRequestHandlerRegistered(const std::string &type, const std::string &name) const;

      /**
       */
      Service *getService(const std::string &type, const std::string &name) const;

      /**
       */
      RequestHandler *getRequestHandler(const std::string &type, const std::string &name) const;

      /** Get the dim dns node.
       *  First look at DimServer::getDnsNode() then
       *  environment variable "DIM_DNS_NODE"
       */
      static std::string getDnsNode();

      /** Get the dim dns port
       */
      static int getDnsPort();

    private:
      typedef std::map<std::string, Service *>         ServiceMap;
      typedef std::map<std::string, RequestHandler *>  RequestHandlerMap;

      std::string                                    m_name;
      bool                                           m_started;
      ServiceMap                                     m_serviceMap;
      RequestHandlerMap                              m_requestHandlerMap;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename T>
    T *Server::createService(const std::string &type, const std::string &name)
    {
      const std::string fullServiceName(Service::getFullServiceName(type, name));

      auto findIter = m_serviceMap.find(fullServiceName);

      if(findIter != m_serviceMap.end())
      {
        T *pService = dynamic_cast<T*>(findIter->second);

        if(!pService)
          throw;

        return pService;
      }

      // first insert nullptr, then create service
      std::pair<ServiceMap::iterator, bool> inserted = m_serviceMap.insert(ServiceMap::value_type(fullServiceName, nullptr));


      if(inserted.second)
      {
        T *pService = new T(this, type, name);
        inserted.first->second = pService;
        return pService;
      }
      else
        throw;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T, typename S>
    inline RequestHandler *Server::createRequestHandler(const std::string &type, const std::string &name,
        T *pController, S function)
    {
      const std::string fullRequestHandlerName(RequestHandler::getFullRequestHandlerName(type, name));

      auto findIter = m_requestHandlerMap.find(fullRequestHandlerName);

      if(findIter != m_requestHandlerMap.end())
      {
        RequestHandlerT<T> *pRequestHandler = dynamic_cast<RequestHandlerT<T>*>(findIter->second);

        if(!pRequestHandler)
          throw;

        return pRequestHandler;
      }

      // first insert nullptr, then create service
      std::pair<RequestHandlerMap::iterator, bool> inserted = m_requestHandlerMap.insert(RequestHandlerMap::value_type(fullRequestHandlerName, nullptr));

      if(inserted.second)
      {
        RequestHandlerT<T> *pRequestHandler = new RequestHandlerT<T>(this, type, name, pController, function);
        inserted.first->second = pRequestHandler;
        return pRequestHandler;
      }
      else
        throw;
    }
  }

} 

#endif  //  SERVER_H