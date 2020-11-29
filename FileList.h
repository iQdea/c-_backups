#pragma once
#include <vector>
#include "File.h"

class FileList {
public:
	FileList() {}
	void add(File* file) {
		list.push_back(file);
	}
	~FileList() {
		for (File* file : list)
			free(file);
	}
	vector<File*> getList() const {
		return list;
	}
private:
	vector<File*> list;
};
