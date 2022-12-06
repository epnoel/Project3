#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

int binarySearchWebsiteMaliciousness(vector<pair<string, bool>> v, string website) {
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

	pair<string, bool> pivot = v.at(start);

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

void quickSort(vector<pair<string, bool>>& v, int start, int end)
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
		linkString = linkString.substr(found3 + w.size(), linkString.size());
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

void iterateMap(map<string, bool> m, char c) {

	map<string, bool>::iterator itr;
	cout << "Website:                 " << setw(20) << "Maliciousness:" << endl;
	for (itr = m.begin(); itr != m.end(); itr++) {
		if (itr->first[0] == c) {
			cout << itr->first << endl;
			cout << itr->second << endl;
		}
	}
}

void iterateUnorderedMap(unordered_map<string, bool> um, char c) {

	unordered_map<string, bool>::iterator itr;
	cout << "Website:                 " << setw(20) << "Maliciousness:" << endl;
	for (itr = um.begin(); itr != um.end(); itr++) {
		if (itr->first[0] == c) {
			cout << itr->first << endl;
			cout << itr->second << endl;
		}
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

	int getMalicious2DVector(string websiteName) {

		string concatWebsite = websiteName;

		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);
		int index = getIndex(concatWebsite);

		int mal = binarySearchWebsiteMaliciousness(v[index], concatWebsite);

		if (mal != -1) {
			return mal;
		}


		cout << "Sorry. " << websiteName << " could not be found" << endl;
		return -1;
	}

	int getMaliciousMap(string websiteName) {

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


	int getMaliciousUnorderedMap(string websiteName) {

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
		iterateMap(m, c);
	}

	void printUnorderedMapWebsiteListByChar(char c) {
		iterateUnorderedMap(um, c);
	}

	void insertWebsiteInto2DVector(string website, bool mal) {
		string concatWebsite = website;
		removeHTTPSPart(concatWebsite);
		removeWWWPart(concatWebsite);

		int index = 0;
		index = getIndex(concatWebsite);

		if (binarySearchWebsiteMaliciousness(v[index], website) == -1) {
			v[index].push_back(make_pair(concatWebsite, mal));
			quickSort(v[index], 0, v[index].size() - 1);
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
