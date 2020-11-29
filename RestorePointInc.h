#pragma once
#include "RestorePoint.h"

class RestorePointInc : public RestorePoint
{
public:
	RestorePointInc(string date) : RestorePoint(date) {}

	virtual bool isFull() const override {
		return false;
	}

	virtual void setParent(RestorePoint* parent) override {
		if (parent == 0)
			throw invalid_argument("Для инкрементальной точки восстановления нужна предыдущая точка");

		RestorePoint::setParent(parent);
	}

	virtual void create(FileList& fileList) override {
		for (File* file : fileList.getList()) {
			if (this->parent->getLastModified(file) < file->getLastModified()) {
				this->fileList.add(new File(*file));
			}
		}
	}
};

