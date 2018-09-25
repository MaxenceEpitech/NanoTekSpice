/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice
 ** File description :
 ** 	File Name : pin.hpp Author : maxence.fourrier Date : 13 févr. 2018
 */

#ifndef SRC_PIN_HPP_
#define SRC_PIN_HPP_

#include <string>

#include "IComponent.hpp"

namespace nts {
	enum PinType {
		INPUT, OUTPUT
	};
	class Pin {
	public:
		Pin(nts::PinType pinType);
		Pin(nts::PinType, std::string name);
		Pin(nts::PinType, std::string name, bool isClock);
		Pin();
		~Pin();
		nts::PinType getPinType() const;
		void setPinType(nts::PinType pinType = nts::PinType::OUTPUT);
		nts::Tristate getValue() const;
		void setValue(nts::Tristate value = nts::Tristate::UNDEFINED);
		static nts::Tristate tristateFromBool(bool boolean);
		bool isLinked() const;
		std::string getName() const;
		void setName(std::string name);
		Pin *getLinkedTo() const;
		void setLinkedTo(Pin *linkedTo);
		bool isClock() const;
		void setClock(bool clock);

	private:
		Pin *linkedTo;
		std::string _name;
		nts::PinType _pinType;
		nts::Tristate _value = nts::Tristate::UNDEFINED;
		bool _isLink;
		bool _clock;
	};
}

#endif /* SRC_PIN_HPP_ */
