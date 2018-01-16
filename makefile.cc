#include "makefile.h"
#include <iostream>
#include <string>
using namespace std;


Makefile::Makefile(ostream &out) : out{ out } {
	this->global_time = 0;
	this->target_num = 0;
	this->arr_target = new Target*[maxTargets];
}

Makefile::~Makefile() {
	for (int i = 0; i < this->target_num; i++) {
		delete this->arr_target[i];
	}
	delete[] this->arr_target;
}

void Makefile::addDepend(const string &t, const string &d) {
	Target *my_target = nullptr;
	Target *my_dependency = nullptr;
	bool exist_target = false;
	bool exist_dependency = false;
	for (int i = 0; i < this->target_num; i++) {
		if (this->arr_target[i]->name == t) {
			exist_target = true;
			my_target = this->arr_target[i];
		}
		if (this->arr_target[i]->name == d) {
			exist_dependency = true;
			my_dependency = this->arr_target[i];
		}
	}
	if (!exist_target) {
		if (this->target_num == maxTargets) {
			this->out << "Max targets exceeded" << endl;
			return;
		}
		else {
			this->arr_target[this->target_num] = new Target(t, this->out);
			my_target = this->arr_target[this->target_num];
			(this->target_num)++;
		}
	}
	if (!exist_dependency) {
		if (this->target_num == maxTargets) {
			this->out << "Max targets exceeded" << endl;
			return;
		}
		else {
			this->arr_target[this->target_num] = new Target(d, this->out);
			my_dependency = this->arr_target[this->target_num];
			(this->target_num)++;
		}
	}
	my_target->addDepend(my_dependency);
}

void Makefile::changeTarget(const string &t) {
	Target *my_target = nullptr;
	bool exist_target = false;
	for (int i = 0; i < this->target_num; i++) {
		if (this->arr_target[i]->name == t) {
			exist_target = true;
			my_target = this->arr_target[i];
		}
	}
	(this->global_time)++;
	if (exist_target) {
		my_target->update(this->global_time);
	}
}

void Makefile::rebuild(const string &t) {
	Target *my_target = nullptr;
	bool exist_target = false;
	for (int i = 0; i < this->target_num; i++) {
		if (this->arr_target[i]->name == t) {
			exist_target = true;
			my_target = this->arr_target[i];
		}
	}
	if (exist_target) {
		my_target->build();
	}
}

