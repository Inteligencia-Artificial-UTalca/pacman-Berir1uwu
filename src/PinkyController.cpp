#include "PinkyController.h"
#include <chrono>
#include <iostream>



class ConditionIsFrightened : public Behavior {
    PinkyController* con;
public:
    ConditionIsFrightened(PinkyController* c) : con(c) {}
    Status update() override {
        return BH_FAILURE; 
    }
}; 

class ActionGoToCorner : public Behavior {
    PinkyController* con;
public:
    ActionGoToCorner(PinkyController* c) : con(c) {}
    Status update() override {
        return BH_SUCCESS;
    }
};

class ActionPinkyAmbush : public Behavior {
    PinkyController* con;
public:
    ActionPinkyAmbush(PinkyController* c) : con(c) {}
    Status update() override {
        return BH_SUCCESS;
    }
}; 

PinkyController::PinkyController(std::shared_ptr<Character> character) :
    Controller(character) {
    setupBehaviorTree();
}

PinkyController::~PinkyController() {}

void PinkyController::setupBehaviorTree() {
    auto rootSelector = std::make_shared<Selector>();
    btRoot = rootSelector; 

    auto frightenedSeq = std::make_shared<Sequence>();
    frightenedSeq->addChild(std::make_shared<ConditionIsFrightened>(this));

    auto chaseSeq = std::make_shared<Sequence>();
    chaseSeq->addChild(std::make_shared<ActionPinkyAmbush>(this));

    auto scatterAction = std::make_shared<ActionGoToCorner>(this);

    rootSelector->addChild(frightenedSeq);
    rootSelector->addChild(chaseSeq);
    rootSelector->addChild(scatterAction);
}

Move PinkyController::getMove(const GameState& game) {
    auto start = std::chrono::high_resolution_clock::now(); 

    if (btRoot) {
        btRoot->tick(); 
    }

    auto end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> diff = end - start; 
    std::cout << "Time elapsed: " << diff.count() << " seconds" << std::endl; 

    return this->currentMove;
}