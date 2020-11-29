#pragma once
#include <vector>
#include <string>
#include "FileList.h"
#include "FileSystem.h"
#include "RestorePoint.h"
#include "Storage.h"

using namespace std;

class Backup
{
public:
	Backup() {}
	Backup(FileSystem* fileSystem, Storage* storage = 0) {
		this->fileSystem = fileSystem;
		this->storage = storage;
	}
	~Backup() {
		for (RestorePoint* rp : pointList) {
			delete rp;
		}
	}
	void addPath(string path) {
		pathList.push_back(path);
	}
	void addRestorePoint(RestorePoint* restorePoint) {
		restorePoint->setParent(pointList.empty() ? 0 : pointList.back());
		restorePoint->setStorage(storage);

		FileList fileList;
		findFiles(restorePoint->getDate(), fileList);
		restorePoint->create(fileList);

		pointList.push_back(restorePoint);
	}
	void print() {
		for (RestorePoint* rp : pointList) {
			rp->print();
		}
	}
	vector<string>& getPathList() {
		return pathList;
	}
	vector<RestorePoint*>& getPointList() {
		return pointList;
	}
	/**
		������ ����, ����� �������������� ������������� ������������� ������
		���������, �������� ���������� ��������� ������ ������� ���������.
	*/
	void save() {
		if (this->storage) {
			this->storage->save(*this);
		}
	}

	void findFiles(const string& date, FileList& fileList) {
		for (string path : pathList) {
			this->fileSystem->findFiles(date, path, fileList);
		}
	}
private:
	vector<RestorePoint*> pointList;
	vector<string> pathList;
	/**
		�������� ������ ������ �� ���� �� �������� ���������.
		�������� �� ����� ����������� ������ ���������. �� ������ �������� ��
		����� ����������� ����� ��������� ���������.
	*/
	Storage* storage = 0;
	FileSystem* fileSystem = 0;
};
