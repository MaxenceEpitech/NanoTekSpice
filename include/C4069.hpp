/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice2
 ** File description :
 ** 	File Name : C4069.hpp Author : maxence.fourrier Date : 2 mars 2018
 */

#ifndef SRC_C4069_HPP_
#define SRC_C4069_HPP_

#include <string>

#include "LogicalGate.hpp"
#include "Pin.hpp"

namespace nts {
	class C4069: public nts::IComponent {
	public:
		C4069();
		~C4069();

		virtual nts::Tristate compute(std::size_t pin = 1) const;
		virtual void setLink(std::size_t pin, nts::IComponent &other,
				std::size_t otherPin);
		virtual void dump() const;
		virtual void simulate();
		nts::Pin *getPinById(size_t id);

	private:
		nts::Pin _pin[13];
		nts::LogicalGate _gates[6];
		std::size_t _size;
		std::string _name;
		std::size_t _nbGates;
	};
}
#endif /* SRC_C4069_HPP_ */
