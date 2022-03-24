#pragma once
#include "Node_gene.h"
#include "Connection_gene.h"
#include "Brain.h"
#include <set>
#include <vector>
#include <iostream>

int main() {

//	//creating inputs
//	std::vector<Node_gene*> inputGenes;
//
//	Node_gene* zero = new Node_gene(0.8);
//	Node_gene* one = new Node_gene(0.8);
//
//	inputGenes.push_back(zero);
//	inputGenes.push_back(one);
//
//
//
//	//creating hidden nodes
//	Node_gene* two = new Node_gene(0);
//
//	two->setInput(zero, 0.2, 1);
//	two->setInput(one, 0.3, 2);
//
//
//
//	Node_gene* three = new Node_gene(0);
//	three->setInput(zero, 0.5, 3);
//	three->setInput(two, 0.5, 4);
//
//
//	//creating output genes
//	std::vector<Node_gene*> outGenes;
//	Node_gene* four = new Node_gene(0);
//	four->setInput(three, 0.8, 5);
//
//	outGenes.push_back(four);
//
//
//	zero->name = "zero";
//	one->name = "one";
//	two->name = "two";
//	three->name = "three";
//	four->name = "four";
//
////	two->calculate(); //works
//
//
//	Brain* example = new Brain();
//	
//	example->setInput(inputGenes);
//	example->setOutput(outGenes);
//
//	std::vector<double> result = example->getOutput();
//
//
//	std::cout << "result is ";
//	for (auto it : result) {
//		std::cout << it << " ";
//	}

	Brain* example = new Brain();
	example->createDefault(10, 6, 2);


	//input example
	std::vector<int> input(10);
	for (int i = 0; i < 10; i++) {
		input[i] = i;
	}

	std::vector<double> result = example->feedForward(input);


	std::cout << "result is ";
	for (auto it : result) {
		std::cout << it << " ";
	}

}