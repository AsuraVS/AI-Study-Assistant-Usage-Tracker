// ============================================================================
//  MEMBER 3 SECTION: MATH & RECURSION
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
    cout<<"Writng: "<<writingCount<<endl;
    cout<<"Research: "<<researchCount<<endl;
    cout<<"Study: "<<studyCount<<endl;
    cout<<"Other: "<<otherCount<<endl;

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
        if(records[i].activityCategory="Coding") {
            codingTotal += records[i].usageTime;
        }
        else if(records[i].activityCategory="Writing") {
            writingTotal += records[i].usageTime;
        }
        else if(records[i].activityCategory="Research") {
            researchTotal += records[i].usageTime;
        }
        else if(records[i].activityCategory="Study") {
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
