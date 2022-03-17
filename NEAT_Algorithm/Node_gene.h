#pragma once
#include <set>
#include <vector>
#include "Connection_gene.h"

class Connection_gene;

class Node_gene {
private:
	double value;
	std::set<Connection_gene*> inputs;
	std::set<Connection_gene*> outputs;


public:
	Node_gene(double value);
	Node_gene(double value, std::set<Connection_gene*> inputs, std::set<Connection_gene*> outputs);

	Node_gene(const Node_gene& obj) {
		this->value = obj.value;
		for (auto it : obj.inputs) {
			this->inputs.insert(it);
		}
		for (auto it : obj.outputs) {
			this->outputs.insert(it);
		}
	}


	void set_value(double value);

	std::set<Connection_gene*> getoutputs();

	std::set<Connection_gene*> getinputs();

	double fastSigmoid(double value);

	double get_value();

	void setOutput(Node_gene* newOutput, double connectionValue, int innovationNumber);
	void setInput(Node_gene* newInput, double connectionValue, int innovationNumber);
	void setInputs(std::set<Connection_gene*> inputs);


	void printOutputs();
	void print();
};