/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice
 ** File description :
 ** 	File Name : pin.cpp Author : maxence.fourrier Date : 13 févr. 2018
 */

#include <string>
#include "Pin.hpp"

nts::Pin::Pin(nts::PinType pinType)
		: linkedTo(nullptr), _name("Undefined_name"), _pinType(pinType), _value(nts::Tristate::UNDEFINED), _isLink(nts::Tristate::FALSE) , _clock(false)
{
}

nts::Pin::Pin(nts::PinType pinType, std::string name)
		: linkedTo(nullptr), _name(name), _pinType(pinType), _value(nts::Tristate::UNDEFINED), _isLink(nts::Tristate::FALSE), _clock(false)
{
}

nts::Pin::Pin(nts::PinType pinType, std::string name, bool isClock)
		: linkedTo(nullptr), _name(name), _pinType(pinType), _value(nts::Tristate::UNDEFINED), _isLink(nts::Tristate::FALSE), _clock(isClock)
{
}

nts::Pin::Pin()
		: linkedTo(nullptr), _pinType(nts::PinType::OUTPUT), _value(nts::Tristate::UNDEFINED), _isLink(nts::Tristate::FALSE), _clock(false)
{
}

nts::Pin::~Pin()
{
}

nts::PinType nts::Pin::getPinType() const
{
	return _pinType;
}

void nts::Pin::setPinType(nts::PinType pinType)
{
	_pinType = pinType;
}

nts::Tristate nts::Pin::getValue() const
{
	return _value;
}

void nts::Pin::setValue(nts::Tristate value)
{
	_value = value;
}

nts::Tristate nts::Pin::tristateFromBool(bool boolean)
{
	if (boolean)
		return nts::Tristate::TRUE;
	else
		return nts::Tristate::FALSE;
}

bool nts::Pin::isLinked() const
{
	return _isLink;
}

std::string nts::Pin::getName() const
{
	return _name;
}

void nts::Pin::setName(std::string name)
{
	_name = name;
}

nts::Pin *nts::Pin::getLinkedTo() const
{
	return linkedTo;
}

void nts::Pin::setLinkedTo(Pin *linkedTo)
{
	this->linkedTo = linkedTo;
}

bool nts::Pin::isClock() const
{
	return _clock;
}

void nts::Pin::setClock(bool clock)
{
	_clock = clock;
}
