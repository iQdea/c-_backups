#pragma once
#include <string>

using namespace std;

class File {
public:
	File(File& file) {
		name = file.getName();
		size = file.getSize();
		lastModified = file.getLastModified();
	}
	File(string _name, unsigned int _size, string _lastModified) {
		name = _name;
		size = _size;
		lastModified = _lastModified;
	}
	string getName() const {
		return name;
	}
	unsigned int getSize() const {
		return size;
	}
	string getLastModified() const {
		return lastModified;
	}
private:
	string name;
	unsigned int size;
	string lastModified;
};

