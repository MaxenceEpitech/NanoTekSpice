/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice
 ** File description :
 ** 	File Name : Exception.hpp Author : maxence.fourrier Date : 13 févr. 2018
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <string>

#define ERROR 1
#define SUCCESS 0

namespace nts {
	class Exception: public std::exception {
	public:
		Exception();
		~Exception();

	private:

	};
}

#endif /* EXCEPTION_HPP_ */
