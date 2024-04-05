#include "parse_tree.hpp"
#include "utility.hpp"

using namespace std;

ParseTree::ParseTree(string node_tagname, string filename)
{
    this->node_tagname = node_tagname;
    this->level = 0;
    string html = Utility::read_file(filename);
    build_tree(html);
}

ParseTree::ParseTree(string node_tagname, int level)
{
    this->node_tagname = node_tagname;
    this->level = level;
}

// Print the tagname, level and id of the node
void ParseTree::print_node()
{
    cout << "Tagname: "<< this->node_tagname << '\n' <<"Level: "<< this->level  << '\n' <<"ID: "<< this->id << '\n';
    return;
}

void ParseTree::build_tree(string html)
{
    parse_html(html);
}

void ParseTree::add_child(ParseTree *child)
{
    children.push_back(child);
}

void ParseTree::print_tree()
{
    cout << "<" << this->node_tagname << "\n";
    for (auto child : children)
    {
        child->print_tree();
    }
    cout << "</" << this->node_tagname << "\n";
    return;
}

void ParseTree::print_tree(int level)
{
    cout << "<" << node_tagname << "\n";
    for (auto child : children)
    {
        child->print_tree(level + 1);
    }
    cout << "</" << node_tagname << ">\n";
}

void ParseTree::parse_html(string html)
{
    int n = html.size();
    ParseTree *current_node = this;

    for (int i = 0; i < n; i++)
    {
        string tag = "";
        string tagname = "";

        if (i < n && html.substr(i, 2) == "</")
        {
            i += 2;
            while (i < n && html[i] != '>')
            {
                if (html[i] == '\n')
                {
                    i++;
                    continue;
                }
                tag += html[i];
                i++;
            }

            vector<string> tag_parts = Utility::separate_strings_by_char(tag, ' ');
            tagname = tag_parts[0];

            if (
                !this->tag_stack.empty() &&
                (tagname != this->tag_stack.top()->node_tagname)
            )
            {
                std::cerr << "Error: Invalid tag " << tagname << std::endl;
                throw "Invalid tag";
                exit(1);
            }

            this->tag_stack.pop(); // remove the current tag from the stack

            // update the current tag using the stack, the top is the new current
            if(!this->tag_stack.empty()){
                current_node = this->tag_stack.top();
            }
        }
        else if (html[i] == '<')
        {
            i++;
            while (i < n && html[i] != '>')
            {
                if (html[i] == '\n')
                {
                    i++;
                    continue;
                }
                tag += html[i];
                i++;
            }

            vector<string> tag_parts = Utility::separate_strings_by_char(tag, ' ');
            tagname = tag_parts[0];

            auto assingments = Utility::extractAssignments(tag_parts);

            // create a new node
            ParseTree *node = new ParseTree(tagname, current_node->level + 1);

            // assign node's attributes to it
            node->id = assingments["id"];

            if (Utility::is_single_ending_tag(tagname)) // if single ending tag, add to the current node
            {
                // add this child to the current node
                current_node->add_child(node);
                continue;
            }

            this->tag_stack.push(node);
            current_node->add_child(node);
            current_node = node;
        }
    }
    return;
}