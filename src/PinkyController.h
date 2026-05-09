#pragma once

#include "Controller.h"
#include "BehaviorTree.h"


class PinkyController: public Controller {

public:
	PinkyController(std::shared_ptr<Character> character);
	virtual ~PinkyController();
	virtual Move getMove(const GameState& game)override;
private:
	void setupBehaviorTree();
	std::shared_ptr<Behavior> btRoot;
	Move currentMove = PASS;
};

