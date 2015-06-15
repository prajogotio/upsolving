#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <new>
using namespace std;

class StringParser {
public:
	StringParser(const string&);
	~StringParser(){}
	void parse();
	bool found();

private:
	string parsable;
	bool isFound;
	static const string lookupTable;

	class Automaton {
	public:
		Automaton();
		~Automaton() {}
		void consume(const char&);
		int getIndex();
	private:
		void transit();
		bool check(const char&);
		void reset();
		int currentIndex;
		bool isAlive;
	};
	friend class Automaton;
};

const string StringParser::lookupTable("CODEFORCES");
StringParser::StringParser(const string& str): parsable(str), isFound(false) {}
StringParser::Automaton::Automaton(): currentIndex(0), isAlive(true) {}

void StringParser::Automaton::transit() {
	++currentIndex;
}

bool StringParser::Automaton::check(const char& ch) {
	return ch == StringParser::lookupTable[currentIndex];
}

int StringParser::Automaton::getIndex() {
	return currentIndex;
}

void StringParser::Automaton::reset() {
	currentIndex = 0;
}

void StringParser::Automaton::consume(const char& ch) {
	if (!isAlive) return;
	if (currentIndex < StringParser::lookupTable.size() && check(ch)) {
		transit();
	} else {
		reset();
		isAlive = false;
	}
}

void StringParser::parse() {
	const string& str = this->parsable;
	int sz = str.size();
	for (int k = 0; k < sz; ++k) {
		for (int i = 0; i < sz; ++i) {
			Automaton a;
			for (int j = 0; j < sz; ++j) {
				if (i <= j && j < i+k) continue;
				a.consume(str[j]);
			}
			if (a.getIndex() == lookupTable.size()) isFound = true;
			if (isFound) return;
		}
	}
}


bool StringParser::found() {
	return this->isFound;
}

int main(){
	string toCheck;
	cin >> toCheck;
	StringParser sp(toCheck);
	sp.parse();
	if (sp.found()) printf("YES\n");
	else printf("NO\n");
	return 0;
}