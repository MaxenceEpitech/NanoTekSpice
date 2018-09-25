/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice2
 ** File description :
 ** 	File Name : links.cpp Author : maxence.fourrier Date : 1 mars 2018
 */

#include <iostream>

#include "links.hpp"

nts::links::links()
	: _idLink1(0), _idLink2(0), _link1(""), _link2("")
{
}

nts::links::links(size_t idLink1, size_t idLink2, std::string link1,
		std::string link2)
	: _idLink1(idLink1), _idLink2(idLink2), _link1(link1), _link2(link2)
{
}

void nts::links::print()
{
	std::cout << "id link 1 " << _idLink1 << std::endl;
	std::cout << "id link 2 " << _idLink2 << std::endl;
	std::cout << "link 1 " << _link1 << std::endl;
	std::cout << "link 2 " << _link2 << std::endl;
}

nts::links::~links()
{
}

size_t nts::links::getIdLink1() const
{
	return _idLink1;
}

size_t nts::links::getIdLink2() const
{
	return _idLink2;
}

const std::string& nts::links::getLink1() const
{
	return _link1;
}

const std::string& nts::links::getLink2() const
{
	return _link2;
}

void nts::links::setIdLink1(size_t idLink1)
{
	_idLink1 = idLink1;
}

void nts::links::setIdLink2(size_t idLink2)
{
	_idLink2 = idLink2;
}

void nts::links::setLink1(const std::string& link1)
{
	_link1 = link1;
}

void nts::links::setLink2(const std::string& link2)
{
	_link2 = link2;
}
