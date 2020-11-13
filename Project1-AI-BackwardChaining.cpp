/*
 * BackwardChaining.cpp
 *
 *
 */

//This class contains the implementation of BackwardChaining.h

#include "Project1-AI-BackwardChaining.h"

using namespace std;

//initialising the required variables and generating the knowledge base

BackwardChaining::BackwardChaining()
{
    knowledgebase();
    filetoarray();
    assignRuleConclist();
    assignRuleKnBase();
    assignClauseNumber();
    varlistInstan();
    assignClauseNumber_validCondition();
}

// KNOWLEDGE BASE IS STORED IN STRING ARRAY - ALL THE IF THEN RULES
//Only if the Symptom is YES, then knowledge base is created.
void BackwardChaining::knowledgebase()
{
    knbase[0] = "IF SYMPTOM=NO THEN DISEASE=NO";
    knbase[1] = "IF SYMPTOM=YES && BREATHLESSNESS=NO && FOOTSORE=YES THEN ABTEST=YES";
    knbase[2] = "IF ABTEST=YES && RESULT=NEGATIVE THEN DISEASE=NO";
    knbase[3] = "IF ABTEST=YES && RESULT=POSITIVE THEN DISEASE=PERIPHERAL_ARTERIAL_DISEASE";
    knbase[4] = "IF SYMPTOM=YES && BREATHLESSNESS=YES && CHESTPAIN=NO && CYANOSIS=YES THEN ECHOCARDIOGRAM=YES";
    knbase[5] = "IF ECHOCARDIOGRAM=YES && GRAPH=NORMAL THEN DISEASE=NO";
    knbase[6] = "IF ECHOCARDIOGRAM=YES && GRAPH=ABNORMAL THEN DISEASE=CONGENITAL_HEART_DISEASE";
    knbase[7] = "IF SYMPTOM=YES && BREATHLESSNESS=YES && CHESTPAIN=NO && CYANOSIS=NO && HMURMURS=YES THEN XRAY=YES";
    knbase[8] = "IF XRAY=YES && RXRAY=NORMAL THEN DISEASE=NO";
    knbase[9] = "IF XRAY=YES && RXRAY=ABNORMAL THEN CARDIACMRI=YES";
    knbase[10] = "IF CARDIACMRI=YES && RMRI=THIN THEN DISEASE=DILATED_CARDIOMYOPATHY";
    knbase[11] = "IF CARDIACMRI=YES && RMRI=THICK THEN DISEASE=HYPERTROPHIC_CARDIOMYOPATHY";
    knbase[12] = "IF CARDIACMRI=YES && RMRI=NORMAL THEN CTSCAN=YES";
    knbase[13] = "IF CTSCAN=YES && RCTSCAN=NEGATIVE THEN DISEASE=NO";
    knbase[14] = "IF CTSCAN=YES && RCTSCAN=POSITIVE THEN DISEASE=ANGINA";
    knbase[15] = "IF SYMPTOM=YES && BREATHLESSNESS=YES && CHESTPAIN=YES && DISCOMFORT=NO THEN ULTRASONOGRAPHY=YES";
    knbase[16] = "IF ULTRASONOGRAPHY=YES && REPORT=NORMAL THEN DISEASE=NO";
    knbase[17] = "IF ULTRASONOGRAPHY=YES && REPORT=ABNORMAL THEN DISEASE=DEEP_VEIN_THROMBOSIS";
    knbase[18] = "IF SYMPTOM=YES && BREATHLESSNESS=YES && CHESTPAIN=YES && DISCOMFORT=YES THEN ECG=YES";
    knbase[19] = "IF ECG=YES && RECG=NORMAL THEN DISEASE=NO";
    knbase[20] = "IF ECG=YES && RECG=VABNORMALITIES && STRESSTEST=HIGH THEN DISEASE=HEART_VALVE_DISEASE";
    knbase[21] = "IF ECG=YES && RECG=ABNORMAL THEN BLOODTEST=YES";
    knbase[22] = "IF BLOODTEST=YES && BLOODREPORT=HIGHPROTEIN THEN DISEASE=HEART_ATTACK";
    knbase[23] = "IF BLOODTEST=YES && BLOODREPORT=LOWIRON THEN DISEASE=STROKE";
    knbase[24] = "IF BLOODTEST=YES && BLOODREPORT=ABNORMAL THEN DISEASE=HEART_FAILURE";
    knbase[25] = "IF BLOODTEST=YES && BLOODREPORT=NORMAL THEN CATHDERIZATION=YES";
    knbase[26] = "IF CATHDERIZATION=YES && RCATH=POSITIVE THEN DISEASE=ARRHYTHMIAS";
    knbase[27] = "IF CATHDERIZATION=YES && RCATH=NEGATIVE THEN TREADMILLTEST=YES";
    knbase[28] = "IF TREADMILLTEST=YES && TRESULT=NEGATIVE THEN DISEASE=NO";
    knbase[29] = "IF TREADMILLTEST=YES && TRESULT=POSITIVE THEN DISEASE=CORONARY_HEART_DISEASE";

    varibles_questions.insert({"SYMPTOM","Are you experiencing any symptom(s)?"});
    varibles_questions.insert({"BREATHLESSNESS","Are you experiencing any breathlessness?"});
    varibles_questions.insert({"FOOTSORE","Are you experiencing any footsore?"});
    varibles_questions.insert({"RESULT","what's the result of Ankle brachial test? (POSITIVE/NEGATIVE)"});
    varibles_questions.insert({"CHESTPAIN","Are you experiencing any chest pain?"});
    varibles_questions.insert({"CYANOSIS","Are you experiencing any cyanosis?"});
    varibles_questions.insert({"GRAPH","What's the result of Echo cardiogram test? (ABNORMAL/NORMAL)"});
    varibles_questions.insert({"HMURMURS","Are you experiencing any heart murmurs?"});
    varibles_questions.insert({"RXRAY","What's the result of X-RAY? (ABNORMAL/NORMAL)"});
    varibles_questions.insert({"RMRI","What's the result of cardiac MRI test? (THIN/THICK/NORMAL)"});
    varibles_questions.insert({"RCTSCAN","What's the result of RCT scan? (POSITIVE/NEGATIVE)"});
    varibles_questions.insert({"DISCOMFORT","Are you experiencing any discomfort?"});
    varibles_questions.insert({"REPORT","What's the result of Ultra sonography? (ABNORMAL/NORMAL)"});
    varibles_questions.insert({"RECG","What's the result of ECG? (VALVEABNORMALITIES/ABNORMAL/NORMAL)"});
    varibles_questions.insert({"STRESSTEST","what's the result of Stress test?"});
    varibles_questions.insert({"BLOODREPORT","What's the result of blood test? (HIGHPROTEIN/LOWIRON/ABNORMAL/NORMAL)"});
    varibles_questions.insert({"RCATH","What's the result of Cathodic catheterization? (POSITIVE/NEGATIVE)"});
    varibles_questions.insert({"TRESULT","What's the result of Treadmill test? (POSITIVE/NEGATIVE)"});

}
// Variable list,Conclusion list and Clause Variable List are all stored in the file and then called here.

