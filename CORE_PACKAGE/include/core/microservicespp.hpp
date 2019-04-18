/**
 * \file microservicespp.hpp
 * \author Luca Di Mauro
 * \brief Header file for all core classes
 */


#ifndef MICROSERVICES_PP_H
#define MICROSERVICES_PP_H

#include <json/json.h>
#include <core/dynamicLoader.hpp>
#include <core/exceptions.hpp>
#include <dynamicThreadPool.h>

#include <thread>
#include <mutex>
#include <string>
#include <list>
#include <csignal>
#include <map>


namespace microservicespp {
	class ServiceRegistry;		// Keeps track of running services
	class EventManager;			// Has the aim of register all throwable events by services with their subscriber
	class Engine;				// Collects behaviours of ServiceRegistry and EventManager
	class Coordinator;			// Provides Engine's functionalities to services

	class Service;				// Entity which can execute tasks and can be loaded and unloaded
	class ExternalService;		// Specialization of Service class as an external process service 
	class InternalService;		// Specialization of Service class as an internal process service

	class Task;					// Belongs to a service. Can fire events and is executed in parallel with other Tasks
	class PeriodicTask;			// Specialization of Task class as a periodic work
	class OneShotTask;			// Specialization of Task class as a single iteration of a work
	class TimeoutTask;			// Specialization of Task class as a work started after a variable number of milliseconds

	class Logger;				// Log messages with different log levels to an output stream






	/**
	 * \class Handler
	 * \brief Definiton of type "Handler" ehich represent a callback called by "periodically", "setTimeout" and "asynchronously" operations
	 */
	typedef std::function<void(void)> Handler;


	/**
	 * \class EventHandler
	 * \brief Definition of type "EventHandler" which represent a callback called by "triggerEvent" operation
	 */
	typedef std::function<void (Json::Value)> EventHandler;


	/**
	 * \class TemplateEventHandler
	 * \brief Definition of type "TemplateEventHandler" which represent a callback called by "triggerEvent" which take
	 			as arguments a parameter of type T
	 */
	template <typename T>
	using TemplatedEventHandler = std::function<void (T)>;


	/**
	 * \class CommandHandler
	 * \brief Definiton of type "CommandHandler" which represent a command executed by a Service
	 */
	typedef std::function<Json::Value (Json::Value)> CommandHandler;


	/**
	 * \class PrepareShutdownFunction
	 * \brief Definition of type "PrepareShutdownFunction" which is called by Service class before call "shutdown" function
	 */
	typedef std::function<void(void)> PrepareShutdownFunction;


	/**
	 * \class EngineStatus
	 * \brief Enum which describes current engine status
	 */
	enum class EngineStatus {Starting, Running, ShuttingDown, Died};


	/**
	/**
	 * \class ServiceStatus
	 * \brief Enum which describes current status of service
	 */
	enum class ServiceStatus {Loading, Running, ShuttingDown, Died};


	/**
	 * \class TaskType
	 * \brief Enum which define all possibe types of tasks
	 */
	enum class TaskType {None, OneShot, Timeout, Periodic};


	/**
	 * \class TaskStatus
	 * \brief Enum which represents status of current task
	 */
	enum class TaskStatus {Waiting, Running, Ended};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class ServiceRegistry
	 * \brief Its purpose is to keep track of loaded services and to run tasks when requested
	 */
	class ServiceRegistry : private Logger {
	private :
		// TODO


	protected :

		/**
		 * \brief Function to start threads
		 */
		void startRegistry ();

		/**
		 * \brief Function to stop ServiceRegistry
		 */
		void stopRegistry ();

		/**
		 * \brief Return wether registry is started or not
		 */
		bool isStarted ();


		/**
		 * \brief Loads a Service from shared object and insert it into service map
		 */
		void loadService	(std::string soPath, std::string name, int runLevel);

		/**
		 * \brief Returns true if exists a service called "name", false otherwise
		 */
		bool existsService	(std::string name);

		/**
		 * \brief Unload Service with name "name", destroying it
		 */
		void unloadService (std::string name);

		/**
		 * \brief Returns the Service with this name
		 */
		Service &getService	(std::string name);


	public :

		ServiceRegistry				(Engine &engine);
		virtual ~ServiceRegistry	() = 0;
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class EventManager
	 * \brief This class has the aim of register all throwable events by services with their subscriber and, when a service is fired, to call subscriber's callbacks
	 */
	class EventManager : private Logger {
	private :
		// TODO


