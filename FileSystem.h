#pragma once
#include <string>
#include "Config.h"
#include "FileList.h"

using namespace std;

class FileSystem
{
public:
	FileSystem() {}
	~FileSystem() {}
	void init(string filename) {
		config.readFile(filename);
	}
	void findFiles(const string& currDate, string currPath, FileList& fileList) {
		try {
			string path;
			stringstream paths(config.lookup(currPath, "paths").getValue<string>());

			while (getline(paths, path, ':')) {
				findFiles(currDate, currPath + "/" + path, fileList);
			}
		}
		catch (...) {}
		try {
			string dateSize;
			stringstream dateSizes(config.lookup(currPath, "size").getValue<string>());

			unsigned int currSize = 0;
			string lastModified = "";

			while (getline(dateSizes, dateSize, '|')) {
				string item;
				stringstream pair(dateSize);
				string date = "";
				unsigned int size = 0;
				int pos = 0;

				while (getline(pair, item, ':')) {
					pos++;

					if (pos == 1) date = item;
					else if (pos == 2) {
						stringstream ss(item);
						ss >> size;
					}
					else break;
				}

				//cout << date << " " << size << endl;
				if (date <= currDate && date > lastModified) {
					lastModified = date;
					currSize = size;
				}
			}
			fileList.add(new File(currPath, currSize, lastModified));
		}
		catch (...) {}
	}
private:
	Config config;
};

