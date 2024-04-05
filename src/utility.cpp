#include "utility.hpp"
#include <fstream>

using namespace std;

std::string Utility::read_file(const std::string filename)
{
    ifstream file(filename);
    std::string str;
    std::string file_contents;
    while (getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }
    return file_contents;
}

std::vector<std::string> Utility::separate_strings_by_char(const std::string expr, char ch)
{
    std::vector<std::string> result;
    std::string temp = "";

    for (auto c : expr)
    {
        if (c == ch)
        {
            result.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(c);
        }
    }
    result.push_back(temp);
    return result;
}

bool Utility::is_assignment_expression(const std::string expr)
{
    // check if the expression is an assignment expression
    bool check = expr.find("="); // very trivial check
    return check;
}

bool Utility::is_double_ending_tag(const std::string tag)
{
    for (int i = 0; i < DOUBLE_ENDING_TAGS; i++)
    {
        if(tag == double_ending_html_tags[i])
        {
            return true;
        }
    }

    return false;
}

bool Utility::is_single_ending_tag(const std::string tag)
{
    for (int i = 0; i < SINGLE_ENDING_TAGS; i++)
    {
        if(tag == single_ending_html_tags[i])
        {
            return true;
        }
    }

    return false;
}

std::stack<std::string> Utility::append_stacks(stack<std::string> to, stack<std::string> from)
{
    stack<std::string> temporary_st;
    while (!from.empty())
    {
        std::cout << from.top() << std::endl;
        temporary_st.push(from.top());
        from.pop();
    }

    while (!temporary_st.empty())
    {
        std::cout << temporary_st.top() << std::endl;
        to.push(temporary_st.top());
        temporary_st.pop();
    }

    return to;
}

std::map<std::string, std::string> Utility::extractAssignments(const std::vector<std::string> assignments) {
    std::map<std::string, std::string> extractedAssignments;

    for (const std::string& assignment : assignments) {
        // Find the position of '=' in the assertion
        size_t equalSignPos = assignment.find('=');
        if (equalSignPos == std::string::npos) {
            // Invalid assertion format, skip it
            continue;
        }

        // Extract the variable name (before the '=' sign)
        std::string variable = assignment.substr(0, equalSignPos);
        // Trim any leading or trailing whitespaces
        variable.erase(0, variable.find_first_not_of(" \t"));
        variable.erase(variable.find_last_not_of(" \t") + 1);

        // Extract the value (after the '=' sign)
        std::string value = assignment.substr(equalSignPos + 1);
        // Trim any leading or trailing whitespaces
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        // Remove quotes from the value if present
        if (!value.empty() && (value.front() == '"' || value.front() == '\'') &&
            value.front() == value.back()) {
            value = value.substr(1, value.size() - 2);
        }

        // Create an Assertion object and add it to the vector
        // extractedAssignments.push_back({variable, value});
        extractedAssignments[variable] = value;
    }

    return extractedAssignments;
}

const std::string Utility::double_ending_html_tags[DOUBLE_ENDING_TAGS] = {"html",
                                                 "h1",
                                                 "h2",
                                                 "h3",
                                                 "h4",
                                                 "h5",
                                                 "h6",
                                                 "h7",
                                                 "div",
                                                 "body",
                                                 "head",
                                                 "title",
                                                 "link",
                                                 "style",
                                                 "script",
                                                 "noscript",
                                                 "template",
                                                 "article",
                                                 "section",
                                                 "nav",
                                                 "aside",
                                                 "header",
                                                 "footer",
                                                 "span",
                                                 "p",
                                                 "a",
                                                 "b",
                                                 "i",
                                                 "em",
                                                 "strong",
                                                 "small",
                                                 "mark",
                                                 "del",
                                                 "ins",
                                                 "sub",
                                                 "sup",
                                                 "q",
                                                 "cite",
                                                 "dfn",
                                                 "abbr",
                                                 "time",
                                                 "code",
                                                 "var"};

const std::string Utility::single_ending_html_tags[SINGLE_ENDING_TAGS] = {"br",
                                                 "hr",
                                                 "img",
                                                 "input",
                                                 "source",
                                                 "track",
                                                 "wbr",
                                                 "area",
                                                 "base",
                                                 "col",
                                                 "command",
                                                 "embed",
                                                 "keygen",
                                                 "link",
                                                 "meta",
                                                 "param",
                                                 "source",
                                                 "track",
                                                 "wbr",
                                                 "DOCTYPE"
                                                 };