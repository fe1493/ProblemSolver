#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "PriorityQueue.h"
#include "MyClientHandler.h"
#include "State.h"
#include "BestFS.h"
#include <string>


int main(int argc, char** argv)
{
    server_side::Server* server = new MySerialServer();
    CacheManager<vector<string>*, string>* cacheManager = new FileCacheManager<vector<string>*,string>();
    Solver<vector<string>*,string>* solver = new MatrixSolver<vector<string>*,string>(new BestFS<Point>());
    ClientHandler* clientHandler = new MyClientHandler(solver, cacheManager);
    int port = stoi(argv[1]);
    server->open(port, clientHandler);
//    int a = 0;
//    int* b = &a;
//    auto* queue = new PriorityQueue<int>(b);
//    auto* s = new State<int>();
//    s->cost = 5;
//    auto* s2 = new State<int>();
//    s2->cost = 10;
//    queue->push(s);
//    queue->push(s2);
//    queue->pop();
//    cout << queue->top()->getCost() << endl;
}

