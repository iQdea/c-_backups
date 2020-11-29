#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include "Storage.h"
#include "Backup.h"

using namespace std;

/**
 * Конкретные Стратегии реализуют алгоритм, следуя базовому интерфейсу
 * Стратегии. Этот интерфейс делает их взаимозаменяемыми в Контексте.
 */
class StorageSeparate : public Storage
{
public:
	StorageSeparate(string dirname) : Storage()
	{
		// добавим префикс, чтобы случайно не удалить что-то важное
		this->dirname = "backup_" + dirname;
	}
	
	void save(Backup& backup) override
    {
		remove_all(dirname);
		create_directory(dirname);

		ofstream fout(dirname + "/.paths");
		for (string path : backup.getPathList()) {
			fout << path << endl;
		}
		fout.close();

		auto pointList = backup.getPointList();
		fileNumber = 0;

		for (int i = 0; i < (int) pointList.size(); i++) {
			restorePointNumber = i + 1;
			pointList.at(i)->save();
		}
	}

	void save(RestorePoint& restorePoint) override {
		string rpPath = dirname + "/restore_point" + to_string(restorePointNumber);
		create_directory(rpPath);

		ofstream fout(rpPath + "/.date");
		fout << restorePoint.getDate() << endl;
		fout.close();

		fout.open(rpPath + "/.type");
		fout << (restorePoint.isFull() ? "full" : "inc") << endl;
		fout.close();

		for (File* file : restorePoint.getFileList()) {
			fileNumber++;

			string filePath = rpPath + "/file" + to_string(fileNumber);
			create_directory(filePath);

			fout.open(filePath + "/.path");
			fout << file->getName() << endl;
			fout.close();

			fout.open(filePath + "/.lastModified");
			fout << file->getLastModified() << endl;
			fout.close();

			fout.open(filePath + "/.size");
			fout << file->getSize() << endl;
			fout.close();
		}
	}
private:
	int fileNumber = 0;
	int restorePointNumber = 0;
	string dirname = "";
};
