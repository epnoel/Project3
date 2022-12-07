#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

// binarySearchWebsiteMaliciousness
// inputs: 2D vector v, string website URL
// returns the malciousness of the website being searched by performing Binary Search on the vector v
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
/**************************************************/
// partition
// inputs vector v, start index, end index
// returns pivotIndex which is where the partition happens for quickSort
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
// quicksort
// inputs: vector v, start and end index
// performs quicksort recursively using partition function
void quickSort(vector<pair<string, bool>>& v, int start, int end)
{

    if (start >= end) {
        return;
    }
    int pos = partition(v, start, end);

    quickSort(v, start, pos - 1);

    quickSort(v, pos + 1, end);
}

/**************************************************/
// Helper functions to remove the www and https part from the websiteNames
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
/**************************************************/

// Helper function to help get index of the first character of the string website
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
/**************************************************/

// helper function to iterate through the 2D vector that stores vector of the website list
// based on the first character of the website name
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


// Helper functions to iterate through the map and unordered_map of websites
// prints out the website and maliciousness
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
/**************************************************/

/* Class Website created
 * attributes: 2D vector v, map m, unordered_map um
 * methods: constructors, setter functions: set2Dvector, setMap, setUnorderedMap,
 * methods: getMalicious2DVector, getMaliciousMap, getMaliciousUnorderedMap
 * methods: print2DVector, printMap, printUnorderedMap
 * methods: three methods to insert into the vector v, map m, and unordered map um
 */
class Website {
public:
    // constructor resizes 2D vector to size 36
    Website() {
        v.resize(36);
    }
    // constructor with already given vector v, map m, and unordered map um
    Website(vector<vector<pair<string, bool>>>& v, map<string, bool>& m, unordered_map<string, bool>& um) {
        this->v = v;
        this->m = m;
        this->um = um;
    }
    // sets the vector v with passed in 2D vector v
    void set2DVector(vector<vector<pair<string, bool>>>& v) {
        this->v = v;
    }
    // sets the map attribute of the class to the passed in map
    void setMap(map<string, bool>& m) {
        this->m = m;
    }
    // sets the unordered map attribute of the class to the passed in unordered map
    void setUnorderedMap(unordered_map<string, bool>& um) {
        this->um = um;
    }
    // getMalicious2DVector
    // returns int value -1 if the value of the website is not found in the vector
    // performs binary search on the vector
    //
    int getMalicious2DVector(string websiteName) {
        // dummy variable concatWebsite stores the passed in value
        string concatWebsite = websiteName;
        // cleaning the variable concatWebsite to remove www and https from the URL
        removeHTTPSPart(concatWebsite);
        removeWWWPart(concatWebsite);
        int index = getIndex(concatWebsite); //returns the index of the website's first character

        int mal = binarySearchWebsiteMaliciousness(v[index], concatWebsite);

        if (mal != -1) {
            return mal;
        }


        cout << "Sorry. " << websiteName << " could not be found" << endl;
        return -1;
    }
    // getMaliciousMap
    // takes in string websiteName
    // uses the find function in the STL Container map to set an iterator to the found value
    // returns -1 if the websiteName is not in the map
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

    // getMaliciousUnorderedMap
    // takes in string websiteName
    // uses the find function for the STL container unordered_map
    // returns -1 if the websiteName is not found in the unordered_map
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

    // print functions each using helper functions for each data structure
    // check the helper functions for documentation
    void print2DVectorWebsiteListByChar(char c) {
        printWebsitesByChar(v, c);
    }

    void printMapWebsiteListByChar(char c) {
        iterateMap(m, c);
    }

    void printUnorderedMapWebsiteListByChar(char c) {
        iterateUnorderedMap(um, c);
    }

    // insertWebsiteInto2DVector
    // takes in website and the boolean value for whether it is malicious or not
    void insertWebsiteInto2DVector(string website, bool mal) {
        // cleaning the input by removing https and www
        string concatWebsite = website;
        removeHTTPSPart(concatWebsite);
        removeWWWPart(concatWebsite);
        // getting the index of the first letter of the website so we know where to input
        int index = 0;
        index = getIndex(concatWebsite);
        // if not found in the vector then add the website to the vector with its mal value
        // runs a quicksort on the vector stored after each entry into the vector
        if (binarySearchWebsiteMaliciousness(v[index], website) == -1) {
            v[index].push_back(make_pair(concatWebsite, mal));
            quickSort(v[index], 0, v[index].size() - 1);
            cout << website << " has been successfully added to our database." << endl;
        }
        else {
            cout << "This website cannot be added. It is already in the database." << endl;
        }

    }

    // insertWebsiteIntoMap
    // performs insertion of the website name into the map m(websiteName, maliciousness)
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

    // insertWebsiteIntoUnorderedMap
    // performs insertion of the website name into the unordered map um
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

    // returns the size of the unordered map um
    int returnSize() {
        return um.size();
    }

private:
    // attributes contained by the class
    vector<vector<pair<string, bool>>> v; // 2D vector
    map<string, bool> m;
    unordered_map<string, bool> um;
};
