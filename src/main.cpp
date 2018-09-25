/*
 ** EPITECH PROJECT, 2018
 ** NanoTekSpice
 ** File description:
 ** 	     @Author: killian @Date: 13:01:49 @File-name: main
 */

#include <iostream>
#include <string>

#include "Exception.hpp"
#include "Parser.hpp"
#include "ReadLoop.hpp"

int main(int ac, char **av)
{
	if (ac < 2) {
		std::cerr << "Wrong use: ./nanotekspice <CONFIG_FILE>"
				<< std::endl;
		return ERROR;
	}

	try {
		nts::ReadLoop read((std::string)av[1], av + 2);
	} catch (const char *error) {
		std::cerr << error << std::endl;
		return ERROR;
	}

	return SUCCESS;
}