	protected :

		void serviceJoin (std::string serviceName);
		void serviceLeave (std::string serviceName);

		void registerEvent	(std::string serviceName, std::string eventName);
		void onEvent		(std::string service, std::string eventName, EventHandler handler);
		void triggerEvent	(std::string service, std::string eventName, Json::Value &payload);


	public :

		EventManager (Engine &engine);
		virtual ~EventManager () = 0;
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class Engine
	 * \brief It collects behavior of Logger, Runner and EventManager classes
	 * Orchestrator class is a friend of Engine class, to limit access of functions to services
	 */
	class Engine : private Logger, private EventManager, private ServiceRegistry {
	friend class Coordinator;
	
	private :
		// TODO


	public :

		Engine	(std::string configurationFile);
		~Engine	();

		Json::Value &configuration;

		void engineOn	();


		void registerEvent	(Service &instance, std::string eventName) {
			EventManager::registerEvent (instance.getName(), eventName);
		}

		void onEvent (std::string triggerService, std::string eventName, EventHandler handler) {
			EventManager::onEvent (triggerService, eventName, handler);
		}

		void triggerEvent (Service &instance, std::string eventName, Json::Value &payload) {
			EventManager::triggerEvent (instance.getName(), eventName, payload);
		}
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class Coordinator
	 * \brief Class which provide Engine's functionalities to services
	 */
	class Orchestrator : private Logger {
	private :
		// TODO
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class Service
	 * \brief Entity which can execute tasks and can be loaded and unloaded
	 */
	class Service : public Logger {
	private :

		std::string name;
		PrepareShutdownFunction prepareShutdown;
		int runLevel;
		ServiceStatus status;
		std::mutex statusMutex;


	protected :

		Coordinator &coordinator;

		void asynchronously	(Handler handler);
		void setTimeout		(int timeout, Handler handler);
		void periodically	(int period, Handler handler);

		// TODO void addCommandCallback	(std::string commandName, CommandHandler handler);


	public :

		Service						(std::string name, Engine &engine, int runLevel, PrepareShutdownFunction function= []{});
		virtual ~Service			() = 0;

		void startMe				();
		void stopMe					();

		std::string getName			();
		ServiceStatus getStatus		();

		typedef Service* create_t	(Engine *s, std::string name, int runLevel);
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class InternalService
	 * \brief Specialization of Service class as an internal process service
	 */
	class InternalService : public Service {
	public :
		// TODO
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class ExternalService
	 * \brief Specialization of Service class as an external process service 
	 */
	class ExternalService : public Service {
	public :
		// TODO
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class Task
	 * \brief Virtual class wich represent generic runnable task
	 */
	class Task : public Logger {
	private :
		// TODO


	public :

		Task			(Service &parentService, Handler h, TaskType type, unsigned long delay, bool restartMe= false);
		virtual ~Task	() = 0;

		TaskType getType				();
		void executeHandler				();
		TaskStatus getStatus			();
		TaskStatus waitForStatus		(TaskStatus requestedStatus);
		unsigned long getDelay			();
		void stopMe						();
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class OneShotTask
	 * \brief Class which represent an asynchronous task executed for one time
	 */
	class OneShotTask : public Task {
	public :

		inline OneShotTask		(Service &parentService, Handler handler)
			: Task (parentService, handler, TaskType::OneShot, 0) {}
		inline ~OneShotTask 	() {}
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class TimeoutTask
	 * \brief Class which represent an timeout task
	 */
	class TimeoutTask : public Task {
	public :

		inline TimeoutTask	(Service &parentService, Handler handler, int timeout)
			: Task (parentService, handler, TaskType::Timeout, timeout) {}
		inline ~TimeoutTask	() {}
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class PeriodicTask
	 * \brief Class which represent a periodic task
	 */
	class PeriodicTask : public Task {
	private :

		bool startNow;


	public :

		inline PeriodicTask (Service &parentService, Handler handler, int period, bool startNow=false)
			: Task (parentService, handler, TaskType::Periodic, period, true), startNow(startNow) {}
		inline ~PeriodicTask () {}

		inline bool getStartNow () {
			return startNow;
		}
	};








	/* ===================================================================================== */
	/* ===================================================================================== */








	/**
	 * \class Logger
	 * \brief Class to log messages with different log levels to an output stream
	 */
	class Logger {
	private :
		// TODO


	public :
		// TODO
	};
} // namespace microservicespp


#endif