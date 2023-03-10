#include <iostream>
#include <random>
#include <fstream>
#include "array.cpp"

using namespace std;

#define X 130
#define Y 1
#define Z 1000

int main(){

    ofstream result("(130, 1, 1000)", ios::out);

    // a cycle with 1000 nodes
    int graph[V][V];
    for(int i=0; i<V; ++i){
        for(int j=0; j<V; ++j){
            if(i-j==1 || j-i==1) graph[i][j] = 1;
            else graph[i][j] = 0;
        }
    }
    graph[0][V-1] = 1;
    graph[V-1][0] = 1;

    random_device seed;
    default_random_engine generator(seed());
    uniform_int_distribution<int> vertex(0, V-1);

    // randomly add X=100 edges with the length of Y=1
    for(int i=0; i<X; ++i){
        int ver1 = vertex(generator);
        int ver2 = vertex(generator);
        if(ver1==ver2){
            --i;
            continue;
        }
        graph[ver1][ver2] = Y;
    }

    clock_t start, end;
    // randomly produce Z=1000 pairs of src and des to compute the shortest distance
    for(int i=0; i<Z; ++i){
        int src = vertex(generator);
        int des = vertex(generator);
        start = clock();
        int dis = dijkstra(graph, src, des);
        end = clock();
        result << (float)(end-start)/CLOCKS_PER_SEC << endl;
    }

    result.close();
    return 0;
}