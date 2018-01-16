#include <iostream>
#include <fstream>
#include <string>
#include "makefile.h"
using namespace std;

int main() {
	ofstream of_myout{ "Myout.txt" };
  string s, t;
  Makefile m;
  Makefile n{ of_myout };
  while (cin >> s) {
    if (s[s.length() - 1] ==  ':') {  // Indicate dependency
      cin >> t;
      m.addDepend(s.substr(0, s.length() - 1), t);
	  n.addDepend(s.substr(0, s.length() - 1), t);
    }
    else if (s == "touch") { // Update leaf file
      cin >> t;
      m.changeTarget(t);
	  n.changeTarget(t);
    }
    else if (s == "make") { // Build target
      cin >> t;
      m.rebuild(t);
	  n.rebuild(t);
    }
    else if (s == "q") { // Quit
      break;
    }
  }
}
