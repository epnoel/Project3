#include "Website.h"
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

/* method to read data:
 * inputs: fileName + vector, map and unordered_map to store the data in
 * inputs line by line from csv file described by fileName
 * appends websites and their bool mal value (malicious or not) to vector v, map m, and unordered map um
 * performs quick sort on the vector v
 * return: no returns
 */
void readData(string fileName, vector<vector<pair<string,bool>>> &v, map<string,bool> &m, unordered_map<string,bool> &um) {
    ifstream inFile;
    inFile.open(fileName);

    v.resize(36);

    vector<pair<string,string>> duplicates;

    unordered_map<string, pair<string, bool>> testUM;

    string entireLine = "";
    int num;
    string website = "";
    string benignOrMalicious = "";
    bool malicious;

    if (!inFile.is_open()) {
        cout << "Could not open file" << endl;
        return;
    }

    int count = 0;

    getline(inFile, entireLine);

    // initializing the vectors that keep time taken into insert into each data structure
    long long int timeTakenInsertVector = 0;
    long long int timeTakenInsertMap = 0;
    long long int timeTakenInsertUnmap = 0;

    //while loop reads in the lines from the csv file and parses the data
    //stores them into the containers
    while (getline(inFile, entireLine)) {

        for (unsigned int i = 0; i < entireLine.size(); i++) {
            if (entireLine[i] == ',') {
                entireLine[i] = ' ';
            }
        }

        istringstream is(entireLine);

        is >> num;
        is >> website;
        is >> benignOrMalicious;
        is >> malicious;

        string webBeforeRemoveHTTPs = website;
        removeHTTPSPart(website);
        removeWWWPart(website);

        //the if-else conditions assign index of the letters with the help of their ACII values
        int index = 0;

        // If A-Z
        if (website[0] >= 65 && website[0] <= 90) {
            index = website[0] - 65;
        }
            // If a-z
        else if (website[0] >= 97 && website[0] <= 122) {
            index = website[0] - 97;
        }
            // If 0-9
        else if (website[0] >= 48 && website[0] <= 57) {
            index = website[0] - 22;
        }

        // starting the clock that keeps timer for insertion into vector v
        // insertion into vector v works as follows:
        // 1) find if the website is already in the database by using find on unordered_map
        // 2) if in find, push_back onto duplicate vector for debugging purposes
        // 3) if not found, inserts into 2D vector v according to the beginning character
        // count time of insertion into vector keeps account of this whole process
        auto start = high_resolution_clock::now();
        unordered_map<string, pair<string,bool>>::iterator itr;
        itr = testUM.find(website);
        if (itr != testUM.end()) {
            duplicates.push_back(make_pair(webBeforeRemoveHTTPs,itr->second.first));
        }
        else {
            v[index].push_back(make_pair(website, malicious));
            count++;
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        timeTakenInsertVector = timeTakenInsertVector + duration.count();

        start = high_resolution_clock::now();
        m[website] = malicious;
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        timeTakenInsertMap = timeTakenInsertMap + duration.count();

        start = high_resolution_clock::now();
        um[website] = malicious;
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        timeTakenInsertUnmap = timeTakenInsertUnmap + duration.count();


        testUM[website] = make_pair(webBeforeRemoveHTTPs, malicious);

        // Debug
        //cout << "num = " << num << endl;
        //cout << "website = " << website << endl;
        //cout << "benignOrMalicious = " << benignOrMalicious << endl;
        //cout << "malicious = " << malicious << endl;

    }

    //sorting the vector 'v' that stores the website using QUICKSORT
    for (unsigned int a = 0; a < v.size(); a++) {
        quickSort(v[a],0,v[a].size()-1);
    }


    // Debug
    //cout << "vector size = " << count << endl;
    //cout << "map size = " << m.size() << endl;
    //cout << "unordered_map size = " << um.size() << endl;
    cout << endl;

    // printing the execution time taken to insert
    cout << "The execution time taken to insert all the websites into the vector: " << timeTakenInsertVector << endl;
    cout << "The execution time taken to insert all the websites into the map: " << timeTakenInsertMap << endl;
    cout << "The execution time taken to insert all the websites into the unordered map: " << timeTakenInsertUnmap << endl;

}

/*************************************************************************/
//Helper Functions to print instructions for the user

void printRequest() {
    cout << "Would you like to add this website to the list?" << endl;
}

void printMenu() {
    cout << "Options:" << endl;
    cout << "1. Search for website." << endl;
    cout << "2. Show website maliciousness by first character." << endl;
    cout << "3. Show website list size." << endl;
    cout << "4. Add a website to the list." << endl;
    cout << "5. Exit" << endl;
    cout << endl;
}

void printOption() {
    cout << "1. 2D Vector" << endl;
    cout << "2. Map" << endl;
    cout << "3. Unordered Map" << endl;
    cout << endl;
}
/*************************************************************************/


int main() {

    //initializing the 2D vector, map and unordered map that will store the websit data
    vector<vector<pair<string, bool>>> v; // 2D vector
    map<string, bool> m;
    unordered_map<string, bool> um;

    //fileName store the path of the data
    string fileName = "/Users/durgeshjha/Documents/University /Semester 4/Programming 2/GroupProject/urldataMain.csv";

    //starts keeping count of the time needed to read the data from CSV and store into the data structures used (vector, map and unorderedMap)
    auto start = high_resolution_clock::now();

    cout << "Reading in all data..." << endl;

    // reads the data provided by fileName and inserts data to vector v, map m, unordered_map um
    readData(fileName, v, m, um);
    Website test(v, m, um); // website object test

    cout << "Done." << endl;
    cout << endl;
    //stops keeping count of the time needed to read in, parse and store the data
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);


    cout << "Execution time = " << duration.count() << " milliseconds = " << (double) duration.count() / (double) 1000 << " seconds." << endl;
    cout << endl;

    string testOpt;
    int n = 0;
    string websiteOption;
    cout << "Welcome to Malicious Website Sorter" << endl;
    cout << endl;

    while (testOpt != "5") { //testOpt 5 means that the user wants to exit; hence the loop stops
        printMenu();
        cin >> testOpt; //takes input from the user about what they want to do
        cout << endl;

        // Option 1
        if (testOpt == "1") { // Option 1 is search for websites

            cout << "Which website would you like to search for? Make sure you include www. in the website address" << endl;
            cout << endl;
            cin >> websiteOption; //website input by user to check maliciousness
            cout << endl;

            while (true) {
                cout << "Which Data Structure would you like to search in " << endl;
                printOption();
                cin >> testOpt;
                cout << endl;
                int res;
                if (testOpt == "1") { // first data structure option is the vector v
                    start = high_resolution_clock::now(); // starts the clock to measure search in vector

                    res = test.getMalicious2DVector(websiteOption); // returns 0, 1 or -1
                    if (res != -1) { // if found
                        if (res == 1) { // if maliciousness = 1 i.e. malicious website
                            cout << websiteOption << " is malicious according to our databases." << endl;
                        }
                        else { // if maliciousness = 0 i.e. non-malicious website
                            cout << websiteOption << " is safe according to our databases." << endl;
                        }
                    }

                    stop = high_resolution_clock::now(); // stops the clock here
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << endl;
                    cout << "Execution Time: " << duration.count() << " microseconds = " << (double)duration.count() / (double)1000000;
                    cout << " seconds " << endl;

                    break;
                }
                else if (testOpt == "2") { // wants to search in map data structure

                    start = high_resolution_clock::now(); // clock start

                    res = test.getMaliciousMap(websiteOption); // returns 0 , 1 or -1
                    if (res != -1) { // if website found
                        if (res == 1) { // if website is malicious
                            cout << websiteOption << " is malicious according to our databases." << endl;
                        }
                        else { // if website is not malicious
                            cout << websiteOption << " is safe according to our databases." << endl;
                        }
                    }

                    stop = high_resolution_clock::now(); // stop clock
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << endl;
                    cout << "Execution Time: " << duration.count() << " microseconds = " << (double)duration.count() / (double)1000000;
                    cout << " seconds " << endl;

                    break;
                }
                else if (testOpt == "3") { // wants to search in unordered_maps

                    start = high_resolution_clock::now(); // start clock

                    res = test.getMaliciousUnorderedMap(websiteOption); // returns 0, 1 or -1
                    if (res != -1) { // if the website found
                        if (res == 1) { // if the website is malicious
                            cout << websiteOption << " is malicious according to our databases." << endl;
                        }
                        else { // if the website is not malicious
                            cout << websiteOption << " is safe according to our databases." << endl;
                        }
                    }

                    stop = high_resolution_clock::now(); // stop clock
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << endl;
                    cout << "Execution Time: " << duration.count() << " microseconds = " << (double)duration.count() / (double)1000000;
                    cout << " seconds " << endl;

                    break;
                }
                else { // discards invalid option
                    cout << "Not a valid option. Please try again." << endl;
                    cout << endl;
                }
            }
        }

        // Option 2: show website maliciousness by the fist character
        // lists out the websites beginning with the character and their mal value
        else if (testOpt == "2") {
            cout << "Enter first letter of website: " << endl;
            cout << endl;
            cin >> websiteOption;
            cout << endl;
            while (true) {
                cout << "Which Data Structure would you like to search in " << endl;
                printOption();
                cin >> testOpt;
                cout << endl;
                int res;
                if (testOpt == "1") { // search in vector v
                    start = high_resolution_clock::now();

                    test.print2DVectorWebsiteListByChar(websiteOption.at(0)); // uses built in function in Website class

                    stop = high_resolution_clock::now();
                    duration = duration_cast<milliseconds>(stop - start);
                    cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
                    cout << " seconds " << endl;

                    break;
                }
                else if (testOpt == "2") { // search in map m

                    start = high_resolution_clock::now();

                    test.printMapWebsiteListByChar(websiteOption.at(0)); // built in function in the website class

                    stop = high_resolution_clock::now();
                    duration = duration_cast<milliseconds>(stop - start);
                    cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
                    cout << " seconds " << endl;
                    break;
                }
                else if (testOpt == "3") {

                    start = high_resolution_clock::now();


                    test.printUnorderedMapWebsiteListByChar(websiteOption.at(0)); // built in function with the website class

                    stop = high_resolution_clock::now();
                    duration = duration_cast<milliseconds>(stop - start);
                    cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
                    cout << " seconds " << endl;

                    break;
                }
                else { // discards invalid options
                    cout << "Not a valid option. Please try again." << endl;
                    cout << endl;
                }
            }
        }
        else if (testOpt == "3") { // shows a website list size
            cout << "There are " << test.returnSize() << " websites in the database" << endl;
            cout << endl;
        }
        else if (testOpt == "4") { // adds a website to the list
            cout << "Which website would you like to add to our list?" << endl;
            cout << endl;
            cin >> websiteOption;
            cout << endl;
            cout << "Is the website malicious? Enter 0 for 'no', enter 1 for 'yes', enter 2 for 'not sure'" << endl;
            cout << endl;
            cin >> testOpt;
            cout << endl;

            while (true) {
                if (testOpt == "0" || testOpt == "1" || testOpt == "2") {
                    break;
                }
                cout << "Not a valid option. Please try again." << endl;
                cin >> testOpt;
            }

            if (testOpt == "0") { // appends to the vector, map and unordered map with mal value 0
                test.insertWebsiteInto2DVector(websiteOption, 0);
                test.insertWebsiteIntoMap(websiteOption, 0);
                test.insertWebsiteIntoUnorderedMap(websiteOption, 0);
            }
            else { // appends to the vector, map and unordered map with mal value 0
                test.insertWebsiteInto2DVector(websiteOption, 1);
                test.insertWebsiteIntoMap(websiteOption, 1);
                test.insertWebsiteIntoUnorderedMap(websiteOption, 1);
            }
        }
        else if (testOpt == "5") { // exit option
            break;
        }
        else { // discards invalid input
            cout << "Not a valid option. Please try again." << endl;
        }

        cout << endl;
    }


    return 0;
}
