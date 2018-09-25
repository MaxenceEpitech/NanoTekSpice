/*	
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice
 ** File description :
 ** 	File Name : readLoop.hpp Author : maxence.fourrier Date : 13 févr. 2018
 */

#ifndef READLOOP_HPP_
#define READLOOP_HPP_

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "IComponent.hpp"
#include "Parser.hpp"

#define PROMPT "> "

namespace nts {
	class ReadLoop {
	public:
		ReadLoop(std::string fileName, char **argv);
		~ReadLoop();
		void launch();
		void readArgv(char **av);

	private:
		std::string _command;
		Parser _parser;
		bool readCommand();

		typedef bool (nts::ReadLoop::*funcPtr)();
		std::vector<std::pair<funcPtr, std::string>> _ptrVector;

		bool exit();
		bool input();
		bool display();
		bool simulate();
		bool loop();
		bool dump();
		static void handleCControlLoop(int signum);
		static void handleCControl(int signum);

		std::list<nts::IComponent*> components;
	};
}

#endif /* READLOOP_HPP_ */
