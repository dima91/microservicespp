/**
 * \file dynamicLoader.hpp
 * \author Luca Di Mauro
 * \brief Implementation of class DynamicLoader
 */


#ifndef DYNAMIC_LOADER_H
#define DYNAMIC_LOADER_H

#define FACTORY_SYMBOL_NAME "createObject"

#include <core/exceptions.hpp>

#include <memory>
#include <string>
#include <dlfcn.h>


namespace microservicespp {
	namespace dynamicLoader {

		template <class T>
		class DynamicLoader {

		private:

			/**
			 * \class SharedObject
			 * \brief Class which represents an object to create new dynamic objects
			 */
			template <class V>
			class SharedObject {
			private :
				typename V::create_t *factory = nullptr;
				void *dllHandle = nullptr;


				void openModule (std::string module) {
					if(!(dllHandle= dlopen (module.c_str(), RTLD_NOW))) {
						//std::cerr << "Failed to open library: " << dlerror() << std::endl;
						throw exceptions::OpenModuleException (dlerror());
					}

					// Reset errors
					dlerror();

					if(!(factory = (typename V::create_t*) dlsym (dllHandle, FACTORY_SYMBOL_NAME))) {
						//std::cerr << "Failed to load 'create' symbol: " << dlerror() << std::endl;
						closeModule();
						throw exceptions::LoadSymbolExcepion (dlerror());
					}
				}


				void closeModule() {
					if (dllHandle) {
						dlclose (dllHandle);
						dllHandle = nullptr;
					}
					if (factory) {
						factory = nullptr;
					}
				}


			public :

				SharedObject (std::string module) {
					openModule (module);
				}


				~SharedObject () {
					closeModule ();
				}


				/*void checkArgs (int idx) {
					if (idx != 3) {
						std::cout << "Error: too much arguments!\n";
					}
					std::cout<<std::endl;
				}


				template<typename First, typename ... Strings>
				void checkArgs (int idx, First arg, const Strings&... rest) {
					if (idx == 0 && dynamic_cast<noes::ItsStation *>(arg))
						checkArgs (idx+1, rest...);
					else if (idx == 1 && dynamic_cast<std::string>(arg))
						checkArgs (idx+1, rest...);
					else if (idx == 2 && dynamic_cast<int>(arg))
						checkArgs (idx+1, rest...);
					else
						std::cout << "Error for args with index " << idx << std::endl;
				}*/


				// Args:	<ItsStation &, string, int>
				template <typename... Args>
				V *makeObject (Args... args) {
					//checkArgs (0, args...);
					if (factory) {
						return factory (args...);
					}
					else
						return nullptr;
				}
			};

			std::string moduleName;
			SharedObject<T> *sharedObject;

		public:
			DynamicLoader (std::string modName) : moduleName (modName) {
				sharedObject= new SharedObject<T> (moduleName);
			}


			~DynamicLoader () {
				delete (sharedObject);
			}


			template <typename... Args>
			T *makeObject(Args... args) {
				if (!sharedObject)
					return nullptr;

				return sharedObject->makeObject (args...);
			}


			std::string getModuleName () {
				return moduleName;
			}
		};

	} // namespace dynamicLoader
} // namespace microservicespp


#endif
