//
// Created by yonatan on 21/01/2020.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H


#include "State.h"
#include "AbstractSearcher.h"
#include "PriorityQueue.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <set>

template<class T>
class BestFS : public AbstractSearcher<T> {
private:
    PriorityQueue<T> *open;
    set<State<T>*> *closed;
    int numOfNodesEvaluated = 0;
public:
    BestFS<T>() {
        open = new PriorityQueue<T>(&this->numOfNodesEvaluated);
        closed = new set<State<T>*>();
    }

    virtual Solution<T>* search(Searchable<T> *searchable);

    Solution<T>* backTrace(State<T> *goalState, State<T> *initState);

    string checkDirection(State<Point*> *s1, State<Point*> *cameFrom1) {
        Point* s = s1->state;
        Point* cameFrom = cameFrom1->state;
        // x values equals
        if (s->getX() == cameFrom->getX()) {
            // Left
            if (s->getY() < cameFrom->getY()) {
                return "Left";
            } else { // Right
                return "Right";
            }
        }
        // y values equals
        if (s->getY() == cameFrom->getY()) {
            // Down
            if (s->getX() < cameFrom->getX()) {
                return "Up";
            } else { // Up
                return "Down";
            }
        }
        return "undefined move";
    }
};

template<class T>
Solution<T>* BestFS<T>::search(Searchable<T> *searchable) {
    open->push(searchable->getInitialState());
    // while open queue isn't empty
    while (!open->empty()) {
        State<T>* n = open->top();
        open->pop();
        closed->insert(n);
        //
        if (searchable->isGoalState(n)) {
            // backtrace, return the solution - path, according to the output text that we get
            Solution<T> *solution = backTrace(n, searchable->getInitialState());
            solution->setnumOfNodesEvaluated(this->numOfNodesEvaluated);
            return solution;
        }
        vector<State<T>*> *successors = searchable->getAllPossibleStates(n);
        int size = successors->size();
        for (int i = 0; i < size; ++i) {
            State<T> *s = successors->at(i);
            // if s is not in OPEN and not in CLOSED
            if (!(open->contain(s)) && (closed->find(s) == closed->end())) {
                s->cameFrom = n;
                s->cost += n->getCost();
                open->push(s);
            }
                // s in the open queue
                // relax
            else if (n->getCost() + s->value < s->cost) {
                s->cost = n->getCost() + s->value;
                s->cameFrom = n;
                // update key
                open->updateKey(s);
            }
        }
    }
}

template<class T>
Solution<T>* BestFS<T>::backTrace(State<T> *goalState, State<T> *initState) {
    // create empty Solution - vector of states
    auto *solution = new Solution<Point*>();
    // start from the goal, and check his cameFrom
    State<T> *s = goalState;
    // go back until the beginning
    // calculate for every node is next Move
    // insert to the solution from the end to beginning
    while (!(s->equals(initState))) {
        // insert the state to the beginning of the vector
        solution->getVectorOfStates()->insert(solution->getVectorOfStates()->begin(), s);
        // calculate for every node is next Move
        string direction = checkDirection(s, s->cameFrom);
        s->cameFrom->nextMove = direction;
        // go back in the trace
        s = s->cameFrom;
    }
    solution->getVectorOfStates()->insert(solution->getVectorOfStates()->begin(), s);
    return solution;
}


#endif //EX4_BESTFS_H
