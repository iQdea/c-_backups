#pragma once

#include <fstream>
#include <filesystem>
#include <string>

#include "Storage.h"
#include "Backup.h"

using namespace std;

/**
 * Конкретные Стратегии реализуют алгоритм, следуя базовому интерфейсу
 * Стратегии. Этот интерфейс делает их взаимозаменяемыми в Контексте.
 */
class StorageArchive : public Storage
{
public:
	StorageArchive(string filename) : Storage() {
		// добавим префикс, чтобы случайно не затереть важный файл
		this->filename = "backup_" + filename;
	}
    void save(Backup& backup) override
    {
		fout.open(filename.c_str());

		fout << "[Backup]" << endl << "paths=";
		bool first = true;
		vector<string>& pathList = backup.getPathList();
		for (string path : pathList) {
			if (first) first = false;
			else fout << ":";

			fout << path;
		}
		fout << endl << "points=";

		auto pointList = backup.getPointList();

		first = true;
		for (int i = 0; i < (int) pointList.size(); i++) {
			if (first) first = false;
			else fout << ",";

			fout << "RestorePoint" << (i + 1);
		}

		fout << endl;

		for (int j = 0; j < 2; j++) {
			fileNumber = 0;
			step = j + 1;
			for (int i = 0; i < (int) pointList.size(); i++) {
				restorePointNumber = i + 1;
				pointList.at(i)->save();
			}
		}

		fout.close();
	}

	void save(RestorePoint& restorePoint) override {
		if (step == 1) {
			fout << "[RestorePoint" << restorePointNumber << "]" << endl;
			fout << "date=" << restorePoint.getDate() << endl;
			fout << "type=" << (restorePoint.isFull() ? "full" : "inc") << endl;
			bool first = true;
			fout << "files=";
			for (File* file : restorePoint.getFileList()) {
				if (first) first = false; else fout << ",";
				fileNumber++;
				fout << "File" << fileNumber;
			}
			fout << endl;
		}

		if (step == 2) {
			for (File* file : restorePoint.getFileList()) {
				fileNumber++;
				fout << "[File" << fileNumber << "]" << endl;
				fout << "path=" << file->getName() << endl;
				fout << "size=" << file->getSize() << endl;
				fout << "lastModified=" << file->getLastModified() << endl;
			}
		}
	}
private:
	ofstream fout;
	int step = 0;
	int fileNumber = 0;
	int restorePointNumber = 0;
	string filename = "";
};
