#pragma once
#include "Rule.h"
class RuleSize :
    public Rule
{
public:
    RuleSize(unsigned int _size) : Rule() {
        size = _size;
    }
    virtual int getRemoveNeed(Backup& backup) override {
        vector<RestorePoint*>& list = backup.getPointList();
        unsigned int sumSize = 0;
        for (int i = (int) list.size() - 1; i >= 0; i--) {
            sumSize += list.at(i)->getFilesSize();
            if (sumSize > size) {
                return i + 1;
            }
        }
        return 0;
    }
private:
    unsigned int size;
};

