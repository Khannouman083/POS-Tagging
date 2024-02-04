#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

// Struct for handling file operations
struct FileHandler {
    string toStore;
    string myText;

    // Read words from a file and return them in a vector
    vector<string> read(string fileName) {
        vector<string> words;
        ifstream file(fileName);
        string word;
        while (file >> word) {
            words.push_back(word);
        }
        return words;
    }

    // Write a new word to the file
    void write(string fileName) {
        ifstream readFile(fileName);
        vector<string> update;
        while (!readFile.eof()) {
            cin.ignore();
            getline(readFile, myText);
            update.push_back(myText);
        }
        string allString = "";
        for (auto stringVec : update) {
            allString = allString + " " + stringVec;
        }
        string fileWords = allString;
        cout << "Write to store: ";
        getline(cin, toStore);
        fileWords = fileWords + " " + toStore;

        ofstream writeFile(fileName);
        writeFile << fileWords;
    }

    // Find specific words in a paragraph and print them
    void find(vector<string> var, string paragraph) {
        istringstream iss(paragraph);
        string s;

        while (getline(iss, s, ' ')) {
            string word = s.c_str();
            if (count(var.begin(), var.end(), word)) {
                cout << word << ", ";
            }
        }
        cout << endl;
    }
};

// Base class for different parts of speech
class PartOfSpeech {
public:
    virtual vector<string> read() = 0;
    virtual void write() = 0;
    virtual void find(vector<string> words, string paragraph) = 0;
};

// Derived class for verbs
class Verb : public PartOfSpeech {
public:
    vector<string> read() override {
        FileHandler fileHandler;
        return fileHandler.read("verb.txt");
    }

    void write() override {
        FileHandler fileHandler;
        fileHandler.write("verb.txt");
    }

    void find(vector<string> verbs, string paragraph) override {
        cout << "Verb: ";
        FileHandler fileHandler;
        fileHandler.find(verbs, paragraph);
    }
};

// Derived class for nouns
class Noun : public PartOfSpeech {
public:
    vector<string> read() override {
        FileHandler fileHandler;
        return fileHandler.read("noun.txt");
    }

    void write() override {
        FileHandler fileHandler;
        fileHandler.write("noun.txt");
    }

    void find(vector<string> nouns, string paragraph) override {
        cout << "Noun: ";
        FileHandler fileHandler;
        fileHandler.find(nouns, paragraph);
    }
};

// Derived class for articles
class Article : public PartOfSpeech {
public:
    vector<string> read() override {
        FileHandler fileHandler;
        return fileHandler.read("article.txt");
    }

    void write() override {
        FileHandler fileHandler;
        fileHandler.write("article.txt");
    }

    void find(vector<string> articles, string paragraph) override {
        cout << "Article: ";
        FileHandler fileHandler;
        fileHandler.find(articles, paragraph);
    }
};

// Derived class for pronouns
class Pronoun : public PartOfSpeech {
public:
    vector<string> read() override {
        FileHandler fileHandler;
        return fileHandler.read("pronoun.txt");
    }

    void write() override {
        FileHandler fileHandler;
        fileHandler.write("pronoun.txt");
    }

    void find(vector<string> pronouns, string paragraph) override {
        cout << "Pronoun: ";
        FileHandler fileHandler;
        fileHandler.find(pronouns, paragraph);
    }
};

// Derived class for prepositions
class Preposition : public PartOfSpeech {
public:
    vector<string> read() override {
        FileHandler fileHandler;
        return fileHandler.read("preposition.txt");
    }

    void write() override {
        FileHandler fileHandler;
        fileHandler.write("preposition.txt");
    }

    void find(vector<string> prepositions, string paragraph) override {
        cout << "Preposition: ";
        FileHandler fileHandler;
        fileHandler.find(prepositions, paragraph);
    }
};

// Function to display a banner at the top of the screen
void displayBanner() {
    cout << "===================================" << endl;
    cout << "      Part of Speech Tagging        " << endl;
    cout << "===================================" << endl;
}

// Function to animate a loading message
void animateLoading() {
    cout << "Loading";
    for (int i = 0; i < 3; ++i) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    cout << endl;
}

// Function to clear the terminal screen
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int main() {
    char cont;
    do {
        Verb verb;
        Noun noun;
        Article article;
        Pronoun pronoun;
        Preposition prep;

        vector<string> verbs = verb.read();
        vector<string> nouns = noun.read();
        vector<string> articles = article.read();
        vector<string> pronouns = pronoun.read();
        vector<string> preps = prep.read();

        char option;
        clearScreen();
        displayBanner();
        cout << "Please Select an option below"<<endl;
        cout << "For Updating: 1 For Finding: 2"<<endl;
        cout << "Enter Your Choice:";

        cin >> option;

        if (option == '1') {
            char addOpt;
            cout << "For Verb adding, Press 'v'"<<endl;
            cout<<"For noun adding, Press 'n'"<<endl;
            cout<<"Enter your Choice:";
            cin >> addOpt;

            clearScreen();
            displayBanner();
            animateLoading();

            if (addOpt == 'v') {
                verb.write();
            } else if (addOpt == 'n') {
                noun.write();
            } else {
                cout << "Invalid option." << endl;
            }
        } else if (option == '2') {
            string paragraph;
            cout << "Enter a paragraph or word: "<<endl;
            cout<<">";
            cin.ignore();
            getline(cin, paragraph);

            clearScreen();
            displayBanner();
            animateLoading();

            verb.find(verbs, paragraph);
            noun.find(nouns, paragraph);
            article.find(articles, paragraph);
            pronoun.find(pronouns, paragraph);
            prep.find(preps, paragraph);
        } else {
            cout << "Invalid option." << endl;
        }

        cout << endl << "To continue, press 'c': ";
        cin >> cont;
    } while (cont == 'c');

    return 0;
}
