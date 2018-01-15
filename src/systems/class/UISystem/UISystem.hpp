#ifndef NEXUS_LAUNCHER_SYSTEM_UI_HPP_
# define NEXUS_LAUNCHER_SYSTEM_UI_HPP_

#include <QApplication>
#include <unordered_map>
#include "SystemTpl.hpp"
#include "Launcher.hpp"
#include "mainwindow.h"

namespace nx {
	static std::string REDFLAT = "#E74C3C";

	class UISystem : public nx::SystemTpl
	{
	public:
		UISystem(nx::Launcher&);
		~UISystem();

	public:
		virtual void				init(void);
		virtual int					run(void);

		int const					showWidget(std::string const& widgetName);
		int const					hideWidget(std::string const& widgetName);

	private:
		QApplication												_app;
		std::unordered_map<std::string, std::shared_ptr<QWidget>>   _widgetList;

	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_UI_HPP_
