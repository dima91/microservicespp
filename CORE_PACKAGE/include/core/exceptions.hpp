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

	} // namespace exceptions	
} // namespace microservicespp



#endif