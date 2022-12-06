#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int binarySearchWebsiteMaliciousness(vector<pair<string,bool>> v, string website) {
	int low = 0;
	int high = v.size();
	int average = 0;

	int times = 0;

	while (low < high && times < v.size()) {
		average = (low + high) / 2;

		if (v.at(average).first == website) {
			return v[average].second;
		}
		else if (website < v.at(average).first) {
			high = average;
		}
		else {
			low = average;
		}

		times++;

	}

	return -1;

}

int partition(vector<pair<string, bool>>& v, int start, int end)
{

	pair<string,bool> pivot = v.at(start);

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (v.at(i).first <= pivot.first)
			count++;
	}

	int pivotIndex = start + count;
	pair<string, bool> temp = v.at(pivotIndex);
	v.at(pivotIndex) = v.at(start);
	v.at(start) = temp;

	int i = start;
	int j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (v.at(i).first <= pivot.first) {
			i++;
		}

		while (v.at(j).first > pivot.first) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(v[i++], v[j--]);
		}
	}

	return pivotIndex;
}

void quickSort(vector<pair<string,bool>> &v, int start, int end)
{

	if (start >= end) {
		return;
	}
	int pos = partition(v, start, end);

	quickSort(v, start, pos - 1);

	quickSort(v, pos + 1, end);
}

void removeHTTPSPart(string& linkString) {

	string https = "https://";

	size_t found = linkString.find(https);

	if (found != string::npos) {

		linkString = linkString.substr(found + https.size(), linkString.size());
		return;

		// Debug
		//cout << "Removed " << https << " at " << found << endl;
	}

	string http = "http://";

	size_t found2 = linkString.find(http);

	if (found2 != string::npos) {
		linkString = linkString.substr(found2 + http.size(), linkString.size());
		return;

		// Debug
		//cout << "Removed " << http << " at " << found2 << endl;

	}

}

void removeWWWPart(string& linkString) {
	string w = "www.";

	size_t found3 = linkString.find(w);

	if (found3 != string::npos) {
		linkString = linkString.substr(found3+w.size(), linkString.size());
		return;
	}
}

int getIndex(string website) {
	removeHTTPSPart(website);
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

	return index;

}

void printWebsitesByChar(vector<vector<pair<string, bool>>> v, char c) {
	string temp = "";
	temp += c;
	int index = getIndex(temp);

	int count = 0;

	cout << "Website:                 " << setw(40) << "Maliciousness:" << endl;
	for (unsigned int i = 0; i < v[index].size(); i++) {
		count++;
		cout << v[index].at(i).first << endl;
		cout << v[index].at(i).second << endl;

	}

}

class Website {
public:
	Website() {
		v.resize(36);
	}

	Website(vector<vector<pair<string, bool>>>& v, map<string, bool>& m, unordered_map<string, bool>& um) {
		this->v = v;
		this->m = m;
		this->um = um;
	}

	void set2DVector(vector<vector<pair<string, bool>>>& v) {
		this->v = v;
	}

	void setMap(map<string, bool>& m) {
		this->m = m;
	}

	void setUnorderedMap(unordered_map<string, bool>& um) {
		this->um = um;
	}

	bool getMalicious2DVector(string websiteName) {

		string concatWebsite = websiteName;

		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);
		int index = getIndex(concatWebsite);

		int mal = binarySearchWebsiteMaliciousness(v[index], concatWebsite);

		if (mal != -1) {
			return mal;
		}


		cout << "Sorry. " << websiteName << " could not be found" << endl;
		//v[index].push_back(make_pair(concatWebsite, 1));
		return -1;
	}

	bool getMaliciousMap(string websiteName) {

		string concatWebsite = websiteName;

		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);

		map<string, bool>::iterator itr;
		itr = m.find(concatWebsite);

		if (itr != m.end()) {
			return itr->second;
		}


		cout << "Sorry. " << websiteName << " could not be found" << endl;
		return -1;
	}


	bool getMaliciousUnorderedMap(string websiteName) {

		string concatWebsite = websiteName;

		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);

		unordered_map<string, bool>::iterator itr;
		itr = um.find(concatWebsite);

		if (itr != um.end()) {
			return itr->second;
		}

		cout << "Sorry. " << websiteName << " could not be found" << endl;
		return -1;
	}

	void print2DVectorWebsiteListByChar(char c) {
		printWebsitesByChar(v, c);
	}

	void printMapWebsiteListByChar(char c) {
		map<string, bool>::iterator itr;
		for (itr = m.begin(); itr != m.end(); itr++) {
			if (itr->first.at(0) == c) {
				cout << "Website:                 " << setw(20) << "Maliciousness:" << endl;
				cout << itr->first << "           " << itr->second << endl;
			}
		}
	}

	void printUnorderedMapWebsiteListByChar(char c) {
		unordered_map<string, bool>::iterator itr;
		for (itr = um.begin(); itr != um.end(); itr++) {
			if (itr->first.at(0) == c) {
				cout << "Website:                 " << setw(20) << "Maliciousness:" << endl;
				cout << itr->first << "           " << itr->second << endl;
			}
		}
	}

	void insertWebsiteInto2DVector(string website, bool mal) {
		string concatWebsite = website;
		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);

		int index = 0;
		index = getIndex(concatWebsite);

		if (binarySearchWebsiteMaliciousness(v[index],website) == -1) {
			v[index].push_back(make_pair(concatWebsite, mal));
			cout << website << " has been successfully added to our database." << endl;
		}
		else {
			cout << "This website cannot be added. It is already in the database." << endl;
		}

	}

	void insertWebsiteIntoMap(string website, bool mal) {
		string concatWebsite = website;
		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);

		map<string, bool>::iterator itr;
		itr = m.find(concatWebsite);

		if (itr == m.end()) {
			m[concatWebsite] = mal;
			//cout << website << " has been successfully added to our database." << endl;
		}
		else {
			//cout << "This website cannot be added. It is already in the database." << endl;
		}

	}

	void insertWebsiteIntoUnorderedMap(string website, bool mal) {
		string concatWebsite = website;
		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);

		unordered_map<string, bool>::iterator itr;
		itr = um.find(concatWebsite);

		if (itr == um.end()) {
			um[concatWebsite] = mal;
			//cout << website << " has been successfully added to our database." << endl;
		}
		else {
			//cout << "This website cannot be added. It is already in the database." << endl;
		}
	}

private:
	vector<vector<pair<string, bool>>> v; // 2D vector
	map<string, bool> m;
	unordered_map<string, bool> um;
};


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
	cout << "vector size = " << count << endl;
	cout << "map size = " << m.size() << endl;
	cout << "unordered_map size = " << um.size() << endl;
	cout << endl;
	//cout << "Duplicates:" << endl;

	//for (unsigned int i = 0; i < duplicates.size(); i++) {
	//	cout << "--" << duplicates.at(i).first << endl;
	//	cout << "**" << duplicates.at(i).second << endl;
	//}

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
