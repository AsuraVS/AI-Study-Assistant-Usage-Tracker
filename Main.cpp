#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int Max_Records = 100; // Maximum number of records the array can store

// STEP 1 FOR MEMBER 2: This is the structure for a single usage record.
struct UsageRecord {
    int recordID;              // 101, 102, 103
    string toolName;           // "ChatGPT", "GitHub Copilot", "Claude"
    string activityCategory; // Coding, Writing, Research, Study, Other
    double usageTime;        // Time spent in minutes
    int Rating;              // Rating from 1 to 5
};

// Function prototypes
void addUsageRecord(UsageRecord records[], int &count);
string classifyDuration(double duration);
void displayRecords(const UsageRecord records[], int count);
double calculateTotalUsageTimeRecursive(const UsageRecord records[], int n);
double calculateAverageRating(const UsageRecord records[], int count);
void countByActivityCategory(const UsageRecord records[], int count);
void showCategoryWithHighestUsage(const UsageRecord records[], int count);
void sortRecords(UsageRecord records[], int count, int sortByOption);
void searchRecords(const UsageRecord records[], int count, const string &searchKey, int searchOption);
void saveRecordsToFile(const UsageRecord records[], int count, const string &filename);
void loadRecordsFromFile(UsageRecord records[], int &count, const string &filename);

// ============================================================================
// MEMBER 2 SECTION: RECORDS MANAGEMENT & DISPLAY
// ============================================================================

