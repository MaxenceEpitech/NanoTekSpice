/*
 ** EPITECH PROJECT, 2018
 ** NanoTekSpice
 ** File description:
 ** 	     @Author: killian @Date: 12:50:56 @File-name: LogicalGate
 */

#include "LogicalGate.hpp"

#include <iostream>

nts::LogicalGate::LogicalGate()
		: _type(nts::GateType::AND), _input1(nullptr), _input2(nullptr), _output(nullptr)
{
}

nts::LogicalGate::LogicalGate(nts::GateType type, nts::Pin *input1, nts::Pin *input2, nts::Pin *output)
		: _type(type), _input1(input1), _input2(input2), _output(output)
{
}

nts::LogicalGate::~LogicalGate()
{
}

nts::Tristate nts::LogicalGate::getOutput() const
{
	return this->_output->getValue();
}

void nts::LogicalGate::evaluate()
{
	if (this->_input1->getValue() == nts::Tristate::UNDEFINED || this->_input2->getValue() == nts::Tristate::UNDEFINED) {
		if (this->_type == nts::GateType::OR && (this->_input1->getValue() == nts::Tristate::TRUE || this->_input2->getValue() == nts::Tristate::TRUE)) {
			this->_output->setValue(nts::Tristate::TRUE);
		} else {
			this->_output->setValue(nts::Tristate::UNDEFINED);
		}
	} else {
		switch (this->_type) {
		case (nts::GateType::AND):
			this->_output->setValue(Pin::tristateFromBool(this->_input1->getValue() && this->_input2->getValue()));
			break;
		case (nts::GateType::NAND):
			this->_output->setValue(Pin::tristateFromBool(!(this->_input1->getValue() && this->_input2->getValue())));
			break;
		case (nts::GateType::NOR):
			this->_output->setValue(Pin::tristateFromBool(!(this->_input1->getValue() || this->_input2->getValue())));
			break;
		case (nts::GateType::NOT):
			this->_output->setValue(Pin::tristateFromBool(!(this->_input1->getValue())));
			break;
		case (nts::GateType::OR):
			this->_output->setValue(Pin::tristateFromBool((this->_input1->getValue() || this->_input2->getValue())));
			break;
		case (nts::GateType::XNOR):
			this->_output->setValue(Pin::tristateFromBool(!((this->_input1->getValue() || this->_input2->getValue()) && !(this->_input1->getValue() && this->_input2->getValue()))));
			break;
		case (nts::GateType::XOR):
			this->_output->setValue(Pin::tristateFromBool(((this->_input1->getValue() || this->_input2->getValue()) && !(this->_input1->getValue() && this->_input2->getValue()))));
			break;
		default:
			std::cerr << "Error while evaluating LogicalGate" << std::endl;
		}
	}
	if (this->_output->getLinkedTo() != nullptr) {
		this->_output->getLinkedTo()->setValue(this->_output->getValue());
	}
}
