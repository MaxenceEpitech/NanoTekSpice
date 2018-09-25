/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice
 ** File description :
 ** 	File Name : C4071.hpp Author : maxence.fourrier Date : 13 févr. 2018
 */

#ifndef SRC_C4071_HPP_
#define SRC_C4071_HPP_

#include <cstddef>
#include <string>

#include "IComponent.hpp"
#include "LogicalGate.hpp"
#include "Pin.hpp"

namespace nts {
	class C4071 : public nts::IComponent {
	public:
		C4071();
		~C4071();

		virtual nts::Tristate compute(std::size_t pin = 1) const;
		virtual void setLink(std::size_t pin, nts::IComponent &other,
				std::size_t otherPin);
		virtual void dump() const;
		virtual void simulate();
		nts::Pin *getPinById(size_t id);

	private:
		nts::Pin _pin[13];
		nts::LogicalGate _gates[4];
		std::size_t _size;
		std::string _name;
		std::size_t _nbGates;
	};
}

#endif /* SRC_C4071_HPP_ */
