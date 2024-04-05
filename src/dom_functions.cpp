#include "parse_tree.hpp"
#include "utility.hpp"

using namespace std;

vector<ParseTree *> ParseTree::getElementsByTagName(string tagname, ParseTree *root)
{

    vector<ParseTree *> result;
    // level order traversal

    queue<ParseTree *> q;
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            ParseTree *current = q.front();
            q.pop();

            if (current->node_tagname == tagname)
            {
                result.push_back(current);
            }

            for (auto child : current->children)
            {
                q.push(child);
            }
        }
    }
    return result;
}

// Get DOM/ParseTree node by id from the DOM tree created after parsing the HTML string
ParseTree* ParseTree::getElementById(ParseTree* root, string id){
    // simple bfs search
    queue<ParseTree*> q;
    q.push(root);

    while(!q.empty()){
        ParseTree* current = q.front();
        q.pop();

        if(current->id == id){
            return current;
        }

        for(auto child: current->children){
            q.push(child);
        }
    }

    cout<<"RETURNING NULL\n";
    return nullptr;
}