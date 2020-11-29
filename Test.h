#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "Config.h"
#include "Backup.h"
#include "RestorePointFull.h"
#include "RestorePointInc.h"
#include "RuleCount.h"
#include "RuleDate.h"
#include "RuleSize.h"
#include "RuleCombo.h"

using namespace std;

class Test
{
public:
	Test() {}
	Test(FileSystem* fileSystem, Storage* storage = 0) { 
		this->backup = Backup(fileSystem, storage);
	};
	~Test() {}

	template<typename T> T getValue(string section, string param) {
		return config.lookup(section, param).getValue<T>();
	}

	void init(string filename) {
		config.readFile(filename);
		
		string path;
		stringstream paths(getValue<string>("Backup", "paths"));

		while (getline(paths, path, ':')) {
			backup.addPath(path);
		}

		string action;
		stringstream actions(getValue<string>("Backup", "actions"));

		while (getline(actions, action, ',')) {
			string actionType = getValue<string>(action, "type");

			cout << "Выполняется действие: " << action << " (" << actionType << ")" << endl << endl;
			try {
				if (actionType.find("point.") == 0) {
					backup.addRestorePoint(getRestorePoint(action, actionType));
				}
				else if (actionType.find("rule.") == 0) {
					Rule* rule = getRule(action, actionType);
					rule->apply(backup);
					free(rule);
				}
			}
			catch (exception excep) {
				cout << excep.what() << endl << endl;
			}
			backup.print();
			cout << endl;
		}

		backup.save();
	}
private:
	Backup backup;
	Config config;

	RestorePoint* getRestorePoint(string restorePointName, string restorePointType) {
		if (restorePointType == "point.full") {
			return new RestorePointFull(getValue<string>(restorePointName, "date"));
		}
		if (restorePointType == "point.inc") {
			return new RestorePointInc(getValue<string>(restorePointName, "date"));
		}
		throw invalid_argument("Неизвестный тип точки восстановления");
	}

	Rule* getRule(string ruleName, string ruleType) {
		if (ruleType == "rule.count") {
			return new RuleCount(getValue<unsigned int>(ruleName, "count"));
		}
		if (ruleType == "rule.date") {
			return new RuleDate(getValue<string>(ruleName, "date"));
		}
		if (ruleType == "rule.size") {
			return new RuleSize(getValue<unsigned int>(ruleName, "size"));
		}
		if (ruleType == "rule.combo.min" || ruleType == "rule.combo.max") {
			string subRuleName;
			stringstream subRuleNames(getValue<string>(ruleName, "rules"));
			RuleCombo* rule = new RuleCombo(ruleType == "rule.combo.min" ? ComboType::Min : ComboType::Max);

			while (getline(subRuleNames, subRuleName, ',')) {
				string subRuleType = getValue<string>(subRuleName, "type");
				rule->add(getRule(subRuleName, subRuleType));
			}

			return rule;
		}
		throw invalid_argument("Неизвестный тип алгоритма очистки");
	}
};

