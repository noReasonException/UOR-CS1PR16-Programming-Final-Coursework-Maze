//
// Created by stefan on 17/04/19.
//

#include "RuleEngine.h"

RuleEngine::RuleEngine(RawMap *_rawMap) : rawMap(_rawMap) {
    initializeRules();
}

void RuleEngine::initializeRules() {
    rules.push_back(new AvoidLevelLimits(rawMap));
    rules.push_back(new AvoidColission(rawMap));
    rules.push_back(new AvoidMoveOverOneBlockAway(rawMap));
}

void RuleEngine::applyActionObject(Action &ao) {
    for (Rule *r:rules)r->ruleCheck(ao);
}
