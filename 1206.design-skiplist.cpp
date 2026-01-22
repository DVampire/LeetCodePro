#
# @lc app=leetcode id=1206 lang=cpp
#
# [1206] Design Skiplist
#
#include <vector>
#include <random>
#include <iostream>
using namespace std;
// @lc code=start
class Skiplist {
private:
    struct Node {
        int val;
        vector<Node*> forward;
        Node(int v, int level) : val(v), forward(level, nullptr) {}
    };
    const int MAX_LEVEL = 16; // enough for up to ~65k elements
    Node* head;
    int curMaxLevel;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    
    int randomLevel() {
        // returns a random level between 1 and MAX_LEVEL inclusive
        // geometric distribution with p=0.5
        int lvl = 1;
        while ((dist(rng) < 0.5) && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }
public:
    Skiplist() : curMaxLevel(1), rng(std::random_device{}()), dist(0.0, 1.0) {
        head = new Node(-1, MAX_LEVEL); // dummy head with value -1
    }
    
    ~Skiplist() {
        // clean up all nodes
        Node* curr = head->forward[0];
        while (curr) {
            Node* tmp = curr->forward[0];
            delete curr;
            curr = tmp;
        }
        delete head;
    }
    
    bool search(int target) {
        Node* cur = head;
        for (int i = curMaxLevel - 1; i >= 0; --i) {
            while (cur->forward[i] && cur->forward[i]->val < target)                cur = cur->forward[i];        }        cur = cur->forward[0];        return cur && cur->val == target;    }        void add(int num) {        vector<Node*> update(MAX_LEVEL, nullptr);        Node* cur = head;        // find predecessors at each layer        for (int i = curMaxLevel - 1; i >= 0; --i) {            while (cur->forward[i] && cur->forward[i]->val < num)                cur = cur->forward[i];            update[i] = cur;	}	// generate random level for new nod	int newLevel = randomLevel();	if(newLevel > curMaxLeve	{		for(int i=curMaxLeve;i<newLeve;i++)			update[i]=head		curMaxLeve=newLeve	}	Node* newNode=new Nod(numnewLeve	for(int i=0;i<newLeve;i++)	{		newNode->forwar[i]=update[i]->forwar[		update[		update[	}	}	bool erase(int num){	vector<Node*> updat(MAX_LEVE nullptr)	Node* cu=head	for(int i=curMaxLeve-1;i>=0;i--{	while(cu->forwar[	cu=cu->forwar[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	upt[	t}	t}	t}	t}	t}	t}	t}	t}	t}	t}	t}	t}}
t}