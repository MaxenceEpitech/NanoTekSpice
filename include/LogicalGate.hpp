/*
 ** EPITECH PROJECT, 2018
 ** NanoTekSpice
 ** File description:
 ** 	     @Author: killian @Date: 12:50:56 @File-name: LogicalGate
 */

#ifndef SRC_LOGICALGATE_HPP_
# define SRC_LOGICALGATE_HPP_

#include "IComponent.hpp"
#include "Pin.hpp"

namespace nts {
	enum GateType {
		AND, OR, NAND, NOR, XOR, NOT, XNOR
	};

	class LogicalGate {
	public:
		LogicalGate();
		LogicalGate(nts::GateType gate, nts::Pin *pin1, nts::Pin *pin2, nts::Pin *output);
		~LogicalGate();
		void evaluate();
		nts::Tristate getOutput() const;

	private:
		nts::GateType _type;
		nts::Pin *_input1;
		nts::Pin *_input2;
		nts::Pin *_output;
	};
}

#endif /* SRC_LOGICALGATE_HPP_ */
