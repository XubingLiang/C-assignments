//
// Created by RyanLiang on 16/9/17.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <set>
#include <memory>
#include<algorithm>

namespace gdwg {

    //begin graph class
    template<typename N, typename E>
    class Graph {

        class Node;
        class Edge;

    public:
        //default constructor
        Graph();

        //copy && move constructor
        Graph(const Graph &old);
        Graph(Graph &&old);

        //copy && move assignment
        Graph &operator=(const Graph &old);
        Graph &operator=(Graph &&old);

        ////////////////////////////////
        bool addNode(const N &val);
        bool addEdge(const N &src, const N &dst, const E &w);
        bool replace(const N &oldData, const N &newData);
        void mergeReplace(const N &oldData, const N &newData);
        void deleteNode(const N &val) noexcept;
        void deleteEdge(const N &src, const N &dst, const E &w) noexcept;
        void clear() noexcept;
        bool isNode(const N &val) const;
        bool isConnected(const N &src, const N &dst) const;
        void printNodes() const;
        void printEdges(const N &val) const;

        //iterator functions
        void begin() const;
        bool end() const;
        void next() const;
        const N& value() const;

        //other functions
        auto getNode(const N &val) const;
        auto getNode(const N &val); 


    private:
        std::vector<std::shared_ptr<Node>> nodes;
        mutable typename std::vector<std::shared_ptr<Node>>::const_iterator graphitr;
        class Node {
        public:
            Node(const N &val) : nodePtr{std::make_shared<N>(val)} {};
            const N& getNodeVal() const { return *nodePtr; }
            std::shared_ptr<N> getnodePtr() const { return nodePtr; }
            void addEdge(const Node &to, const E &w);
            std::vector<std::shared_ptr<Edge>> getEdges(){return edges;}
            void setNodeVal(const N& val) {*nodePtr=val;}
            int numofedges(){return edges.size();}
            void printEdges();
            bool isEdge(const N &dst,const E &w)const;
            void removeEdge(const N &dst, const E &w);
            void removeExpired();


        private:
            std::vector<std::shared_ptr<Edge>> edges;
            std::shared_ptr<N> nodePtr;
        };

        class Edge {
        public:
            Edge(const Node &to, const E &w);
            E getWeight() const { return weight;}
            N& getdesNVal() const;
            void setdesN(std::shared_ptr<N> newN){desN = newN; };
            std::weak_ptr<N> getdesNPtr() {return desN;};
        private:
            E weight;
            std::weak_ptr<N> desN;
        };
    };

    #include "Graph.tem"
}


#endif //GRAPH_GRAPH_H
