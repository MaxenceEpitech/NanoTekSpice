/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice2
 ** File description :
 ** 	File Name : C4011.cpp Author : maxence.fourrier Date : 2 mars 2018
 */

#include <iostream>

#include "C4011.hpp"

nts::C4011::C4011()
		: _size(13), _name("4011"), _nbGates(4)
{
	_pin[0] = nts::Pin(nts::PinType::INPUT);
	_pin[1] = nts::Pin(nts::PinType::INPUT);
	_pin[2] = nts::Pin(nts::PinType::OUTPUT);
	_pin[3] = nts::Pin(nts::PinType::OUTPUT);
	_pin[4] = nts::Pin(nts::PinType::INPUT);
	_pin[5] = nts::Pin(nts::PinType::INPUT);
	_pin[6] = nts::Pin(nts::PinType::INPUT);//
	_pin[7] = nts::Pin(nts::PinType::INPUT);
	_pin[8] = nts::Pin(nts::PinType::INPUT);
	_pin[9] = nts::Pin(nts::PinType::OUTPUT);
	_pin[10] = nts::Pin(nts::PinType::OUTPUT);
	_pin[11] = nts::Pin(nts::PinType::INPUT);
	_pin[12] = nts::Pin(nts::PinType::INPUT);
	_gates[0] = nts::LogicalGate(nts::GateType::NAND, &_pin[0], &_pin[1],
			&_pin[2]);
	_gates[1] = nts::LogicalGate(nts::GateType::NAND, &_pin[4], &_pin[5],
			&_pin[3]);
	_gates[2] = nts::LogicalGate(nts::GateType::NAND, &_pin[7], &_pin[8],
			&_pin[9]);
	_gates[3] = nts::LogicalGate(nts::GateType::NAND, &_pin[11], &_pin[12],
			&_pin[10]);
}

nts::C4011::~C4011()
{
}

nts::Tristate nts::C4011::compute(std::size_t pin) const
{
	if (pin >= _size) {
		throw "Error: Pin index is out of bounds.";
	}
	return this->_pin[pin].getValue();
}

void nts::C4011::setLink(std::size_t pin, nts::IComponent &other,
		std::size_t otherPin)
{
	if (pin >= this->_size) {
		throw "Error: Pin index is out of bounds.";
	}
	otherPin += 1;
	(void)other;
}

void nts::C4011::dump() const
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

void nts::C4011::simulate()
{
	for (std::size_t i = 0; i < this->_nbGates; i++) {
		this->_gates[i].evaluate();
	}
}

nts::Pin* nts::C4011::getPinById(size_t id)
{
	return &(this->_pin[id]);
}
