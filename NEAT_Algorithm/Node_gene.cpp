#include "Node_gene.h"
#include <math.h>
#include <set>
#include <iostream>


Node_gene::Node_gene(double value) {
	this->value = value;
	this->inputs;
	this->outputs;
}

Node_gene::Node_gene(double value, std::set<Connection_gene*> inputs, std::set<Connection_gene*> outputs) {
	this->value = value;
	this->inputs = inputs;
	this->outputs = outputs;
}

std::set<Connection_gene*> Node_gene::getoutputs() {
	return this->outputs;
}

std::set<Connection_gene*> Node_gene::getinputs() {
	return this->inputs;
}

void Node_gene::setInputs(std::set<Connection_gene*> inputs) {
	this->inputs = inputs;
}

void Node_gene::setInput(Node_gene* newInput, double connectionValue, int innovationNumber) {
	Connection_gene newConnection(newInput, this, connectionValue, innovationNumber);
	newInput->outputs.insert(&newConnection);
	this->inputs.insert(&newConnection);

	//debug stuff bruh
	std::cout << innovationNumber << " " << inputs.size() << std::endl;
}

void Node_gene::setOutput(Node_gene* newOutput, double connectionValue, int innovationNumber) {
	Connection_gene newConnection(newOutput, this, connectionValue, innovationNumber);
	newOutput->inputs.insert(&newConnection);
	this->outputs.insert(&newConnection);
}



void Node_gene::set_value(double value) {
	this->value = value;
}

double Node_gene::fastSigmoid(double value){
	return value/(1+abs(value));
}

double Node_gene::get_value() {
	return this->value;
}

void Node_gene::print() {
	std::cout << "Node " << this->value;
}

void Node_gene::printOutputs() {

	std::cout << "Node " << this->value << " .Outputs are: ";

	for (Connection_gene* connection : outputs) {
		connection->getOutGene()->print();
	}

}


