#include "Website.h"
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


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


		unordered_map<string, pair<string,bool>>::iterator itr;
		itr = testUM.find(website);
		if (itr != testUM.end()) {
			duplicates.push_back(make_pair(webBeforeRemoveHTTPs,itr->second.first));
		}
		else {
			v[index].push_back(make_pair(website, malicious));
			count++;
		}
		m[website] = malicious;
		um[website] = malicious;
		testUM[website] = make_pair(webBeforeRemoveHTTPs, malicious);

		// Debug
		//cout << "num = " << num << endl;
		//cout << "website = " << website << endl;
		//cout << "benignOrMalicious = " << benignOrMalicious << endl;
		//cout << "malicious = " << malicious << endl;

	}

	for (unsigned int a = 0; a < v.size(); a++) {
		quickSort(v[a],0,v[a].size()-1);
	}


	// Debug
	//cout << "vector size = " << count << endl;
	//cout << "map size = " << m.size() << endl;
	//cout << "unordered_map size = " << um.size() << endl;
	cout << endl;

}

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

int main() {

	vector<vector<pair<string, bool>>> v; // 2D vector
	map<string, bool> m;
	unordered_map<string, bool> um;

	string fileName = "urldataMain.csv";


	auto start = high_resolution_clock::now();


	readData(fileName, v, m, um);
	Website test(v, m, um);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);


	cout << "Execution time = " << duration.count() << " milliseconds = " << (double) duration.count() / (double) 1000 << " seconds." << endl;

	string testOpt;
	int n = 0;
	string websiteOption;
	cout << "Welcome to Malicious Website Sorter" << endl;
	while (testOpt != "5") {
		printMenu();
		cin >> testOpt;
		//n = stoi(testOpt);
		cout << endl;

		// Option 1
		if (testOpt == "1") {

			cout << "Which website would you like to search for? Make sure you include www. in the website address" << endl;
			cin >> websiteOption;
			cout << endl;
			while (true) {
				cout << "Which Data Structure would you like to search in " << endl;
				printOption();
				cin >> testOpt;
				bool res;
				if (testOpt == "1") {
					start = high_resolution_clock::now();

					res = test.getMalicious2DVector(websiteOption);
					if (res != -1) {
						if (res == 1) {
							cout << websiteOption << " is malicious according to our databases." << endl;
						}
						else {
							cout << websiteOption << " is safe according to our databases." << endl;
						}
					}

					stop = high_resolution_clock::now();
					duration = duration_cast<milliseconds>(stop - start);
					cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
					cout << " seconds " << endl;

					break;
				}
				else if (testOpt == "2") {

					start = high_resolution_clock::now();

					res = test.getMaliciousMap(websiteOption);
					if (res != -1) {
						if (res == 1) {
							cout << websiteOption << " is malicious according to our databases." << endl;
						}
						else {
							cout << websiteOption << " is safe according to our databases." << endl;
						}
					}

					stop = high_resolution_clock::now();
					duration = duration_cast<milliseconds>(stop - start);
					cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
					cout << " seconds " << endl;

					break;
				}
				else if (testOpt == "3") {

					start = high_resolution_clock::now();

					res = test.getMaliciousUnorderedMap(websiteOption);
					if (res != -1) {
						if (res == 1) {
							cout << websiteOption << " is malicious according to our databases." << endl;
						}
						else {
							cout << websiteOption << " is safe according to our databases." << endl;
						}
					}

					stop = high_resolution_clock::now();
					duration = duration_cast<milliseconds>(stop - start);
					cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
					cout << " seconds " << endl;

					break;
				}
				else {
					cout << "Not a valid option. Please try again." << endl;
				}
			}
		}

		// Option 2
		else if (testOpt == "2") {
			cout << "Enter first letter of website: " << endl;
			cin >> websiteOption;
			while (true) {
				cout << "Which Data Structure would you like to search in " << endl;
				printOption();
				cin >> testOpt;
				bool res;
				if (testOpt == "1") {
					start = high_resolution_clock::now();

					test.print2DVectorWebsiteListByChar(websiteOption.at(0));

					stop = high_resolution_clock::now();
					duration = duration_cast<milliseconds>(stop - start);
					cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
					cout << " seconds " << endl;

					break;
				}
				else if (testOpt == "2") {

					start = high_resolution_clock::now();

					test.printMapWebsiteListByChar(websiteOption.at(0));

					stop = high_resolution_clock::now();
					duration = duration_cast<milliseconds>(stop - start);
					cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
					cout << " seconds " << endl;
					break;
				}
				else if (testOpt == "3") {

					start = high_resolution_clock::now();


					test.printUnorderedMapWebsiteListByChar(websiteOption.at(0));

					stop = high_resolution_clock::now();
					duration = duration_cast<milliseconds>(stop - start);
					cout << "Execution Time: " << duration.count() << " milliseconds = " << (double)duration.count() / (double)1000;
					cout << " seconds " << endl;

					break;
				}
				else {
					cout << "Not a valid option. Please try again." << endl;
				}
			}
		}
		else if (testOpt == "3") {
			cout << "There are " << um.size() << " websites in the database" << endl;
		}
		else if (testOpt == "4") {
			cout << "Which website would you like to add to our list?" << endl;
			cin >> websiteOption;
			cout << "Is the website malicious? Enter 0 for 'no', enter 1 for 'yes', enter 2 for 'not sure'" << endl;
			cin >> testOpt;

			while (true) {
				if (testOpt == "0" || testOpt == "1" || testOpt == "2") {
					break;
				}
				cout << "Not a valid option. Please try again." << endl;
				cin >> testOpt;
			}

			if (testOpt == "0") {
				test.insertWebsiteInto2DVector(websiteOption, 0);
				test.insertWebsiteIntoMap(websiteOption, 0);
				test.insertWebsiteIntoUnorderedMap(websiteOption, 0);
			}
			else {
				test.insertWebsiteInto2DVector(websiteOption, 1);
				test.insertWebsiteIntoMap(websiteOption, 1);
				test.insertWebsiteIntoUnorderedMap(websiteOption, 1);
			}
		}
		else if (testOpt == "5") {
			break;
		}
		else {
			cout << "Not a valid option. Please try again." << endl;
		}

		cout << endl;
	}


	return 0;
}
