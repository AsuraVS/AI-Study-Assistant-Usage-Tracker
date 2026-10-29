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
                UsageRecord temp = records [j];
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
        cout << "[Success] Records sorted by Rating in "
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

        if (searchOption == 1 && records [i].toolName == searchKey){
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
