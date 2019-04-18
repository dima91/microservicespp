/**
 * \file exceptions.hpp
 * \author Luca Di Mauro
 * \brief Header file for all exceptions class
 */


#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdexcept>


namespace microservicespp {
	namespace exceptions {

		/**
		 * \class OpenModuleException
		 * \brief Definition (and implementation) of exception "OpenModuleException".
		 * This exception will be launched from DynamicLoader to notify that an error occurs during "dlopen" function
		 */
		class OpenModuleException : public std::runtime_error {
		public:
			OpenModuleException (const char *msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			OpenModuleException (const std::string &msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			virtual ~OpenModuleException() throw() { /*Destructor do nothing*/ };
			virtual const char *what() const throw() { return std::runtime_error::what(); };
		};




		/**
		 * \class LoadSymbolExcepion
		 * \brief Definition (and implementation) of exception "LoadSymbolExcepion".
		 * This exception will be launched from DynamicLoader to notify that an error occurs during "dlsym" function
		 */
		class LoadSymbolExcepion : public std::runtime_error {
		public:
			LoadSymbolExcepion (const char *msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			LoadSymbolExcepion (const std::string &msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			virtual ~LoadSymbolExcepion() throw() { /*Destructor do nothing*/ };
			virtual const char *what() const throw() { return std::runtime_error::what(); };
		};





		/**
		 * \class EngineException
		 * \brief Definition (and implementation) of an exception called by Engine class
		 */
		class EngineException : public std::runtime_error {
		public:
			EngineException (const char *msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			EngineException (const std::string& msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			virtual ~EngineException() throw() { /*Destructor do nothing*/ };
			virtual const char *what() const throw() { return runtime_error::what(); };
		};




		/**
		 * \class ServiceRegistryException
		 * \brief Definition (and implementation) of exception "ServiceRegistryException".
		 */
		class ServiceRegistryException : public std::runtime_error {
		public:
			ServiceRegistryException (const char *msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			ServiceRegistryException (const std::string &msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			virtual ~ServiceRegistryException () throw() { /*Destructor do nothing*/ };
			virtual const char *what() const throw() { return std::runtime_error::what(); };
		};




		/**
		 * \class EventManagerException
		 * \brief Definition (and implementation) of exception "EventManagerException".
		 */
		class EventManagerException : public std::runtime_error {
		public:
			EventManagerException (const char *msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			EventManagerException (const std::string &msg) : runtime_error(msg) { /*Constructor do nothing*/ };
			virtual ~EventManagerException () throw() { /*Destructor do nothing*/ };
			virtual const char *what() const throw() { return std::runtime_error::what(); };
		};




		/**
		 * \class ServiceException
		 * \brief Definition (and implementation) of exception "ServiceException".
		 */
		class ServiceException : public std::runtime_error {
		private :
			std::string whichService;
		public:
			ServiceException (const char *msg, const char *service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			ServiceException (const char *msg, const std::string &service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			ServiceException(const std::string &msg, const char *service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			ServiceException (const std::string &msg, const std::string &service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			virtual ~ServiceException() throw() { /*Destructor do nothing*/ };
			virtual const char *what() const throw() { return std::runtime_error::what(); };
			virtual const char *which() const throw() {return whichService.c_str();}
		};




		/**
		 * \class DestroyServiceException
		 * \brief Definition (and implementation) of exception "DestroyServiceException".
		 * This exception will be launched from any object belonging to Service class to notify to station that the service have to be destroyed
		 */
		class DestroyServiceException : public std::runtime_error {
		private:
			std::string errorMessage;
			std::string whichService;

		public:
			DestroyServiceException (const char *msg, const char *service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			DestroyServiceException (const char *msg, const std::string &service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			DestroyServiceException(const std::string &msg, const char *service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			DestroyServiceException (const std::string &msg, const std::string &service) : runtime_error(msg), whichService(service) { /*Constructor do nothing*/ };
			virtual ~DestroyServiceException() throw() { /*Destructor do nothing*/ };
			virtual const char *what() const throw() { return std::runtime_error::what(); };
			virtual const char *which() const throw() {return whichService.c_str();}
		};

	} // namespace exceptions	
} // namespace microservicespp



#endif