#pragma once
#ifndef MYHEADER_H
#define MYHEADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

class ParseTree
{
public:
    // Constructors
    ParseTree(std::string node_tagname, std::string filename);
    ParseTree(std::string node_tagname, int level);

    // Public Methods
    void print_node();
    void build_tree(std::string html);
    void add_child(ParseTree *child);
    void print_tree();
    void print_tree(int level);

    std::vector<ParseTree *> getElementsByTagName(std::string tagname, ParseTree *root);

private:

    std::string node_tagname;
    int level;
    std::vector<ParseTree *> children;
    void parse_html(std::string html);

};

#endif // MYHEADER_H