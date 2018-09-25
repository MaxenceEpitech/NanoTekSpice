/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice2
 ** File description :
 ** 	File Name : C4081.hpp Author : maxence.fourrier Date : 2 mars 2018
 */

#ifndef SRC_C4081_HPP_
#define SRC_C4081_HPP_

#include <string>

#include "LogicalGate.hpp"
#include "Pin.hpp"

namespace nts {
	class C4081: public nts::IComponent {
	public:
		C4081();
		~C4081();

		virtual nts::Tristate compute(std::size_t pin = 1) const;
		virtual void setLink(std::size_t pin, nts::IComponent &other,
				std::size_t otherPin);
		virtual void dump() const;
		virtual void simulate();
		nts::LogicalGate getGateById(int id);
		nts::Pin *getPinById(size_t id);

	private:
		nts::Pin _pin[13];
		nts::LogicalGate _gates[4];
		std::size_t _size;
		std::string _name;
		std::size_t _nbGates;
	};
}
#endif /* SRC_C4081_HPP_ */
