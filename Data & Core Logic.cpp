/*
 ============================================================================
  GROUP PROJECT: AI Study Assistant Usage Tracker
  COURSE: Practikum Pemrograman | Computer Science | CS-C
  
  Role:
  - Faraz: Project Leader & Main Menu Integration
  - Rafif: Data Structure, Record Inputs, & Printing
  - Nick: Math Calculations, Category Counting, & Recursion
  - Dyen: Manual Sorting & Searching Algorithms
 ============================================================================
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;

// ============================================================================
// DATA & CORE LOGIC
// ============================================================================

const int Max_Records = 100; // Maximum number of records the array can store

// STEP 1 FOR MEMBER 2: This is the structure for a single usage record.
struct UsageRecord {
    int recordID;            // 101, 102, 103
    string toolName;         // "ChatGPT", "GitHub Copilot", "Claude"
    string activityCategory; // Coding, Writing, Research, Study, Other
    double usageTime;        // Time spent in minutes
    int Rating;              // Rating from 1 to 5
};


// Function to ask the user for inputs and save them.
void addUsageRecord(UsageRecord records[], int &count) {
    if (count >= Max_Records) {
        cout << "Error, database is full! You cannot add more than " << Max_Records << " records." << endl;
        return;
    }

    cout << "==== ADD NEW USAGE RECORD ====" << endl;

    // Input the records
    cout << "Add the records (i.e. 101, 102, 103, etc): " << endl;
    cin >> records[count].recordID;

    // If user press enter for the input, then it gets ignore
    cin.ignore(10000, '\n'); 

    //  Input tool name
    cout << "Add the tool name (i.e. ChatGPT, Claude, Qwen): ";
    getline(cin, records[count].toolName);

    // If the user press enter then empty() is true
    while (records[count].toolName.empty()) {
        cout << "Invalid input, string cannot be empty! Please enter again: ";
        getline(cin, records[count].toolName);
    }

    // Input the activity category
    cout << "Add the activity (i.e. Research, Study, Coding): ";
    getline(cin, records[count].activityCategory);

    // If the user press enter then empty() is true
    while (records[count].activityCategory.empty()) {
        cout << "Invalid input, string cannot be empty! Please enter again: ";
        getline(cin, records[count].activityCategory);
    }

    // Input the usage time
    cout << "Add the usage time (time spent on minutes): " << endl;
    cin >> records[count].usageTime;

    // Input the rating
    cout << "Add the records here (rating from the scale of 1-5): " << endl;
    cin >> records[count].Rating;

    // While loop if the user input input for RATING is less than 1 and more than 5
    while (records[count].Rating > 5 || 1 > records[count].Rating){
        cout << "Invalid number, please input the rating again:" << endl;
        cin >> records[count].Rating;
    }
    count++;
}

string classifyDuration(double duration) {
    // Use if else statement to determine the duration category: Low, Moderate, High
    if (duration < 30) return "Low";
    else if (duration <= 60) return "Moderate";
    else return "High";
}

// Print all stored records
void displayRecords(const UsageRecord records[], int count) {
    if (count == 0) {
        cout << "[Info] No records found. Try adding some records first!" << endl;
        return;
    }

    cout << "\n=============== ALL USAGE RECORDS ===============\n";

    // For loop to print out the recordID, toolName, activityCategory, Rating, and usageTime
    for (int i = 0; i < count; i++){
        cout << "Record: " << records[i].recordID << endl;
        cout << "Tool name: " << records[i].toolName << endl;
        cout << "Activity: " << records[i].activityCategory << endl;
        cout << "Rating: " << records[i].Rating << endl;
        cout << "Usage time: " << records[i].usageTime << " Minutes " << "= " << classifyDuration(records[i].usageTime) << endl << endl;
    }
}
