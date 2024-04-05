#include "parse_tree.hpp"

int main() {
    // File to read HTML from
    std::string filename = "../index.html";

    // Create a ParseTree object with root tagname "root" and parse the HTML file
    ParseTree* root = new ParseTree("root", filename);

    // root->print_tree();
    // Example usage: Get elements by tag name and print their node_tagname and level
    // auto result = root->getElementsByTagName("h1", root);
    // for(auto r: result){
    //     r->print_node();
    // // }

    std::string id = "tree";
    auto node = root->getElementById(root, id);
    node->print_node();
    // std::cout<<node->level<<std::endl;
    // root->print_tree();

    // Clean up
    delete root;

    return 0;
}
