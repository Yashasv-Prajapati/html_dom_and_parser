#include "html.hpp"

using namespace std;

class DOMTree
{
public:
    string tagname;
    vector<DOMTree *> children;
    DOMTree(string tagname, string filename){
        this->tagname = tagname;
        string html = read_file(filename);
        build_tree(html);
    }
    DOMTree(string tagname)
    {
        this->tagname = tagname;
    }

    void build_tree(string html)
    {
        parse_html(html);
    }

    void add_child(DOMTree *child)
    {
        children.push_back(child);
    }

    void print_tree()
    {
        cout << "<" << tagname << ">\n";
        for (auto child : children)
        {
            child->print_tree();
        }
        cout << "</" << tagname << ">\n";
        return;
    }

    void print_tree(int level)
    {
        cout << "<" << tagname << ">\n";
        for (auto child : children)
        {
            child->print_tree(level + 1);
        }
        cout << "</" << tagname << ">\n";
    }


private:
    string read_file(string filename){

        ifstream file(filename);
        string line;
        string html = "";
        while(getline(file, line)){
            html += line;
            html.push_back('\n');
        }
        return html;
    }

    void parse_html(string html)
    {
        int n = html.size();
        if(n <= 0) return ;

        // tagname, last position of opening tag, first position of closing tag
        vector<pair<string, pair<int,int>>> tag_indices;

        // find all the starting tags position and their corresponding closing tag position in the html
        for(int i=0; i<n; i++){
            int start = i;
            int end = i;
            string tag = "";
            string front_tagname = "";

            if(html[i]=='<'){
                // start = i; // found start position of a tag
                i++;
                while(i<n && html[i]!='>'){ // iterate to get the whole tag
                    if(html[i]=='\n'){
                        i++;
                        continue;
                    }
                    tag += html[i];
                    i++;
                }
                start = i;
                vector<string> tag_parts = separate_strings_by_char(tag, ' ');
                front_tagname = tag_parts[0];

                // check if the tag is a double ending tag
                bool double_ending = is_double_ending_tag(front_tagname);

                if(!double_ending){
                    continue;
                }

                // find the corresponding closing tag and check if the tagname is the same as the front tagname, like <body> matches with </body>
                while(i+2<n && (html.substr(i,2)!="</" || html.substr(i+2, front_tagname.size())!=front_tagname)){
                    i++;
                }

                end = i;
                i++;
                tag_indices.push_back({tag,{start, end}});
            }
        }

        for(auto t: tag_indices){
            string tag = t.first;
            int start = t.second.first+1;
            int end = t.second.second-1;

            vector<string> tag_parts = separate_strings_by_char(tag, ' ');
            string tagname = tag_parts[0];

            if(is_double_ending_tag(tagname)){
                // create a new node with the tagname
                DOMTree* node = new DOMTree(tagname);
                add_child(node);
                // recursively parse the html content inside the tag
                node->parse_html(html.substr(start, end-start+1));
            }else if(is_single_ending_tag(tagname)){
                // create a new node with the tagname
                DOMTree* node = new DOMTree(tagname);
                add_child(node);
                // recursively parse the html content inside the tag
                node->parse_html(html.substr(start, end-start+1));
            }else{
                std::cerr<<"Error: Invalid tag "<<tagname<<std::endl;
                throw "Invalid tag";
                exit(1);
            }
        }
        return;
    }

    stack<string> append_stacks(stack<string> to, stack<string> from)
    {

        stack<string> temporary_st;
        while (!from.empty())
        {
            cout << from.top() << endl;
            temporary_st.push(from.top());
            from.pop();
        }

        while (!temporary_st.empty())
        {
            cout << temporary_st.top() << endl;
            to.push(temporary_st.top());
            temporary_st.pop();
        }

        return to;
    }

    // function to check if the tag is a double ending tag
    bool is_double_ending_tag(string tag)
    {
        for (auto t : double_ending_html_tags)
        {
            if (t == tag)
            {
                return true;
            }
        }
        return false;
    }

    // function to check if the tag is a single ending tag
    bool is_single_ending_tag(string tag)
    {
        for (auto t : single_ending_html_tags)
        {
            if (t == tag)
            {
                return true;
            }
        }
        return false;
    }

    bool is_assignment_expression(string expr)
    {
        // check if the expression is an assignment expression
        bool check = expr.find("="); // very trivial check
        return check;
    }

    vector<string> separate_strings_by_char(string expr, char ch)
    {
        vector<string> result;
        string temp = "";

        for (auto c : expr)
        {
            if (c == ch)
            {
                result.push_back(temp);
                temp = "";
            }
            else
            {
                temp += c;
            }
        }
        result.push_back(temp);
        return result;
    }
};



int main()
{
#ifndef READ_FROM_FILE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif


    string filename;
    cin>>filename;
    DOMTree *root = new DOMTree("root", filename);
    root->print_tree();

    return 0;
}