void BackwardChaining::filetoarray()
{
    ifstream varfile, conlfile, clausefile, clausecountfile, clauseCountValidConditionFile;

    // the file path is given where all the files are stored

    varfile.open("Project1-AI-BWC_Varlist.txt");
    for (int i = 0; i < varsize; i++)
    {
        varfile >> varlist[i];
    }
    varfile.close();

    conlfile.open("Project1-AI-BWC_Conclist.txt");
    for (int i = 0; i < concsize; i++)
    {
        conlfile >> conclist[i];
    }
    conlfile.close();

    clausefile.open("Project1-AI-BWC_Clausevarlist.txt");
    for (int i = 0; i < clausesize; i++)
    {
        clausefile >> clausevarlist[i];
    }
    clausefile.close();

    clauseCountValidConditionFile.open("Project1-AI-BWC_ClausevarlistConditions.txt");
    for (int i = 0; i < clausesize; i++)
    {
        clauseCountValidConditionFile >> clausevarlistValidConditions[i];
    }
    clauseCountValidConditionFile.close();

}

// Assigning the Rule number for the knowledge base - uses MAP STL

void BackwardChaining::assignRuleKnBase()
{
    int rule = 10, i = 0;
    while ( i < concsize )
    {
        rule_number.insert(pair<int, string>(rule, knbase[i]));
        rule = rule + 10;
        i++;
    }
}


