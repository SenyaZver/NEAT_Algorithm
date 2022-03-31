#pragma once
#include <set>
#include <vector>
#include "Connection_gene.h"
#include <string>

class Connection_gene;

class Node_gene {
private:
	double value;
	std::set<Connection_gene*> inputs;		//can there be memory leaks due to sets not neing pointers?
	std::set<Connection_gene*> outputs;


public:
	Node_gene(double value);
	Node_gene(double value, std::set<Connection_gene*> inputs, std::set<Connection_gene*> outputs);

	Node_gene(const Node_gene& obj) {	//TODO get this into cpp
		this->value = obj.value;
		for (auto it : obj.inputs) {
			this->inputs.insert(it);
		}
		for (auto it : obj.outputs) {
			this->outputs.insert(it);
		}
	}


	void setValue(double value);
	double getValue();


	std::set<Connection_gene*> getOutConnections();
	std::set<Connection_gene*> getInConnections();

	std::set<Node_gene*> getInputGenes();
	std::set<Node_gene*> getOutputGenes();

	double fastSigmoid(double value);


	void setOutput(Node_gene* newOutput, double connectionValue, int innovationNumber);
	void setInput(Node_gene* newInput, double connectionValue, int innovationNumber);

	void setInputs(std::set<Connection_gene*> inputs);

	void calculate();


	//debug functions
	void printOutputs();
	void printInputs();
	void print();
};