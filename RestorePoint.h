#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "FileSystem.h"
#include "FileList.h"
#include "Storage.h"
#include <experimental/filesystem>

using namespace std::experimental::filesystem;

enum class TypeSaving { Archive = 0, Separate };
enum class PointType { Full = 0, Inc };

class RestorePoint {
public:
	RestorePoint(string date) {
		this->date = date;
	}

	void setStorage(Storage* storage) {
		this->storage = storage;
	}
	
	string getLastModified(File* _file) const {
		for (File* file : fileList.getList())
			if (file->getName() == _file->getName())
				return file->getLastModified();

		return (this->parent) ? this->parent->getLastModified(_file) : "";
	}

	virtual void setParent(RestorePoint* parent) {
		this->parent = parent;
	}

	virtual void create(FileList& _fileList) = 0;
	
	virtual bool isFull() const = 0;
	
	void print() {
		cout << "Точка восстановления от " << date << endl;
		for (File* file : fileList.getList()) {
			cout << "- " << file->getLastModified() << " " << file->getName() << " [" << file->getSize() << "]" << endl;
		}
	}
	
	string getDate() {
		return date;
	}
	
	int getFilesSize() {
		int sumSize = 0;
		for (File* file : fileList.getList()) {
			sumSize += file->getSize();
		}
		return sumSize;
	}
	
	void save() {
		if (storage) {
			storage->save(*this);
		}
	}

	vector<File*> getFileList() const {
		return fileList.getList();
	}
private:
	string date;
	PointType pointType;
protected:
	Storage* storage = 0;
	RestorePoint* parent = 0;
	FileList fileList;
};

