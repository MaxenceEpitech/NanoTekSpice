/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice
 ** File description :
 ** 	File Name : readLoop.cpp Author : maxence.fourrier Date : 13 févr. 2018
 */

#include "ReadLoop.hpp"

#include <stddef.h>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <iterator>

#include "C4001.hpp"
#include "C4011.hpp"
#include "C4030.hpp"
#include "C4069.hpp"
#include "C4071.hpp"
#include "C4081.hpp"
#include "Pin.hpp"

static bool continueLoop = true;

void nts::ReadLoop::readArgv(char** av)
{
	size_t pos;
	for (int i = 0; av[i] != nullptr; i++) {
		std::string tmp = (std::string) av[i];
		if ((pos = tmp.find('=')) == std::string::npos)
			throw "Unvalid args.";
		std::string name = std::string().assign(tmp, 0, pos);
		if (!_parser.inputExist(name)) {
			throw "Unknown input name.";
		}
		std::string value = std::string().assign(tmp, pos + 1, tmp.size() - (pos + 1));
		if (value == "0")
			_parser.setInputValue(name, nts::Tristate::FALSE);
		else if (value == "1")
			_parser.setInputValue(name, nts::Tristate::TRUE);
		else
			throw "Unknown value";
		_parser.getPinFromInputList(name)->getLinkedTo()->setValue(_parser.getPinFromInputList(name)->getValue());
	}
	for (std::vector<Pin*>::const_iterator it = _parser.getInput()->begin(); it != _parser.getInput()->end(); ++it) {
		if ((*it)->getValue() == nts::Tristate::UNDEFINED)
			throw "All input have to be initialize.";
	}
}

nts::ReadLoop::ReadLoop(std::string fileName, char **argv)
		: _command(""), _parser(fileName)
{
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::input, "input"));
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::exit, "exit"));
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::display, "display"));
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::simulate, "simulate"));
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::loop, "loop"));
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::dump, "dump"));
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::exit, "exit"));
	_ptrVector.push_back(std::make_pair(&nts::ReadLoop::exit, ""));

	readArgv(argv);
	simulate();
	display();
	launch();
}

nts::ReadLoop::~ReadLoop()
{
}

void nts::ReadLoop::launch()
{
	std::signal(SIGINT, nts::ReadLoop::handleCControl);
	while (std::cin) {
		std::cout << PROMPT;
		std::getline(std::cin, _command);
		if (std::cin.eof()) {
			nts::ReadLoop::exit();
		} else if (readCommand()) {
			std::cin.clear();
		} else {
			std::cout << "ERROR while interpreting command: Commands are: exit, display, input=<value>, simulate, loop, dump" << std::endl;
		}
	}
}

bool nts::ReadLoop::readCommand()
{
	if (_command.empty()) {
		return true;
	}
	for (int i = 0; _ptrVector.at(i).second != ""; i++) {
		if (_command == _ptrVector.at(i).second || _command.find("=") != std::string::npos)
			return ((this)->*_ptrVector.at(i).first)();
	}
	return false;
}

bool nts::ReadLoop::exit()
{
	std::exit(0);
}

bool nts::ReadLoop::input()
{
	size_t pos = _command.find("=");
	std::string inputName = std::string().assign(_command, 0, pos);
	if (!_parser.inputExist(inputName)) {
		std::cerr << inputName << ":This input does not exist." << std::endl;
		return true;
	}
	std::string value = std::string().assign(_command, pos + 1, _command.size() - (pos + 1));
	if (value == "1")
		_parser.setInputValue(inputName, nts::Tristate::TRUE);
	else if (value == "0")
		_parser.setInputValue(inputName, nts::Tristate::FALSE);
	else if (value == "U")
		_parser.setInputValue(inputName, nts::Tristate::UNDEFINED);
	else {
		std::cerr << "Unvalid value. Value has to be 1 or 0 or U." << std::endl;
	}
	_parser.getPinFromInputList(inputName)->getLinkedTo()->setValue(_parser.getPinFromInputList(inputName)->getValue());
	return true;
}

bool nts::ReadLoop::display()
{
	for (std::vector<nts::Pin *>::const_iterator it = _parser.getOutput()->begin(); it != _parser.getOutput()->end(); it++) {
		if ((*it)->getValue() == nts::Tristate::UNDEFINED) {
			std::cout << (*it)->getName() << "=" << "U" << std::endl;
		} else {
			std::cout << (*it)->getName() << "=" << (*it)->getValue() << std::endl;
		}
	}
	return true;
}

bool nts::ReadLoop::simulate()
{
	for (std::vector<Pin*>::const_iterator it = _parser.getInput()->begin(); it != _parser.getInput()->end(); ++it) {
		if ((*it)->isClock()) {
			if ((*it)->getValue() == nts::Tristate::TRUE) {
				(*it)->setValue(nts::Tristate::FALSE);
			} else if ((*it)->getValue() == nts::Tristate::FALSE) {
				(*it)->setValue(nts::Tristate::TRUE);

			}
			(*it)->getLinkedTo()->setValue((*it)->getValue());
		}
	}
	for (std::vector<std::pair<nts::IComponent*, std::string>>::const_iterator it = _parser.getComponents()->begin(); it != _parser.getComponents()->end(); ++it) {
		if (dynamic_cast<nts::C4071 *>((*it).first))
			dynamic_cast<nts::C4071 *>((*it).first)->simulate();
		if (dynamic_cast<nts::C4081 *>((*it).first))
			dynamic_cast<nts::C4081 *>((*it).first)->simulate();
		if (dynamic_cast<nts::C4011 *>((*it).first))
			dynamic_cast<nts::C4011 *>((*it).first)->simulate();
		if (dynamic_cast<nts::C4030 *>((*it).first))
			dynamic_cast<nts::C4030 *>((*it).first)->simulate();
		if (dynamic_cast<nts::C4001 *>((*it).first))
			dynamic_cast<nts::C4001 *>((*it).first)->simulate();
		if (dynamic_cast<nts::C4069 *>((*it).first))
			dynamic_cast<nts::C4069 *>((*it).first)->simulate();
		// add other comp
	}
	return true;
}

bool nts::ReadLoop::loop()
{
	std::signal(SIGINT, nts::ReadLoop::handleCControlLoop);
	continueLoop = true;
	while (continueLoop) {
		this->simulate();
	}
	return true;
}

bool nts::ReadLoop::dump()
{
	std::cout << "dumping" << std::endl;
	return true;
}

void nts::ReadLoop::handleCControlLoop(int signum)
{
	int voider = signum;
	voider += 1;
	continueLoop = false;
}

void nts::ReadLoop::handleCControl(int signum)
{
	std::exit(signum);
}
