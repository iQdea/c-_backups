#pragma once
#include "Rule.h"
class RuleCount :
    public Rule
{
public:
    RuleCount(unsigned int _count) {
        count = _count;
    }
    virtual int getRemoveNeed(Backup& backup) override {
        vector<RestorePoint *>& list = backup.getPointList();
        return (int) list.size() - count;
    }
private:
    unsigned int count;
};

