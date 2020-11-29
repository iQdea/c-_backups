#pragma once
#include <string>
#include "Rule.h"

using namespace std;

class RuleDate :
    public Rule
{
public:
    RuleDate(string _date) : Rule() {
        date = _date;
    }
    virtual int getRemoveNeed(Backup& backup) override {
        vector<RestorePoint*>& list = backup.getPointList();
        for (int i = 0; i < (int) list.size(); i++) {
            if (list.at(i)->getDate() >= date) {
                return i;
            }
        }
        return 0;
    }
private:
    string date;
};

