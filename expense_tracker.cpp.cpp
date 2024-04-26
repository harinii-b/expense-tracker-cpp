#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> readCSVData(const string& filename) {
    ifstream file(filename);

    vector<vector<string>> data;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> tokens;

        string token;
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        data.push_back(tokens);
    }

    file.close();

    return data;
}

double calculateTotalCost(const vector<vector<string>>& data) {
    double totalCost = 0.0;

    for (int i = 1; i < data.size(); ++i) {
        const auto &row = data[i];

        if (row.size() > 3) { 
            istringstream price(row[3]);
            double cost;

            if (price >> cost) {
                totalCost += cost;
            } else {
                cerr << "Error converting cost to double: " << row[3] << endl;
            }
        } 
    }

    return totalCost;
}


double displayCSVData(const vector<vector<string>>& data,int num) {

  cout<<"inside function that shows above a particular value" <<endl; 

    for (size_t i = 1; i < data.size(); ++i) {
        const auto &row = data[i];

        if (row.size() > 3) { 
            istringstream price(row[3]);
            double cost;

            if (price >> cost) {
                if(cost>num)
                {
                    // cout << "Row " << i + 1 ;
                    for (const auto &col : row) {
                        cout << col << "\t";
                    }
                    cout<<endl<<endl<<endl;
                }
            } else {
                cerr << "Error converting cost to double: " << row[3] << endl;
            }
        }
    }

    
}

void displayCSVData(const vector<vector<string>>& data) {
      cout<<"inside function that shows all values" <<endl; 

    for (const auto &row : data) {
        for (const auto &col : row) {
            cout << col << "\t";
        }
        cout << endl<<endl;
    }
}

void writeToCSV(const string &filename, const vector<vector<string>> &data) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Failed to open the file for writing." << endl;
        return;
    }

    for (const auto &row : data) {
        for (int i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
    cout << "Data has been appended to " << filename << " successfully."<<endl<<endl<<endl;
}

double calculateTotalCost(const vector<vector<string>>& data, const string& category) {
    double totalCost = 0.0;
    for (int i = 1; i < data.size(); ++i) {
        const auto& row = data[i];//iterate over rows starting from 1

		//row[3] cause amount is in index 1
        if (row.size() > 3 && row[1] == category) { 
            istringstream costcsv(row[3]); // cause cost is in 4th column
            double cost;

            if (costcsv >> cost) {
                totalCost += cost;
            } else {
                cerr << "Error converting cost to double: " << row[3] << " in row " << i + 1 << endl;
            }
        }
    }

    return totalCost;
}



int main() {
    string filename = "expense_tracker.csv";
    vector<vector<string>> csvData = readCSVData(filename);

    while (true) {
        cout << "1. Display all expenses\n"
             << "2. Display all Records, Calculate and display total cost\n"
             << "3. Total cost in a particular category\n"
             << "4. Display records with cost above a certain threshold\n"
             << "5. Write (Append) Record to file\n"
             << "6. Exit\n"
             <<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            displayCSVData(readCSVData(filename));
            break;
        case 2:
            cout << "Total cost is " << calculateTotalCost(readCSVData(filename)) << endl<<endl<<endl;
            break;
        case 3: {
            string categoryToFind;
            cout << "Enter the category: ";
            cin >> categoryToFind;
            cout << "Total expense in the category \"" << categoryToFind << "\": "
                 << calculateTotalCost(readCSVData(filename), categoryToFind) << endl<<endl<<endl;
            break;
        }
        case 4: {
            double num;
            cout << "Enter the threshold: ";
            cin >> num;
            displayCSVData(readCSVData(filename), num);
            break;
        }
        case 5: {
            vector<string> userInput;
            string input;

            for (int i = 0; i < 4; ++i) {
                cout << "Enter value for column " << i + 1 << ": ";
                cin.ignore(); // Ignore newline character from the previous input
                getline(cin, input);
                userInput.push_back(input);
            }

            writeToCSV(filename, {userInput});
            break;
        }

        case 6:
            cout << "Exiting the program." << endl;
            return 0;
        

        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}