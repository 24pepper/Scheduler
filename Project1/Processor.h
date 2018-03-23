/*
 * Processor.h
 *
 *  Created on: Feb 26, 2018
 *      Author: KevinBeshears
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <string>

using namespace std;

class Processor {
public:
	Processor(){
		name = "";
	}
	Processor(int name){
		this->name = "Processor " + to_string(name);
	}

	string getName(){
		return name;
	}

    friend ostream &operator<<(ostream &stream, Processor p){
    		stream<<p.getName();
    		return stream;
    }

private:
	string name;

};


#endif /* PROCESSOR_H_ */
