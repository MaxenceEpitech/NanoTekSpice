/*
 ** EPITECH PROJECT, 2018
 ** NanoTekSpice
 ** File description:
 ** 	     @Author: killian @Date: 11:18:30 @File-name: Parser
 */

#include "Parser.hpp"

#include <stddef.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

#include "C4001.hpp"
#include "C4011.hpp"
#include "C4030.hpp"
#include "C4069.hpp"
#include "C4071.hpp"
#include "C4081.hpp"

nts::Parser::Parser(std::string fileName)
		: _fileContent(""), _link(false), _chipset(false)
{
	_ptrComponent.push_back(std::make_pair(new nts::C4071, "4071"));
	_ptrComponent.push_back(std::make_pair(new nts::C4081, "4081"));
	_ptrComponent.push_back(std::make_pair(new nts::C4011, "4011"));
	_ptrComponent.push_back(std::make_pair(new nts::C4030, "4030"));
	_ptrComponent.push_back(std::make_pair(new nts::C4001, "4001"));
	_ptrComponent.push_back(std::make_pair(new nts::C4069, "4069"));
	_ptrComponent.push_back(std::make_pair(nullptr, ""));

	read(fileName);
}

nts::Parser::~Parser()
{
}

bool nts::Parser::addToComponent(std::string line)
{
	size_t pos = line.find_first_of("\t ");
	pos = line.find_first_not_of("\t ", pos);
	std::string tmp = std::string().assign(line, pos, line.size() - pos);
	for (int i = 0; _ptrComponent.at(i).second != ""; i++) {
		if (line.find(_ptrComponent.at(i).second) == 0) {
			_components.push_back(std::make_pair(_ptrComponent.at(i).first, tmp));
			return true;
		}
	}
	return false;
}

void nts::Parser::addChipset(std::string line)
{
	std::string tmp;
	size_t start;
	if (line.find("input") == 0 && (start = line.find_first_not_of("\t ", 5)) != std::string::npos && line.find_first_not_of(ALPHANUMERICAL, start)
			== std::string::npos && line.at(start) != '#') {
		tmp.assign(line, start, line.size());
		if (inputExist(tmp) || outputExist(tmp) || componentExist(tmp))
			throw "Some chipsets have the same name.";
		_input.push_back(new Pin(nts::PinType::INPUT, tmp, false));
	} else if (line.find("output") == 0 && (start = line.find_first_not_of("\t ", 6)) != std::string::npos && line.find_first_not_of(ALPHANUMERICAL, start)
			== std::string::npos && line.at(start) != '#') {
		tmp.assign(line, start, line.size());
		if (inputExist(tmp) || outputExist(tmp) || componentExist(tmp))
			throw "Some chipsets have the same name.";
		_output.push_back(new Pin(nts::PinType::OUTPUT, tmp));
	} else if (line.find("clock") == 0 && (start = line.find_first_not_of("\t ", 5)) != std::string::npos && line.find_first_not_of(ALPHANUMERICAL, start)
			== std::string::npos && line.at(start) != '#') {
		tmp.assign(line, start, line.size());
		if (inputExist(tmp) || outputExist(tmp) || componentExist(tmp))
			throw "Some chipsets have the same name.";
		_input.push_back(new Pin(nts::PinType::INPUT, tmp, true));
	} else if (!addToComponent(line)) {
		throw "Unknown component.";
	}
}

void nts::Parser::addLink(std::string line)
{
	nts::links link;
	size_t posLink2;
	size_t firstSeparator = line.find(':');
	size_t secondSeparator = line.find_last_of(':');
	if (firstSeparator == secondSeparator || firstSeparator == std::string::npos || secondSeparator == std::string::npos || firstSeparator == 0 || secondSeparator == 0)
		throw "Unvalid file. Links have to be specified.";
	link.setLink1(std::string().assign(line, 0, firstSeparator));
	posLink2 = line.find_first_not_of(NUMBER, firstSeparator + 1);
	link.setLink2(std::string().assign(line, posLink2, secondSeparator - posLink2));
	if (line.find('\t', firstSeparator) == std::string::npos && line.find(' ', firstSeparator) == std::string::npos)
		throw "Unvalid file. Arg have to be separated by tabs";
	link.setIdLink1(std::atoi(std::string().assign(line, firstSeparator + 1, line.find('\t', firstSeparator) - firstSeparator - 1).c_str()));
	link.setIdLink2(std::atoi(std::string().assign(line, secondSeparator + 1, line.size() - (secondSeparator + 1)).c_str()));
	_links.push_back(link);
}

void nts::Parser::setInputValue(std::string input, nts::Tristate trist)
{
	for (std::vector<Pin*>::iterator it = _input.begin(); it != _input.end(); ++it)
		if ((*it)->getName() == input)
			(*it)->setValue(trist);
}

nts::Tristate nts::Parser::getInputValue(std::string name)
{
	for (std::vector<Pin*>::iterator it = _input.begin(); it != _input.end(); ++it)
		if ((*it)->getName() == name)
			return (*it)->getValue();
	throw "not find";
	return nts::Tristate::UNDEFINED;
}

bool nts::Parser::inputExist(std::string input)
{
	for (std::vector<nts::Pin *>::iterator it = _input.begin(); it != _input.end(); ++it)
		if ((*it)->getName() == input)
			return true;
	return false;
}

bool nts::Parser::outputExist(std::string output)
{
	for (std::vector<nts::Pin *>::iterator it = _output.begin(); it != _output.end(); ++it)
		if ((*it)->getName() == output)
			return true;
	return false;
}

