#pragma once
#include "RestorePoint.h"

class RestorePointFull : public RestorePoint
{
public:
	RestorePointFull(string date) : RestorePoint(date) {}

	virtual bool isFull() const override {
		return true;
	}

	virtual void setParent(RestorePoint* parent) override {
		RestorePoint::setParent(0);
	}

	virtual void create(FileList& fileList) override {
		for (File* file : fileList.getList()) {
			if (file->getSize() != 0) {
				this->fileList.add(new File(*file));
			}
		}
	}
};
