/*
** EPITECH PROJECT , 2018
** NanoTekSpice2
** File description :
** 	File Name : Parser.hpp Author : maxence.fourrier Date : 15 févr. 2018
*/

#ifndef SRC_PARSER_HPP_
#define SRC_PARSER_HPP_

#include <string>
#include <utility>
#include <vector>

#include "IComponent.hpp"
#include "links.hpp"
#include "Pin.hpp"

namespace nts {
	#define ALPHANUMERICAL "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
	#define NUMBER "0123456789\t "

	class Parser {
	public:
		Parser(std::string fileName);
		~Parser();

		bool inputExist(std::string input);
		bool outputExist(std::string output);
		bool componentExist(std::string component);

		void setInputValue(std::string input, nts::Tristate trist);
		const std::vector<std::pair<nts::IComponent*, std::string>> *getComponents() const;
		const std::vector<nts::Pin *> *getOutput() const;
		const std::vector<nts::Pin *> *getInput() const;

		nts::Tristate getInputValue(std::string name);

		Pin *getPinFromInputList(std::string name);
		Pin *getPinFromOutputList(std::string name);
		Pin *getPinFromComponentList(std::string name, int id);
		void linkAll();

	private:
		std::vector<std::pair<nts::IComponent*, std::string>> _ptrComponent;
		std::vector<std::pair<nts::IComponent*, std::string>> _components;

		bool addToComponent(std::string line);
		void addToList(std::string line);
		void addChipset(std::string line);
		void addLink(std::string line);
		void read(std::string fileName);
		void checkLineError(std::string line);
		std::string clearLine(std::string line);
		std::string _fileContent;

		std::vector<nts::Pin *> _output;
		std::vector<nts::Pin *> _input;
		std::vector<nts::links> _links;

		bool _link;
		bool _chipset;
	};
}

#endif /* SRC_PARSER_HPP_ */
