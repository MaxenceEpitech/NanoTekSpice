/*
 ** EPITECH PROJECT, 2018
 ** NanoTekSpice
 ** File description:
 ** 	     @Author: killian @Date: 13:05:21 @File-name: IComponent
 */
#ifndef ICOMPONENT_HPP_
# define ICOMPONENT_HPP_

#include <cstddef>

namespace nts {
	enum Tristate {
		FALSE = false,
		UNDEFINED = (-true),
		TRUE = true
	};

	class IComponent {
	public:
		virtual ~IComponent() = default;
		virtual nts::Tristate compute(std::size_t pin = 1) const = 0;
		virtual void setLink(std::size_t pin, nts::IComponent &other,
				std::size_t otherPin) = 0;
		virtual void dump() const = 0;
		virtual void simulate() = 0;
	};
}

#endif /* ICOMPONENT_HPP_ */
