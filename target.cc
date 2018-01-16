#include "target.h"
#include <string>
using namespace std;


bool Target::isLeaf() const {
	if (this->size == 0) {
		return true;
	}
	return false;
}

void Target::addDepend(Target *d) {
	bool exist = false;
	for (int i = 0; i < this->size; i++) {
		if (d == this->arr_d[i]) {
			exist = true;
		}
	}
	if (!exist) {
		if (this->size == maxDepends) {
			this->out << "Max dependencies exceeded" << endl;
		}
		else {
			this->arr_d[this->size] = d;
			(this->size)++;
		}
	}
}

Target::Target(const string &name, ostream &out = cout) :name{ name }, out{ out } {
	this->size = 0;
	this->arr_d = new Target*[maxDepends];
	this->local_time = 0;
}

Target::~Target() {
	delete[] this->arr_d;
}

void Target::update(int time) {
	if (isLeaf()) {
		this->local_time = time;
		this->out << this->name << " updated at time " << time << endl;
	}
	else {
		this->out << "Cannot update non-leaf object" << endl;
	}
}

int Target::lastUpdated() const {
	return this->local_time;
}

void Target::build() {
	bool update = false;
	for (int i = 0; i < this->size; i++) {
		this->arr_d[i]->build();
		if ((this->arr_d[i])->local_time > this->local_time) {
			update = true;
			this->local_time = (this->arr_d[i])->local_time;
		}
	}
	if (update) {
		this->out << "Building " << this->name << endl;
	}
}