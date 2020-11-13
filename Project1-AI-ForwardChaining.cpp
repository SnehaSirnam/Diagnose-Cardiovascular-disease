/*
 * ForwardChaining.cpp
 *
 *
 */

//This class contains the implementation of ForwardChaining.h

#include "Project1-AI-ForwardChaining.h"
using namespace std;

//Initializing all the methods

ForwardChaining::ForwardChaining()
{
    knowledgebase_FW();
    Filecopy();
    MapRuleNumber_kn_base();
    MapClauseNumber_ClauseVarList();
    Varlist_Instantiation();
}


//Knowledge base is created.
//For a particular disease treatment is given
void ForwardChaining::knowledgebase_FW()
{
    kn_base[0] = "IF DISEASE=Angina THEN TREATMENT=Angioplastry and Stent treatment. Should take oral medications that include Nitrates, Aspirin.";
    kn_base[1] = "IF DISEASE=Arrhythmias THEN TREATMENT=Maze procedure and cardioversion treatment that uses electricity to shock the heart back into a normal rhythm while the patient is sedated are to be done.";
    kn_base[2] = "IF DISEASE=Congenital_heart_disease THEN TREATMENT=Treatment include medicines, catheter procedures, surgery, and heart transplants.";
    kn_base[3] = "IF DISEASE=Coronary_Heart_Disease THEN TREATMENT=Coronary bypass surgery should be done. Beta blockers and calcium channel blockers should be given to the patient for speed recovery";
    kn_base[4] = "IF DISEASE=Deep_vein_thrombosis THEN TREATMENT=Oral antocoagulants, Heparin and Vitamin K antagonist should be taken";
    kn_base[5] = "IF DISEASE=Dilated_Cardiomyopathy THEN TREATMENT=Treated with Beta blockers and ACE inhibitors can help to recover soon";
    kn_base[6] = "IF DISEASE=Heart_Attack THEN TREATMENT=Thrombolysis and baloon Angioplastry surgery are to be undergone.";
    kn_base[7] = "IF DISEASE=Heart_failure THEN TREATMENT=Heart transplantation or coronary bypass surgery is to be undergone. Blood Thinning medications can prevent further damage to the heart. ";
    kn_base[8] = "IF DISEASE=Heart_Valve_Disease THEN TREATMENT=Valve repair replacement or Balloon valvuloplastry are to be done";
    kn_base[9] = "IF DISEASE=Hypertrophic_Cardiomyopathy THEN TREATMENT=Septal Myectomy and Alcohol septal ablation can cure this disease";
    kn_base[10] = "IF DISEASE=Peripheral_arterial_disease THEN TREATMENT=Angioplastry,Bypass surgery are to be done. Supervised exercise program can help with the cure.";
    kn_base[11] = "IF DISEASE=Stroke THEN TREATMENT=Tissue plasminogen activator should be given.Thrombectomy should be done.";

}

// Clause Variable List is stored in the file

void ForwardChaining::Filecopy()
{
    fstream Clausefile;

    Clausefile.open("Project1-AI-FWC_Clausevarlist.txt");
    for (int i = 0; i < clausevarsize; i++)
    {
        Clausefile >> ClauseVarlist[i];
    }

}

// The rule number is assigned to the knowledge base
//uses MAP STL

void ForwardChaining::MapRuleNumber_kn_base()
{
    int rule = 10;
    for (int i = 0; i < rulesize; i++)
    {
        assign_rule_number.insert(pair<int, string>(rule, kn_base[i]));
        rule = rule + 10;
    }
}

// Clause number is assigned to the clause variable list
//User MAP STL
void ForwardChaining::MapClauseNumber_ClauseVarList()
{
    int Clause_no = 1, i = 0;
    while ( i < clausevarsize )
    {
        assign_clause_number.insert(pair<int, string>(Clause_no, ClauseVarlist[i]));
        Clause_no++;
        i++;
    }
}

// ALL VARIABLES in the variable list are initialized to NI

void ForwardChaining::Varlist_Instantiation()
{
    var_list_Ins.insert(pair<string, string>("DISEASE", "NI"));
}


// Used for comparison of the disease with the knowledge base

bool ForwardChaining::CompareStrings(string s1, string s2)
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

// Checks if the conclusion variable queue is not empty and gets the rule number from the clause number
// Compares the disease name with the knowledge base
// else goes to the position of the disease in the clause variable list
void ForwardChaining::Treatment(string disease)
{

    conc_var_queue.push("DISEASE");
    var_list_Ins["DISEASE"] = disease;
    int Clause_no = 1, Rule_no;

    if (disease != "")
    {
        while (!conc_var_queue.empty())
        {
            map<int, string>::iterator itr;
            for (itr = assign_clause_number.begin(); itr != assign_clause_number.end(); itr++)
            {
                if (itr->second != "s")
                {
                    // Converting of Clause number to Rule number
                    Rule_no = (((Clause_no / 3) + 1) * 10);
                }

            }

            int pos = assign_rule_number[Rule_no].find("=");
            int pos1 = assign_rule_number[Rule_no].find(" THEN");
            string compare = assign_rule_number[Rule_no].substr(pos + 1, pos1 - (pos + 1));

            if (CompareStrings(compare, disease))
            {
                int treatment = assign_rule_number[Rule_no].rfind("=");
                Result = assign_rule_number[Rule_no].substr(treatment, assign_rule_number[Rule_no].length());
                Result.erase(0,1);
                cout << Result << endl;
                break;
            }
            else
            {
                Clause_no = Clause_no + 2; // moving to the position of disease

            }

        }

    }

    else
        cout << "Apologies..!!!! Could not specify the treatment as we are not able to detect the disease!!!!" << endl;

}


