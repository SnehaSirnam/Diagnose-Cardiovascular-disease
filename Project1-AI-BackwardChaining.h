/*
 * BackwardChaining.h
 *
 *
 */


#include <iostream>
#include <cstddef>
#include <queue>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>
#include <stack>
#include <set>
#include <ctype.h>

using namespace std;

// CREATION OF CLASS BackwardChaining
class BackwardChaining
{
public:

    static const int varsize = 18, concsize = 30, clausesize = 180, var_inc = 6;
    string varlist[varsize], conclist[concsize], clausevarlist[clausesize], clausevarlistValidConditions[clausesize], knbase[concsize];
    string str1, str2, disease ;
    bool DiseaseFound = false ;

    // STL FUNCTIONS INITIALIZED

    map<int, string> rule_number;
    map<int, string> clause_number;
    map<int, string> clause_number_valid_condition;
    map<string, string> varlist_instan;
    map<int, bool> finalized_conclusions;
    map<int, string> ruleno_concllist;
    stack<int> conclusion_stack;
    stack<int> conclusion_stack_clause_number;
    stack<int> rule_number_stack;
    map<string, string> finalized_conclusions2;
    set<string> true_conclusions;
    map<string,string> varibles_questions;

    // FUNCTION HEADERS
    BackwardChaining();
    void knowledgebase();
    void filetoarray();
    void Display_Structures();
    void assignRuleKnBase();
    void assignRuleConclist();
    void assignClauseNumber();
    void assignClauseNumber_validCondition();
    void varlistInstan();
    string DiseaseIdentification();
    bool questionUser();
    bool CompareStrings(string, string);
};
