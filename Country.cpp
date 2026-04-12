#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct CountryInfo {
    string name;
    string capital;
    long population;
    double area;
    string continent;
    string currency;
    string officialLanguage;
    
    CountryInfo(string n, string c, long p, double a, 
                string cont, string curr, string lang)
        : name(n), capital(c), population(p), area(a), 
          continent(cont), currency(curr), officialLanguage(lang) {}
};

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

map<string, CountryInfo> createCountryDatabase() {
    map<string, CountryInfo> database;
    
    database["china"] = CountryInfo("China", "Beijing", 1411780000, 9640011, 
                                    "Asia", "Yuan", "Chinese");
    database["usa"] = CountryInfo("United States", "Washington D.C.", 331449281, 9372610, 
                                  "North America", "US Dollar", "English");
    database["japan"] = CountryInfo("Japan", "Tokyo", 125800000, 377975, 
                                     "Asia", "Yen", "Japanese");
    database["germany"] = CountryInfo("Germany", "Berlin", 83166711, 357588, 
                                      "Europe", "Euro", "German");
    database["brazil"] = CountryInfo("Brazil", "Brasilia", 213993437, 8515767, 
                                     "South America", "Real", "Portuguese");
    database["australia"] = CountryInfo("Australia", "Canberra", 25788200, 7692024, 
                                        "Oceania", "Australian Dollar", "English");
    database["egypt"] = CountryInfo("Egypt", "Cairo", 102334404, 1001450, 
                                    "Africa", "Egyptian Pound", "Arabic");
    database["india"] = CountryInfo("India", "New Delhi", 1393409038, 3287263, 
                                   "Asia", "Indian Rupee", "Hindi, English");
    database["france"] = CountryInfo("France", "Paris", 67750000, 551695, 
                                     "Europe", "Euro", "French");
    database["russia"] = CountryInfo("Russia", "Moscow", 146171015, 17098242, 
                                     "Europe/Asia", "Ruble", "Russian");
    
    return database;
}

void displayCountryInfo(const CountryInfo& country) {
    cout << "\n========== Country Information: " << country.name << " ==========\n";
    cout << "Capital: " << country.capital << endl;
    cout << "Population: " << country.population << " people" << endl;
    cout << "Area: " << country.area << " sq km" << endl;
    cout << "Continent: " << country.continent << endl;
    cout << "Currency: " << country.currency << endl;
    cout << "Official Language: " << country.officialLanguage << endl;
    cout << "==============================================\n";
}

void searchCountry(const map<string, CountryInfo>& database, const string& countryName) {
    string lowerName = toLower(countryName);
    
    auto it = database.find(lowerName);
    if (it != database.end()) {
        displayCountryInfo(it->second);
    } else {
        cout << "No exact match found for '" << countryName << "'." << endl;
        cout << "Possible countries: ";
        
        bool foundSimilar = false;
        for (const auto& pair : database) {
            if (pair.first.find(lowerName) != string::npos || 
                toLower(pair.second.name).find(lowerName) != string::npos) {
                cout << pair.second.name << " ";
                foundSimilar = true;
            }
        }
        
        if (!foundSimilar) {
            cout << "No related countries found in database.";
        }
        cout << endl;
    }
}

void showAvailableCountries(const map<string, CountryInfo>& database) {
    cout << "\nAvailable Countries List:\n";
    cout << "------------------------\n";
    
    int count = 1;
    for (const auto& pair : database) {
        cout << count++ << ". " << pair.second.name << endl;
    }
    cout << "------------------------\n";
}

int main() {
    map<string, CountryInfo> countryDB = createCountryDatabase();
    
    cout << "========== Country Information System ==========\n";
    cout << "Commands:\n";
    cout << "1. Enter country name to search (English name)\n";
    cout << "2. Enter 'list' to show all available countries\n";
    cout << "3. Enter 'exit' or 'quit' to exit program\n";
    cout << "==============================================\n";
    
    string input;
    while (true) {
        cout << "\nEnter country name or command: ";
        getline(cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        string lowerInput = toLower(input);
        if (lowerInput == "exit" || lowerInput == "quit") {
            cout << "Thank you for using Country Information System. Goodbye!\n";
            break;
        } else if (lowerInput == "list") {
            showAvailableCountries(countryDB);
        } else {
            searchCountry(countryDB, input);
        }
    }
    
    return 0;
}