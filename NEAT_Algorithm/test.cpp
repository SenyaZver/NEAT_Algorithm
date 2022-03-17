#pragma once
#include "Node_gene.h"
#include "Connection_gene.h"
#include "Brain.h"
#include <set>
#include <vector>
#include <iostream>

int main() {
	//note: connection genes leak memory


	//consider: constructor for Node_gene takes copies of the values instad of references
	//which makes impossible writing something like:
	//inputGenes.push_back(new Node_gene(0.8, new std::set<Connection_gene>, new std::set<Connection_gene>));
	//is this bad? //edit, fixed


	//creating inputs
	std::vector<Node_gene*> inputGenes;

	Node_gene* zero = new Node_gene(0.8);
	Node_gene* one = new Node_gene(0.8);

	inputGenes.push_back(zero);
	inputGenes.push_back(one);



	//creating hidden nodes
	Node_gene* two = new Node_gene(0);

	two->setInput(zero, 0.2, 1);
	two->setInput(one, 0.3, 2);



	Node_gene* three = new Node_gene(0);
	three->setInput(zero, 0.5, 3);
	three->setInput(two, 0.5, 4);


	//creating output genes
	std::vector<Node_gene*> outGenes;
	Node_gene* four = new Node_gene(0);
	four->setInput(three, 0.8, 5);

	outGenes.push_back(four);



	three->printOutputs();
	std::cout << std::endl;

	for (auto it : inputGenes) {
		it->printOutputs();
		std::cout << std::endl;
	}


//	Brain example()


}