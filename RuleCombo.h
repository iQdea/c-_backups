#pragma once
#include "Rule.h"

enum class ComboType { Min = 0, Max };

class RuleCombo :
    public Rule
{
public:
    RuleCombo(ComboType _comboType) : Rule() {
        comboType = _comboType;
    }
    ~RuleCombo() {
        for (Rule* rule : list) {
            free(rule);
        }
    }
    void add(Rule* rule) {
        list.push_back(rule);
    }
    virtual int getRemoveNeed(Backup& backup) override {
        int result = 0;
        bool first = 1;

        for (Rule* rule : list) {
            int count = rule->getRemoveNeed(backup);
            if (first
                || count > result && comboType == ComboType::Min
                || count < result && comboType == ComboType::Max)
            {
                first = 0;
                result = count;
            }
        }

        return result;
    }
private:
    ComboType comboType;
    vector<Rule *> list;
};