void BackwardChaining::assignRuleConclist()
{
    int rule = 10, i = 0;
    while (i < concsize )
    {
        ruleno_concllist.insert(pair<int, string>(rule, conclist[i]));
        rule = rule + 10;
        i++;
    }
}

// Assigning the Clause number for the knowledge base - uses MAP STL

void BackwardChaining::assignClauseNumber()
{
    int clauseno = 1, i = 0;
    while ( i < clausesize )
    {
        clause_number.insert(pair<int, string>(clauseno, clausevarlist[i]));
        clauseno++;
        i++;
    }
}

void BackwardChaining::assignClauseNumber_validCondition()
{
    int clauseno = 1, i = 0;
    while ( i < clausesize )
    {
        clause_number_valid_condition.insert(pair<int, string>(clauseno, clausevarlistValidConditions[i]));
        clauseno++;
        i++;
    }
}

// Instantiating all the variables in the variable list to "NI" initially - uses MAP STL

void BackwardChaining::varlistInstan()
{
    int i = 0;
    while ( i < varsize )
    {
        varlist_instan.insert(pair<string, string>(varlist[i], "NI"));
        i++;
    }
}


// This function is used to compare two strings, in this program it compares the user entered data along with knowledge base.
bool BackwardChaining::CompareStrings(string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    if (s1 == s2)
    {
        return true;

    }

    else
    {
        return false;
    }
}

