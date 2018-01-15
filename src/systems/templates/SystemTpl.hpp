#ifndef NEXUS_LAUNCHER_SYSTEM_TPL_HPP
# define NEXUS_LAUNCHER_SYSTEM_TPL_HPP

#include <string>

#include "SystemInitException.hpp"

namespace nx {
	class Launcher;
}

namespace nx {
	class SystemTpl
	{
	public:
		SystemTpl(nx::Launcher& launcher, const std::string& name) : _root(launcher), _name(name) {};
		virtual ~SystemTpl() {};

	public:
		virtual void				init(void) = 0;
		virtual int					run(void) = 0;
		virtual const std::string&	getName(void) const { return this->_name; }
		virtual const nx::Launcher&	getRoot(void) const { return this->_root; }

	protected:
		nx::Launcher&				_root;		
		const std::string			_name;
	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_TPL_HPP