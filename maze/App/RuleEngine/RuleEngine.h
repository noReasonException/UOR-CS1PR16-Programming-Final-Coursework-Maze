//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_RULEENGINE_H
#define MAZE_RULEENGINE_H


#include "../RawMap/RawMap.h"
#include "Rule.h"
#include "GenericRuleException.h"

class RuleEngine {
    RawMap*rawMap;
    std::vector<Rule*> rules;
    void initializeRules();
public:
    RuleEngine(RawMap *rawMap);
    virtual ~RuleEngine()= default;

    void applyActionObject(Action&);


};


#endif //MAZE_RULEENGINE_H
