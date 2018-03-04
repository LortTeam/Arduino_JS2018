#include "connection.h"
#include "neuron.h"

Connection::Connection(vertex first, vertex second)
{
    this->first = first;
    this->second = second;
    //count++;
    //id = count;
    age = 0;
}

Connection::~Connection()
{
    //delete first;
    //delete second;
}
void Connection::incAge()
{
	age++;
}

void Connection::setAge(int age)
{
	this->age = age;
}

//int Connection::getId(){
//	return id;
//}

int Connection::getAge()
{
	return age;
}

vertex Connection::getNeighbourNeuron(vertex node)
{
	return first == node ? second : first;
}