// Function to ask the user for inputs and save them.
void addUsageRecord(UsageRecord records[], int &count) {
    if (count >= Max_Records) {
        cout << "Error, database is full! You cannot add more than " << Max_Records << " records." << endl;
        return;
    }

    cout << "==== ADD NEW USAGE RECORD ====" << endl;

    // Input the records
    cout << "Add the records (e.g. 1, 2, 3, etc): " << endl;
    cin >> records[count].recordID;

    // If user press enter for the input, then it gets ignore
    cin.ignore(10000, '\n');  

    //  Input tool name
    cout << "Add the tool name (e.g. ChatGPT, Claude, Qwen): ";
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
    cout << "[Success] Record added successfully!\n";
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

// ============================================================================
// MEMBER 3 SECTION: MATH & RECURSION
// ============================================================================

// STEP 1 FOR MEMBER 3: Recursive function to sum up total minutes.
double calculateTotalUsageTimeRecursive(const UsageRecord records[], int n) {
    if (n <= 0) {
        return 0.0;
    }
    return records[n-1].usageTime + calculateTotalUsageTimeRecursive(records, n-1); 
}

// STEP 2 FOR MEMBER 3: Calculate the average rating.
double calculateAverageRating(const UsageRecord records[], int count) {
    if (count == 0) {
    return 0.0;
    }
    
    double total=0.0;
    
    for(int i=0;i<count;i++) {
        total += records[i].Rating;
    }
    
    return total/count;
}

// STEP 3 FOR MEMBER 3: Count how many times each category was picked.
void countByActivityCategory(const UsageRecord records[], int count) {
    if (count == 0) {
        cout << "\n[Info] No records to analyze.\n";
        return;
    }

// setting variables for each category count
    int codingCount=0;
    int writingCount=0;
    int researchCount=0;
    int studyCount=0;
    int otherCount=0;
    
// categorizing the user inputs into specific category based on the activity
    for(int i=0;i<count;i++) {
        if(records[i].activityCategory=="Coding") {
            codingCount++;
        }
        else if(records[i].activityCategory=="Writing") {
            writingCount++;
        }
        else if(records[i].activityCategory=="Research") {
            researchCount++;
        }
        else if(records[i].activityCategory=="Study") {
            studyCount++;
        }
        else {
            otherCount++;
        }
    }

// printing the result
    cout<<"=== TOTAL ACTIVITY CATEGORY ==="<<endl;
    cout<<"Coding: "<<codingCount<<endl;
    cout<<"Writing: "<<writingCount<<endl;
    cout<<"Research: "<<researchCount<<endl;
    cout<<"Study: "<<studyCount<<endl;
    cout<<"Other: "<<otherCount<<endl;
}

// STEP 4 FOR MEMBER 3 (CHALLENGE REQUIREMENT): Find the category with the highest total usage time.
void showCategoryWithHighestUsage(const UsageRecord records[], int count) {
    if (count == 0) {
        cout << "\n[Info] No records available.\n";
        return;
    }

// setting variables for total time on each category
    double codingTotal=0;
    double writingTotal=0;
    double researchTotal=0;
    double studyTotal=0;
    double otherTotal=0;

// categorizing the user inputs to specific activity based category
    for(int i=0;i<count;i++) {
        if(records[i].activityCategory=="Coding") {
            codingTotal += records[i].usageTime;
        }
        else if(records[i].activityCategory=="Writing") {
            writingTotal += records[i].usageTime;
        }
        else if(records[i].activityCategory=="Research") {
            researchTotal += records[i].usageTime;
        }
        else if(records[i].activityCategory=="Study") {
            studyTotal += records[i].usageTime;
        }
        else {
            otherTotal += records[i].usageTime;
        }
    }
    
// assume the highest time usage is in coding
    string highestCategory="Coding";
    double highestTotal=codingTotal;
    
// test each category and sort based which is highest time usage
    if(writingTotal>highestTotal) {
        highestTotal=writingTotal;
        highestCategory="Writing";
    }
    else if(researchTotal>highestTotal) {
        highestTotal=researchTotal;
        highestCategory="Research";
    }
    else if(studyTotal>highestTotal) {
        highestTotal=studyTotal;
        highestCategory="Study";
    }
    else if(otherTotal>highestTotal) {
        highestTotal=otherTotal;
        highestCategory="Other";
    }

// print results
    cout<<"\n=== HIGHEST CATEGORY TIME USAGE ==="<<endl;
    cout<<"Highest Category Usage: "<<highestCategory<<endl;
    cout<<"Total Time Usage: "<<highestTotal<<endl;
}

// ============================================================================
// MEMBER 4 SECTION: SORTING & SEARCHING
// ============================================================================

// STEP 1 FOR MEMBER 4: Write a manual sorting algorithm (DO NOT use std::sort).
// Reorders the records by usage time or rating, based on the user's choices.
void sortRecords(UsageRecord records[], int count, int sortByOption) {
    // There is nothing useful to sort when there are zero or one records.
    if (count <= 1) {
        cout << "[Info] Not enough records to sort." << endl;
        return;
    }

    // Option 1 means usage time; option 2 means rating.
    if (sortByOption != 1 && sortByOption != 2) {
        cout << "[Error] Invalid sort option." << endl;
        return;
    }

    // Ask whether smaller values should come first or larger values should come first.
    string directionChoice;
    cout << "Choose sort order (1 = Ascending, 2 = Descending): " << endl;
    cin >> directionChoice;

    // Stop if the user enters anything other than 1 or 2.
    if (directionChoice != "1" && directionChoice != "2") {
        cout << "[Error] Invalid sort direction." << endl;
        return;
    }

    // Bubble sort: each pass moves an out-of-order record toward its correct position.
    for (int i = 0; i < count - 1; i++){
        // The last i records are already in the right place, so skip them.
        for (int j = 0; j < count - i - 1; j++){
            // This becomes true when the two neighboring records need to trade places.
            bool shouldSwap = false;

            // Compare usage times when the user chose option 1.
            if (sortByOption == 1){
                // Ascending puts the smaller time first; descending puts the larger time first.
                if ((directionChoice == "1" && records[j].usageTime > records[j+1].usageTime) ||
                    (directionChoice == "2" && records[j].usageTime < records[j+1].usageTime)){
                    shouldSwap = true;
                }
            // Compare ratings when the user chose option 2.
            } else if (sortByOption == 2){
                // Use the same ascending or descending rule for ratings.
                if ((directionChoice == "1" && records[j].Rating > records[j+1].Rating) ||
                    (directionChoice == "2" && records[j].Rating < records[j+1].Rating)){
                    shouldSwap = true;
                }
            }
            // Swap the complete records so their other details stay together.
            if (shouldSwap){
                UsageRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
    // Tell the user which field and order were used.
    if (sortByOption == 1){
        cout << "\n[Success] Records sorted by Usage Time in "
             << (directionChoice == "1" ? "ascending" : "descending") << " order!" << endl;
    } else {
        cout << "\n[Success] Records sorted by Rating in "
             << (directionChoice == "1" ? "ascending" : "descending") << " order!" << endl;
    }
}

// STEP 2 FOR MEMBER 4: Write a manual search algorithm (DO NOT use STL find).
// Looks through every record for a matching tool name or activity category.
void searchRecords(const UsageRecord records[], int count, const string &searchKey, int searchOption) {
    // Searching an empty list cannot return a match.
    if (count == 0) {
        cout << "[Info] No records to search." << endl;
        return;
    }
    // Option 1 searches tool names; option 2 searches activity categories.
    if (searchOption != 1 && searchOption != 2) {
        cout << "[Error] Invalid search option." << endl;
        return;
    }

    // Remember whether at least one record matched the search.
    bool found = false;
    cout << "\n--- SEARCH RESULTS ---\n";

    // Linear search checks each record one by one until the list is finished.
    for (int i = 0; i < count; i++){
        // Check whether this record matches the selected search field.
        bool isMatch = false;

        if (searchOption == 1 && records[i].toolName == searchKey){
            isMatch = true;
        } else if (searchOption == 2 && records[i].activityCategory == searchKey){
            isMatch = true;
        }
        // Print all details for each matching record and remember that a match was found.
        if (isMatch){
            cout << "ID: " << records[i].recordID
                 << " | Tool: " << records[i].toolName
                 << " | Category: " << records[i].activityCategory
                 << " | Time: " << records[i].usageTime << " mins"
                 << " | Rating: " << records[i].Rating << "/5" << endl;
            found = true;
        }
    }
    // Only show the no-results message if the loop found no matches.
    if (!found){
        cout << "No matching records found for \"" << searchKey << "\"." << endl;
    }
}

// ============================================================================
// FILE PERSISTENCE FUNCTIONS (<fstream>)
// ============================================================================

void saveRecordsToFile(const UsageRecord records[], int count, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "[Error] Could not open file for writing!" << endl;
        return;
    }

    outFile << count << endl;
    for (int i = 0; i < count; i++) {
        outFile << records[i].recordID << endl;
        outFile << records[i].toolName << endl;
        outFile << records[i].activityCategory << endl;
        outFile << records[i].usageTime << endl;
        outFile << records[i].Rating << endl;
    }
    outFile.close();
    cout << "[Success] Records saved to " << filename << endl;
}

void loadRecordsFromFile(UsageRecord records[], int &count, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        // File might not exist yet on first run, which is totally normal
        return;
    }

    inFile >> count;
    inFile.ignore(10000, '\n');

    for (int i = 0; i < count; i++) {
        inFile >> records[i].recordID;
        inFile.ignore(10000, '\n');
        getline(inFile, records[i].toolName);
        getline(inFile, records[i].activityCategory);
        inFile >> records[i].usageTime;
        inFile >> records[i].Rating;
        inFile.ignore(10000, '\n');
    }
    inFile.close();
}

// ============================================================================
// MAIN FUNCTION & HIERARCHICAL MENUS
// ============================================================================

int main() {
    UsageRecord records[Max_Records];
    int recordCount = 0;
    string dataFilename = "ai_usage_records.txt";

    // Automatically load existing records at startup
    loadRecordsFromFile(records, recordCount, dataFilename);

    int mainChoice;

    do {
        cout << "\n==================================================\n";
        cout << "        AI STUDY ASSISTANT USAGE TRACKER          \n";
        cout << "==================================================\n";
        cout << " [1] Manage Records (Add / View)\n";
        cout << " [2] Statistics & Analytics Reports\n";
        cout << " [3] Search & Sort Records\n";
        cout << " [4] Exit Program & Save\n";
        cout << "==================================================\n";
        cout << "Enter your choice (1-4): ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                int subChoice;
                do {
                    cout << "\n--------------------------------------------------\n";
                    cout << "              RECORD MANAGEMENT                   \n";
                    cout << "--------------------------------------------------\n";
                    cout << " [1] Add New Usage Record\n";
                    cout << " [2] Display All Records (with Low/Med/High tags)\n";
                    cout << " [3] Return to Main Menu\n";
                    cout << "--------------------------------------------------\n";
                    cout << "Enter your choice (1-3): ";
                    cin >> subChoice;

                    if (subChoice == 1) {
                        addUsageRecord(records, recordCount);
                        saveRecordsToFile(records, recordCount, dataFilename); // Auto-save on add
                    } else if (subChoice == 2) {
                        displayRecords(records, recordCount);
                    } else if (subChoice != 3) {
                        cout << "[Error] Invalid option. Try again.\n";
                    }
                } while (subChoice != 3);
                break;
            }
            case 2: {
                int subChoice;
                do {
                    cout << "\n--------------------------------------------------\n";
                    cout << "              STATISTICS & ANALYTICS              \n";
                    cout << "--------------------------------------------------\n";
                    cout << " [1] Total & Average Usage Time (Recursive)\n";
                    cout << " [2] Calculate Average Usefulness Rating\n";
                    cout << " [3] View Category Record Counts\n";
                    cout << " [4] Show Category with Highest Total Usage Time\n";
                    cout << " [5] Return to Main Menu\n";
                    cout << "--------------------------------------------------\n";
                    cout << "Enter your choice (1-5): ";
                    cin >> subChoice;

                    if (subChoice == 1) {
                        double totalTime = calculateTotalUsageTimeRecursive(records, recordCount);
                        double avgTime = (recordCount > 0) ? (totalTime / recordCount) : 0.0;
                        cout << "\n=== USAGE TIME STATISTICS ===" << endl;
                        cout << "Total Usage Time : " << totalTime << " minutes" << endl;
                        cout << "Average Usage Time: " << avgTime << " minutes" << endl;
                    } else if (subChoice == 2) {
                        double avgRating = calculateAverageRating(records, recordCount);
                        cout << "\n=== AVERAGE RATING ===" << endl;
                        cout << "Average Usefulness Rating: " << avgRating << " / 5" << endl;
                    } else if (subChoice == 3) {
                        countByActivityCategory(records, recordCount);
                    } else if (subChoice == 4) {
                        showCategoryWithHighestUsage(records, recordCount);
                    } else if (subChoice != 5) {
                        cout << "[Error] Invalid option. Try again.\n";
                    }
                } while (subChoice != 5);
                break;
            }
            case 3: {
                int subChoice;
                do {
                    cout << "\n--------------------------------------------------\n";
                    cout << "               SEARCH & SORT                      \n";
                    cout << "--------------------------------------------------\n";
                    cout << " [1] Search Records (by Tool Name or Category)\n";
                    cout << " [2] Sort Records (by Usage Time or Rating)\n";
                    cout << " [3] Return to Main Menu\n";
                    cout << "--------------------------------------------------\n";
                    cout << "Enter your choice (1-3): ";
                    cin >> subChoice;

                    if (subChoice == 1) {
                        int searchOpt;
                        cout << "Search by:\n [1] Tool Name (e.g., ChatGPT)\n [2] Activity Category (e.g., Coding)\nChoice: ";
                        cin >> searchOpt;
                        cin.ignore(10000, '\n');
                        
                        string query;
                        cout << "Enter search keyword: ";
                        getline(cin, query);
                        
                        searchRecords(records, recordCount, query, searchOpt);
                    } else if (subChoice == 2) {
                        int sortOpt;
                        cout << "Sort by:\n [1] Usage Time\n [2] Rating\nChoice: ";
                        cin >> sortOpt;
                        
                        sortRecords(records, recordCount, sortOpt);
                        displayRecords(records, recordCount);
                        saveRecordsToFile(records, recordCount, dataFilename); // Auto-save after sorting
                    } else if (subChoice != 3) {
                        cout << "[Error] Invalid option. Try again.\n";
                    }
                } while (subChoice != 3);
                break;
            }
            case 4:
                saveRecordsToFile(records, recordCount, dataFilename);
                cout << "\nData saved successfully. Exiting program. Goodbye!\n";
                break;
            default:
                cout << "[Error] Invalid main menu choice. Please select 1-4.\n";
        }
    } while (mainChoice != 4);

    return 0;
}
