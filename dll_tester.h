#ifndef DLL_TESTER_H
#define DLL_TESTER_H

#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "exception.h"
#include "double_linked_list.h"

using namespace std;

class DllTester {
public:
	DllTester();
	~DllTester();

	void readInput();

private:
	stack<DoubleLinkedList> lists;

	bool readNextLine(ifstream& fin, ofstream& fout);

	void addList();
	void copyList();
	void removeList();
	void pushFront(int val);
	string popFront();
	void pushBack(int val);
	string popBack();
	int size();
	void print(ofstream& fout);
	bool isEmpty();
	string find(int val);
	int count(int val);
	string swap();
	int erase(int val);
};

#endif

DllTester::DllTester() : lists() {

}

DllTester::~DllTester() {
	lists = stack<DoubleLinkedList>();
}

void DllTester::readInput() {
	ifstream fin;
	fin.open("input.txt");

	ofstream fout;
	fout.open("output.txt");

	while (readNextLine(fin, fout));

	fin.close();
	fout.close();
}

bool DllTester::readNextLine(ifstream& fin, ofstream& fout) {
	string inputLine;
	if (getline(fin, inputLine)) {
		stringstream ss(inputLine);

		string command = "";
		if (ss.good()) {
			ss >> command;
		
			if (command == "") return true;
			else if (command == "new") addList();
			else if (command == "exit") return false;
			else if (command == "copy") copyList();
			else if (command == "end") {
				removeList();
				if (lists.empty()) return false;
			}
			else if (command == "size") fout << size() << endl;
			else if (command == "print") print(fout);
			else if (command == "empty") fout << std::boolalpha << isEmpty() << endl;
			else if (command == "swap") fout << std::boolalpha << swap() << endl;
			else if (command == "pop_front") fout << popFront() << endl;
			else if (command == "pop_back") fout << popBack() << endl;
			else {
				int param;
				if (ss.good()) ss >> param;
				else throw IllegalArgument();
				
				if (command == "push_front") pushFront(param);
				else if (command == "push_back") pushBack(param);
				else if (command == "find") fout << find(param) << endl;
				else if (command == "count") fout << count(param) << endl;
				else if (command == "erase") fout << erase(param) << endl;
			}
			return true;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

void DllTester::addList() {
	DoubleLinkedList newList;
	lists.push(newList);
}

void DllTester::copyList() {
	DoubleLinkedList newList(lists.top());
	lists.push(newList);
}

void DllTester::removeList() {
	lists.pop();
}

void DllTester::pushFront(int val) {
	lists.top().pushFront(val);
}

string DllTester::popFront() {
	try {
		int val = lists.top().front();
		lists.top().popFront();
		return to_string(val);
	}
	catch (Underflow ex) {
		return "empty";
	}
	catch (Exception ex) {
		return "error";
	}
	return "none";
}

void DllTester::pushBack(int val) {
	lists.top().pushBack(val);
}

string DllTester::popBack() {
	try {
		int val = lists.top().back();
		lists.top().popBack();
		return to_string(val);
	}
	catch (Underflow ex) {
		return "empty";
	}
	catch (Exception ex) {
		return "error";
	}
	return "none";
}

int DllTester::size() {
	return lists.top().size();
}

void DllTester::print(ofstream& fout) {
	fout << lists.top() << endl;
}

bool DllTester::isEmpty() {
	return lists.top().empty();
}

string DllTester::find(int val) {
	DoubleLinkedList::DoubleNode* node = lists.top().find(val);
	if (node == nullptr) return "not-found";
	return to_string(node->value());
}

int DllTester::count(int val) {
	return lists.top().count(val);
}

string DllTester::swap() {
	if (lists.size() < 2) return "less than 2 lists";
	DoubleLinkedList list2 = lists.top();
	lists.pop();
	DoubleLinkedList list1 = lists.top();
	lists.pop();

	list1.swap(list2);

	lists.push(list1);
	lists.push(list2);
	return "swapped";
}

int DllTester::erase(int val) {
	return lists.top().erase(val);
}