bool BackwardChaining::questionUser()
{

    bool result = true;
    string Y_N_user;

    // We will loop until the conclusion stack is empty
    while(!conclusion_stack.empty())
    {
        // Initially setting result to be true
        result = true;

        int clause_number_to_start = conclusion_stack_clause_number.top();
        // Keeping track of rule number in current iteration
        int rule_no_in_current_iteration = conclusion_stack.top();
        // Looping only through the clause variables which are part of the rule.
        // So starting from clause_number_to_start and ending +6 which is our var_inc
        for (int i = clause_number_to_start; i < clause_number_to_start+var_inc; i++)
        {
            if (clause_number[i] != "s")// Empty Values are stored as "s" in clause variable list.
            {
                map<string, string>::iterator itr;
                string correspondingClauseVariable = clause_number[i];
                // Checking if clauseVariable is part of variable list. If it is not part of variable list then
                // it should be a conclusion variable
                if (varlist_instan.find( correspondingClauseVariable ) != varlist_instan.end())
                {
                    string variable_instantiation_value = varlist_instan[correspondingClauseVariable];
                    // This indicates that variable is not initialized.
                    // So, we need to ask questions to initialize variables
                    if(CompareStrings(variable_instantiation_value, "NI"))
                    {
                        string question = "";
                        // If question corresponding to variable is not defined then ask default question
                        // which is in else block
                        if(varibles_questions.find(correspondingClauseVariable) != varibles_questions.end())
                        {
                            question = varibles_questions.at(clause_number[i]);
                        }
                        else
                        {
                            question = "Are you suffering from "+clause_number[i];
                        }
                        cout << question << endl;
                        cin >> Y_N_user;
                        transform(Y_N_user.begin(), Y_N_user.end(), Y_N_user.begin(), ::toupper);
                        if (Y_N_user == "YES" || Y_N_user == "NO" || Y_N_user == "NEGATIVE" || Y_N_user == "POSITIVE" || Y_N_user == "NORMAL" || Y_N_user == "ABNORMAL" || Y_N_user == "THIN" || Y_N_user == "THICK" || Y_N_user == "VABNORMALITIES" || Y_N_user == "HIGH" || Y_N_user == "HIGHPROTEIN" || Y_N_user == "LOWIRON")
                        {
                            varlist_instan[clause_number[i]] = Y_N_user;
                        }
                        else
                        {
                            cout << "Please enter YES/NO unless specified" << endl;
                            cout << question << endl;
                            cin >> Y_N_user;
                            transform(Y_N_user.begin(), Y_N_user.end(), Y_N_user.begin(), ::toupper);
                            varlist_instan[clause_number[i]] = Y_N_user;
                        }
                    }
                    string variable_instantiation_value_after_instantiating = varlist_instan[correspondingClauseVariable];
                    // Checking if the input from the user is same as that if the expected value for this rule to be true
                    // If one of them is not true then rejecting the rule by making result false
                    // If expectation is same as that of user input then continuing the loop for next clause variable
                    if(!CompareStrings(variable_instantiation_value_after_instantiating, clause_number_valid_condition[i]))
                    {
                        result = result && false;
                        conclusion_stack_clause_number.pop();
                        conclusion_stack.pop();
                        // Indicating that result for a rule is already derived
                        finalized_conclusions.insert({rule_no_in_current_iteration, result});
                        string found_conclusion = ruleno_concllist[rule_no_in_current_iteration];
                        // This will be an intermediate step. So not adding DISEASE into finalized_conclusions2
                        // But, will be adding all the other conclusion variables such as ABTEST, ECG etc.,
                        if(found_conclusion != "DISEASE")
                        {
                            finalized_conclusions2.insert({found_conclusion, "NO"});
                        }
                        break;
                    }
                    else
                    {
                        result = result && true;
                        continue;
                    }
                }
                else
                {
                    // If a rule is already. finalized_conclusions only has conclusion variables which failed
                    // So popping the stack and continuing the loop
                    if(finalized_conclusions.find(rule_no_in_current_iteration) != finalized_conclusions.end())
                    {
                        conclusion_stack_clause_number.pop();
                        conclusion_stack.pop();
                        continue;
                    }

                    // finalized_conclusions2 has conclusion variable to calculated result YES/NO
                    // If YES then we have passed the check so continuing the loop
                    // If NO then we have not passed check for one conclusion variable so popping from the stack and breaking the for-loop
                    if(finalized_conclusions2.find(correspondingClauseVariable) != finalized_conclusions2.end() && finalized_conclusions2.at(correspondingClauseVariable) == "YES")
                    {
                        continue;
                    }
                    else
                    {
                        if(finalized_conclusions2.find(correspondingClauseVariable) != finalized_conclusions2.end() && finalized_conclusions2.at(correspondingClauseVariable) == "NO")
                        {
                            conclusion_stack_clause_number.pop();
                            conclusion_stack.pop();
                            string found_conclusion = ruleno_concllist[rule_no_in_current_iteration];
                            // This will be an intermediate step. So not adding DISEASE into finalized_conclusions2
                            // But, will be adding all the other conclusion variables such as ABTEST, ECG etc.,
                            if(found_conclusion != "DISEASE")
                            {
                                finalized_conclusions2.insert({found_conclusion, "NO"});
                            }
                            break;
                        }
                        // Conclusion variable not in finalized_conclusions2 indicates that corresponding conclusion variable is not evaluated
                        // We need to find the corresponding rule for the conclusion variable and add it to stack and break the for-loop
                        // to continue with outside while loop on stack
                        for (auto itr = ruleno_concllist.cbegin(); itr != ruleno_concllist.cend(); itr++)
                        {
                            int ruleNo = itr->first;
                            string conclusion_concList = itr->second;
                            if(CompareStrings(correspondingClauseVariable, conclusion_concList) && conclusion_concList != "DISEASE")
                            {
                                int clause_no = (((ruleNo / 10) - 1) * 6) + 1;
                                conclusion_stack.push(ruleNo);
                                conclusion_stack_clause_number.push(clause_no);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else
            {
                // This check indicates that we have come to last step of checking for all the clause variables in a rule
                // Based on the conclusion variable if it s disease then we have concluded with the disease
                // Or else adding the identified conclusion variable to finalized_conclusions2 map in order to not evaluate for it again
                // Also popping both stacks as we finished checking all the conditions for a rule
                if(i - clause_number_to_start == 5)
                {
                    conclusion_stack_clause_number.pop();
                    conclusion_stack.pop();
                    string conclusion = ruleno_concllist.at(rule_no_in_current_iteration);
                    if(conclusion == "DISEASE")
                    {
                        finalized_conclusions2.insert({conclusion, rule_number.at(rule_no_in_current_iteration)});
                    }
                    else
                    {
                        finalized_conclusions2.insert({conclusion, "YES"});
                    }
                }
                continue;
            }

            // Incrementing clause number to be persisted in the stack
            int finished_processing_clause = conclusion_stack_clause_number.top();
            conclusion_stack_clause_number.pop();
            finished_processing_clause++;
            conclusion_stack_clause_number.push(finished_processing_clause);
        }
    }
    return result;
}

// MAIN BACKWARD FUNCTIONALITY IS GIVEN HERE

string BackwardChaining::DiseaseIdentification()
{
    string finalConslusionToFind = "DISEASE";
    string localConslusionToFind = finalConslusionToFind;
    string foundDisease = "";

    int index = 300;
    int i = 0;

    while (i < concsize)
    {
        rule_number_stack.push(index); // Loading the stack with all the rule numbers, where 10 is at the top of the stack.
        index = index - 10;
        i++;
    }

    // When stack is not empty - while loop starts
    while (rule_number_stack.empty() != true)
    {
        int ruleNo = rule_number_stack.top();
        rule_number_stack.pop();
        string conclusion_concList = ruleno_concllist.at(ruleNo);
        // Comparing the corresponding conclusion with disease
        if(CompareStrings(localConslusionToFind, conclusion_concList))
        {
            int clause_no = (((ruleNo / 10) - 1) * 6) + 1;
            // Pushing the rule number to one stack
            conclusion_stack.push(ruleNo);
            // Pushing corresponding clause number to another stack
            conclusion_stack_clause_number.push(clause_no);
            // Asking questions now
            bool returnValue = questionUser();
            // Seeing if finalized_conclusions2 map has an entry for disease which indicates that disease
            // was found while asking questions. We will break from the loop once the disease is found
            if(finalized_conclusions2.find(finalConslusionToFind) != finalized_conclusions2.end())
            {
                int Disease_pos = rule_number[ruleNo].rfind("=");
                foundDisease = rule_number[ruleNo].substr(Disease_pos + 1, rule_number[ruleNo].length());
                if ( foundDisease == "NO" )
                {
                    cout<<endl;
                    cout<<"Congrats! you don't have any Cardiovascular(Heart) disease."<<endl;
                    cout<<endl;
                }
                else
                {
                    cout<<"==================================================================================="<<endl;
                    cout<<"You have been diagnosed with "<<foundDisease<<endl;
                    DiseaseFound = true;
                    return foundDisease;
                }
                break;
            }
        }

    }
    // If none of the user inputs matches with the symptoms specified then below statement executes
    if (foundDisease == "")
    {
        cout << "===================================================================" << endl << endl;
        cout << "\tWe don't have rules specified as of now for your symptoms" << endl;
        cout << "===================================================================" << endl << endl;
    }

    return disease;
}
