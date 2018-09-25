/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice2
 ** File description :
 ** 	File Name : C4069.cpp Author : maxence.fourrier Date : 2 mars 2018
 */

#include <iostream>

#include "C4069.hpp"

nts::C4069::C4069()
		: _size(15), _name("4069"), _nbGates(6)
{
	_pin[0] = nts::Pin(nts::PinType::INPUT);
	_pin[1] = nts::Pin(nts::PinType::OUTPUT);
	_pin[2] = nts::Pin(nts::PinType::INPUT);
	_pin[3] = nts::Pin(nts::PinType::OUTPUT);
	_pin[4] = nts::Pin(nts::PinType::INPUT);
	_pin[5] = nts::Pin(nts::PinType::OUTPUT);
	_pin[6] = nts::Pin(nts::PinType::OUTPUT);//
	_pin[6].setValue(nts::Tristate::TRUE);
	_pin[7] = nts::Pin(nts::PinType::OUTPUT);
	_pin[8] = nts::Pin(nts::PinType::INPUT);
	_pin[9] = nts::Pin(nts::PinType::OUTPUT);
	_pin[10] = nts::Pin(nts::PinType::INPUT);
	_pin[11] = nts::Pin(nts::PinType::OUTPUT);
	_pin[12] = nts::Pin(nts::PinType::INPUT);
	_pin[13] = nts::Pin(nts::PinType::OUTPUT);//
	_gates[0] = nts::LogicalGate(nts::GateType::NOT, &_pin[0], &_pin[6], &_pin[1]);
	_gates[1] = nts::LogicalGate(nts::GateType::NOT, &_pin[2], &_pin[6], &_pin[3]);
	_gates[2] = nts::LogicalGate(nts::GateType::NOT, &_pin[4], &_pin[6], &_pin[5]);
	_gates[3] = nts::LogicalGate(nts::GateType::NOT, &_pin[8], &_pin[6], &_pin[7]);
	_gates[4] = nts::LogicalGate(nts::GateType::NOT, &_pin[10], &_pin[6], &_pin[9]);
	_gates[5] = nts::LogicalGate(nts::GateType::NOT, &_pin[12], &_pin[6], &_pin[11]);
}

nts::C4069::~C4069()
{
}

nts::Tristate nts::C4069::compute(std::size_t pin) const
{
	if (pin >= _size) {
		throw "Error: Pin index is out of bounds.";
	}
	return this->_pin[pin].getValue();
}

void nts::C4069::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
	if (pin >= this->_size) {
		throw "Error: Pin index is out of bounds.";
	}
	otherPin += 1;
	(void)other;
}

void nts::C4069::dump() const
{
	std::cout << "Chipset " << this->_name << std::endl;
	for (std::size_t i = 0; i < this->_size; i++) {
		std::cout << "\tpin #" << i + 1 << ": ";
		if (this->_pin[i].isLinked()) {
			try {
				std::cout << compute(i) << std::endl;
			} catch (std::exception &e) {

			}
		} else
			std::cout << "NULL" << std::endl;
	}
}

void nts::C4069::simulate()
{
	for (std::size_t i = 0; i < this->_nbGates; i++) {
		this->_gates[i].evaluate();
	}
}

nts::Pin* nts::C4069::getPinById(size_t id)
{
	return &(this->_pin[id]);
}
