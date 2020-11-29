#pragma once
#include "Backup.h"

class Rule
{
public:
    virtual int getRemoveNeed(Backup& backup) { return 0; };
    virtual void apply(Backup& backup) {
        int removeNeed = getRemoveNeed(backup);
        if (removeNeed <= 0) return;

        vector<RestorePoint*>& list = backup.getPointList();

        bool foundFull = 0;
        int removeCount = 0;

        for (int i = removeNeed; i >= 0; i--) {
            if (foundFull) {
                free(list.at(i));
                list.erase(list.begin() + i);
            }
            else if (list.at(i)->isFull()) {
                foundFull = 1;
                removeCount = i;
            }
        }
        if (removeCount == 0) {
            throw invalid_argument("Ќевозможно удалить ни одной точки восстановлени€");
        }
        else {
            if (removeCount != removeNeed) {
                stringstream ss;
                ss << "“ребовалось удалить " << removeNeed << " точек восстановлени€, удалено " << removeCount;
                string message;
                ss >> message;
                throw invalid_argument(message);
            }
        }
    }
};

