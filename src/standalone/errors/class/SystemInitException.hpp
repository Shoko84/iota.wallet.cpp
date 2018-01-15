#ifndef NEXUS_LAUNCHER_ERRORS_FAILED_ON_SYSTEM_INIT
#define NEXUS_LAUNCHER_ERRORS_FAILED_ON_SYSTEM_INIT

#include <exception>
#include <string>

namespace nx {
	class SystemInitException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			
			SystemInitException (const std::string& systemName, const std::string& message):	_msg(std::string("Failed to init ") + systemName + std::string(" system: ") + message)	{}
	
			virtual ~SystemInitException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_FAILED_ON_SYSTEM_INIT