bool nts::Parser::componentExist(std::string component)
{
	for (std::vector<std::pair<nts::IComponent *, std::string>>::iterator it = this->_components.begin(); it != this->_components.end(); it++) {
		if ((*it).second == component)
			return true;
	}
	return false;
}

void nts::Parser::checkLineError(std::string line)
{
	if (!line.empty() && line.at(0) != '#') {
		throw "Unvalid file.";
	}
}

void nts::Parser::addToList(std::string line)
{
	if (line == ".chipsets:") {
		_chipset = true;
		_link = false;
	} else if (line == ".links:") {
		_chipset = false;
		_link = true;
	} else if (_chipset) {
		addChipset(line);
	} else if (_link) {
		addLink(line);
	} else {
		checkLineError(line);
	}
	_fileContent += line + "\n";
}

void nts::Parser::read(std::string fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw "Can't open file.";
	}
	std::string tmp;
	while (std::getline(file, tmp)) {
		tmp = clearLine(tmp);
		if (!tmp.empty()) {
			addToList(tmp);
		}
	}
	std::sort(_output.begin(), _output.end());
	std::sort(_input.begin(), _input.end());

	linkAll();

	if (_components.empty())
		throw "You must create a component.";
	if (_links.empty())
		throw "You must create links.";
	if (_input.empty())
		throw "You must create an input.";
	if (_output.empty())
		throw "You must create an output.";
}

void nts::Parser::linkAll()
{
	for (std::vector<links>::iterator it = _links.begin(); it != _links.end(); it++) {
		if (inputExist((*it).getLink1()) && componentExist((*it).getLink2())) {
			Pin *first = getPinFromInputList((*it).getLink1());
			Pin *second = getPinFromComponentList((*it).getLink2(), (*it).getIdLink2());
			first->setLinkedTo(second);
			second->setLinkedTo(first);
		}
		if (inputExist((*it).getLink2()) && componentExist((*it).getLink1())) {
			Pin *first = getPinFromInputList((*it).getLink2());
			Pin *second = getPinFromComponentList((*it).getLink1(), (*it).getIdLink1());
			first->setLinkedTo(second);
			second->setLinkedTo(first);
		}
		if (componentExist((*it).getLink1()) && outputExist((*it).getLink2())) {
			Pin *first = getPinFromComponentList((*it).getLink1(), (*it).getIdLink1());
			Pin *second = getPinFromOutputList((*it).getLink2());
			first->setLinkedTo(second);
			second->setLinkedTo(first);
		}
		if (componentExist((*it).getLink2()) && outputExist((*it).getLink1())) {
			Pin *first = getPinFromComponentList((*it).getLink2(), (*it).getIdLink2());
			Pin *second = getPinFromOutputList((*it).getLink1());
			first->setLinkedTo(second);
			second->setLinkedTo(first);
		}
		if (componentExist((*it).getLink1()) && componentExist((*it).getLink2())) {
			Pin *first = getPinFromComponentList((*it).getLink2(), (*it).getIdLink2());
			Pin *second = getPinFromComponentList((*it).getLink1(), (*it).getIdLink1());
			second->setLinkedTo(first);
		}
	}
}

nts::Pin *nts::Parser::getPinFromInputList(std::string name)
{
	for (std::vector<Pin*>::iterator it = _input.begin(); it != _input.end(); it++) {
		if ((*it)->getName() == name) {
			return (*it);
		}
	}
	return nullptr;
}

nts::Pin *nts::Parser::getPinFromOutputList(std::string name)
{
	for (std::vector<Pin*>::iterator it = _output.begin(); it != _output.end(); it++) {
		if ((*it)->getName() == name) {
			return (*it);
		}
	}
	return nullptr;
}

nts::Pin *nts::Parser::getPinFromComponentList(std::string name, int id)
{
	for (std::vector<std::pair<IComponent*, std::string>>::iterator it = _components.begin(); it != _components.end(); it++) {
		if ((*it).second == name) {
			if (dynamic_cast<nts::C4071 *>((*it).first))
				return dynamic_cast<nts::C4071 *>((*it).first)->getPinById(id - 1);
			if (dynamic_cast<nts::C4081 *>((*it).first))
				return dynamic_cast<nts::C4081 *>((*it).first)->getPinById(id - 1);
			if (dynamic_cast<nts::C4011 *>((*it).first))
				return dynamic_cast<nts::C4011 *>((*it).first)->getPinById(id - 1);
			if (dynamic_cast<nts::C4030 *>((*it).first))
				return dynamic_cast<nts::C4030 *>((*it).first)->getPinById(id - 1);
			if (dynamic_cast<nts::C4001 *>((*it).first))
				return dynamic_cast<nts::C4001 *>((*it).first)->getPinById(id - 1);
			if (dynamic_cast<nts::C4069 *>((*it).first))
				return dynamic_cast<nts::C4069 *>((*it).first)->getPinById(id - 1);
		}
	}
	return nullptr;
}

std::string nts::Parser::clearLine(std::string line)
{
	size_t pos = line.find('#');
	if (pos != std::string::npos) {
		line.replace(pos, line.size() - pos, "");
	}
	int last = line.size() - 1;
	while (last >= 0 && (line[last] == ' ' || line[last] == '\t'))
		--last;
	return line.substr(0, last + 1);
}

const std::vector<std::pair<nts::IComponent*, std::string>> *nts::Parser::getComponents() const
{
	return &_components;
}

const std::vector<nts::Pin *> *nts::Parser::getOutput() const
{
	return &_output;
}

const std::vector<nts::Pin *> *nts::Parser::getInput() const
{
	return &_input;
}
