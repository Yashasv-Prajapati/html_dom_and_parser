#pragma once
#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#define DOUBLE_ENDING_TAGS 45
#define SINGLE_ENDING_TAGS 20

class Utility
{
public:

    static std::string read_file(const std::string filename);
    static std::vector<std::string> separate_strings_by_char(const std::string expr, char ch);
    static bool is_assignment_expression(const std::string expr);
    static bool is_double_ending_tag(const std::string tag);
    static bool is_single_ending_tag(const std::string tag);
    static std::stack<std::string> append_stacks(std::stack<std::string> to, std::stack<std::string> from);

    static const std::string double_ending_html_tags[DOUBLE_ENDING_TAGS];
    static const std::string single_ending_html_tags[SINGLE_ENDING_TAGS];


};

#endif