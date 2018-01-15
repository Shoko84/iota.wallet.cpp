#ifndef NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND
#define NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND

#include <exception>
#include <string>

namespace nx {
	class SystemNotFoundException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			SystemNotFoundException (const std::string& systemName):	_msg(std::string("System ") + systemName + std::string(" not found!"))	{}
	
			virtual ~SystemNotFoundException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND