/*
 * main.cpp
 *
 *
 */

#include <iostream>
#include <string>
#include "Project1-AI-BackwardChaining.h"
#include "Project1-AI-ForwardChaining.h"

using namespace std;

int main()
{
    bool exit = false;
    int choice;
    string response, disease, represent;
    string list_print;
    cout << "\t\t\t==============================================================================" << endl;
    cout << "\t\t\t    Welcome to Expert System for diagnosing Cardiovascular(Heart) Diseases " << endl;
    cout << "\t\t\t==============================================================================" << endl << endl;

    while (!exit)
    {
        cout << endl;
        cout << "\tChoose an option from the following:" << endl;
        cout << "\t\t1.Identification of a Cardiovascular(Heart) Disease" << endl;
        cout << "\t\t2.Treatment for a specific Cardiovascular(Heart) Disease" << endl;
        cout << "\t\t3.To exit" << endl;
        cin >> choice;
        BackwardChaining bw;
        ForwardChaining fw;
        switch (choice)
        {
        case 1:
        {
            cout << "\t=================================================================================" << endl << endl;
            cout << "\t\tEntering the Heart Disease Identification System" << endl;
            cout << "\t\tInitiating the KnowledgeBase" << endl;
            cout << "\t\tPlease enter YES/NO for the following symptoms unless specified." << endl;
            cout << "\t=================================================================================" << endl << endl;
            disease = bw.DiseaseIdentification();
            if (bw.DiseaseFound == true)
            {
                cout << "===================================================================================" << endl << endl;
                cout << "Do you want to proceed to treatment for the identified \"" << disease << "\" (YES/NO):" << endl;
                cin >> response;
                transform(response.begin(), response.end(), response.begin(), ::toupper);
                if (response == "YES")
                {
                    transform(disease.begin(), disease.end(), disease.begin(), ::toupper);
                    cout << "==================================================================================" << endl << endl;
                    cout << "Treatment for \"" << disease << "\" is" << endl;
                    fw.Treatment(disease);
                }
                cout<<endl;
                cout<<endl;
                cout << "Exiting Disease Identification System." << endl;
                break;
            }
            break;
        }
        case 2:
        {
            cout << "\tEnter the Disease name:" << endl;
            cin >> disease;
            transform(disease.begin(), disease.end(), disease.begin(), ::toupper);
            cout << "Treatment for \"" << disease << "\" is" << endl;
            fw.Treatment(disease);
            break;
        }

        case 3:
        {
            exit = true;
            cout << "\t\tBYE BYE :)";
            break;
        }
        default:
        {
            cout << "Please enter a valid choice";
            break;
        }
        }
    }
    return 0;
}
