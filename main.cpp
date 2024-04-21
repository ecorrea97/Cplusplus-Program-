#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class FrequencyCounter {
private:
    map<string, int> frequencyMap; // Map to store word frequencies

public:
    // Count frequencies of words from the input file
    void countFrequencies(const string& filename) {
        ifstream file(filename); // Open input file
        string word;

        // Read words and count frequencies
        while (file >> word) {
            frequencyMap[word]++;
        }
    }

    // Get frequency of a specific word
    int getFrequency(const string& word) {
        return frequencyMap[word];
    }
    // Print all word frequencies
    void printFrequencies() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Print histogram of word frequencies
    void printHistogram() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " ";
            // Print asterisks for frequency
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    // Create a backup file with word frequencies
    void createBackup(const string& backupFilename) {
        ofstream backupFile(backupFilename); // Open output file
        for (const auto& pair : frequencyMap) {
            backupFile << pair.first << " " << pair.second << endl;
        }
    }
};
class Main {
private:
    FrequencyCounter counter;

public:
    // Display menu options
    void displayMenu() {
        cout << "\nMenu Options:" << endl;
        cout << "1. Search for a word and get its frequency" << endl;
        cout << "2. Print list of all items with their frequencies" << endl;
        cout << "3. Print histogram of item frequencies" << endl;
        cout << "4. Exit\n" << endl;
    }

    // Handle user choice from menu
    void handleOption(int option) {
        switch (option) {
            case 1: {
                string word;
                cout << "\nEnter the word to search for: ";
                cin >> word;
                int frequency = counter.getFrequency(word);
                cout << "\nFrequency of " << word << ": " << frequency << endl;
                break;
            }
            case 2:
                cout << endl;
                counter.printFrequencies();
                break;
            case 3:
                cout << endl;
                counter.printHistogram();
                break;
            case 4:
                cout << endl;
                counter.createBackup("frequency.dat");
                cout << "Exiting program." << endl;
                exit(0);
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    // Run the program
    void run(const string& filename) {
        counter.countFrequencies(filename); // Count frequencies from input file
        int option;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            while (!(cin >> option)) { // Input validation
                cout << "Invalid input. Please enter a valid choice: ";
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            handleOption(option);
        } while (option != 4); // Continue until user chooses to exit
    }
};

int main() {
    Main main;
    main.run("CS210_Project_Three_Input_File.txt"); // Run program with input file
    return 0;
}