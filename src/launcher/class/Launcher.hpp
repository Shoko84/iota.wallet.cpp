/**
 * @file Launcher.hpp
 * @author JSX
 */

#ifndef NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
#define NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_

#include <memory>
#include <vector>
#include <iostream>

#include "SystemNotFoundException.hpp"
#include "SystemInitException.hpp"
#include "SystemTpl.hpp"

#include "UISystem.hpp"

namespace nx {
	/**
	* @class Launcher
	* This is the core class of the project.
	* It will link all the systems and will be the entry point for the init/run.
	*/
	class Launcher
	{
	public:
		/**
		 * Classic constructor for Launcher using RAII for assigning private members.
		 * If you want to add more systems to the core, please add them into the vector initialisazion of the method.
		 * @param ac It must be the first parameter given to the main function. Its reference will be stored in nx::Launcher::_argc.
		 * @param av It must be the second parameter given to the main function. Its pointer will be stored in nx::Launcher::_argv.
		 */
		Launcher(int, char**);
		/**
		 * Default destructor for Launcher.
		 */
		~Launcher();

	public:
		/**
		 * Getter for nx::Launcher::_systems
		 * @return This method return a const reference to the vector of systems (nx::Launcher::_systems)
		 */
		const std::vector<std::shared_ptr<nx::SystemTpl>>& getSystems(void) const;

		/**
		 * This method take a string in parameter and return a shared pointer to the associated system.
		 * If the system cannot be found, this method will throw nx::SystemNotFoundException.
		 * @param target The name of the system used for the search.
		 * @return This method return a const reference to a shared pointer of type nx::SystemTpl
		 */
		const std::shared_ptr<nx::SystemTpl>& getSystemByName(const std::string&) const;

		/**
		 * Initialize and run all the systems from nx::Launcher::_systems
		 * @return This method return either EXIT_FAILURE or EXIT_SUCCESS
		 */
		int run(void);

		/**
		 * Getter for nx::Launcher::_argc
		 * @return This method return a reference to nx::Launcher::_argc
		 */
		int& getArgc(void) const;

		/**
		 * Getter for nx::Launcher::_argv
		 * @return This method return a pointer to nx::Launcher::_argv
		 */
		char** getArgv(void) const;


		/**
		* Getter for the binary absolute path
		* @return This method returns a const std::string containing the binary absolute path
		*/
		std::string const	getBinaryAbsolutePath() const;


	private:
		/**
		 * This method will call the init method on each of the system from nx::Launcher::_systems.
		 * @return If one of the init calls fail, an exception is catched and the function return false, else the function return true
		 */
		bool init(void);

	private:
		int&	 	_argc; /**< A reference to the main ARGC. It represents the number of arguments given to the program */
		char**		_argv; /**< A pointer to the main ARGV. It represents the arguments given to the program */
		std::vector<std::shared_ptr<nx::SystemTpl>>	_systems; /**< A vector containing all the systems (SystemTpl) needed by the Launcher. */

	};
}

#endif // !NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
