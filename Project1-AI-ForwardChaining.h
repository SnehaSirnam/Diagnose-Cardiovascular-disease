/*
 * ForwardChaining.h
 *
 *
 */

#include <iostream>
#include <cstddef>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <stack>
#include <map>
#include <queue>

using namespace std;

// CREATION OF CLASS ForwardChaining
class ForwardChaining
{
public:

    static const int varsize = 1, rulesize = 12, clausevarsize = 36, var_inc = 10;
    string ClauseVarlist[clausevarsize], kn_base[rulesize];
    string Result;

    // STL FUNCTIONS INITIALIZED

    map<int, string> assign_rule_number;
    map<int, string> assign_clause_number;
    map<string, string> var_list_Ins;
    queue <string> conc_var_queue;

    // FUNCTION HEADERS
    ForwardChaining();
    void knowledgebase_FW();
    void Filecopy();
    void MapRuleNumber_kn_base();
    void MapClauseNumber_ClauseVarList();
    void Varlist_Instantiation();
    void Display_Structures();
    bool CompareStrings(string str1, string str2);
    void Treatment(string str);
};

