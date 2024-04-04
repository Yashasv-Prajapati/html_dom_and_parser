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

void ParseTree::print_node()
{
    cout << node_tagname << ' ' << level << endl;
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
    cout << "<" << node_tagname << ">\n";
    for (auto child : children)
    {
        child->print_tree();
    }
    cout << "</" << node_tagname << ">\n";
    return;
}

void ParseTree::print_tree(int level)
{
    cout << "<" << node_tagname << ">\n";
    for (auto child : children)
    {
        child->print_tree(level + 1);
    }
    cout << "</" << node_tagname << ">\n";
}

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

void ParseTree::parse_html(string html)
{
    int n = html.size();
    if (n <= 0)
        return;

    // tagname, last position of opening tag, first position of closing tag
    vector<pair<string, pair<int, int>>> tag_indices;

    // find all the starting tags position and their corresponding closing tag position in the html
    for (int i = 0; i < n; i++)
    {
        int start = i;
        int end = i;
        string tag = "";
        string front_tagname = "";

        if (html[i] == '<')
        {
            // start = i; // found start position of a tag
            i++;
            while (i < n && html[i] != '>')
            { // iterate to get the whole tag
                if (html[i] == '\n')
                {
                    i++;
                    continue;
                }
                tag += html[i];
                i++;
            }
            start = i;
            vector<string> tag_parts = Utility::separate_strings_by_char(tag, ' ');
            front_tagname = tag_parts[0];

            // check if the tag is a double ending tag
            bool double_ending = Utility::is_double_ending_tag(front_tagname);

            if (!double_ending)
            {
                continue;
            }

            // find the corresponding closing tag and check if the tagname is the same as the front tagname, like <body> matches with </body>
            while (i + 2 < n && (html.substr(i, 2) != "</" || html.substr(i + 2, front_tagname.size()) != front_tagname))
            {
                i++;
            }

            end = i;
            i++;
            tag_indices.push_back({tag, {start, end}});
        }
    }

    for (auto t : tag_indices)
    {
        string tag = t.first;
        int start = t.second.first + 1;
        int end = t.second.second - 1;

        vector<string> tag_parts = Utility::separate_strings_by_char(tag, ' ');
        string tagname = tag_parts[0];

        if (Utility::is_double_ending_tag(tagname))
        {
            // create a new node with the tagname
            ParseTree *node = new ParseTree(tagname, level + 1);
            ParseTree::add_child(node);
            // recursively parse the html content inside the tag
            node->parse_html(html.substr(start, end - start + 1));
        }
        else if (Utility::is_single_ending_tag(tagname))
        {
            // create a new node with the tagname
            ParseTree *node = new ParseTree(tagname, level + 1);
            ParseTree::add_child(node);
            // recursively parse the html content inside the tag
            node->parse_html(html.substr(start, end - start + 1));
        }
        else
        {
            std::cerr << "Error: Invalid tag " << tagname << std::endl;
            throw "Invalid tag";
            exit(1);
        }
    }
    return;
}

