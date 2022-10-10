#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Method to read the file into a string
string readFileToString(const string& path) {
	ifstream input_f(path);

	// Check that the file was opened
	if (!input_f.is_open()) {
		cerr << "Could not open the file: '" << path << "'" << endl;
		exit(EXIT_FAILURE);
	}

	// Return the string with the file contents in
	return string((istreambuf_iterator<char>(input_f)), istreambuf_iterator<char>());
}

// Comparing two strings alphabetically
bool compare(string a, string b) {
	if (a.compare(b) < 0) {
		return true;
	}
	else { return false; }
}

string findWordFreq(vector<string> words, int length) {
	int count = 0;
	string word_freq;

	// Loop through sorted list of words to find the frequency of each word
	for (int n = 0; n < length; n++) {
		int count = 1;
		string line = words[n] + ": ";

		// Checks how many of the same current word appear
		while (true) {
			if (n + count < length) {
				if (words[n] == words[n + count]) {
					count++;
				}
				else { break; }
			}
			else { break; }
		}

		line += to_string(count) + "\n";
		word_freq += line;
		n += count - 1;
	}

	return word_freq;
}

int main() {
	// Assigning variables
	string input_f_path = "input.txt";
	string text_f;
	vector<string> words;
	int sentences = 0;

	// Call function to read file into string
	text_f = readFileToString(input_f_path);
	cout << text_f << endl;

	// Looping through string to pick out words
	string word;
	for (char c : text_f) {
		// Normalise to lowercase
		if (toascii(c) >= 65 && toascii(c) <= 132) {
			c = char(tolower(c));
		}

		// Check character isn't space or punctuation
		if (toascii(c) >= 97 && toascii(c) <= 122) {
			word += c;
		}
		// If it is, add the word to the words list
		else {
			// If end of sentence add to sentence counter
			if (c == '.' || c == '!' || c == '?') {
				sentences += 1;
			}
			if (word != "") {
				words.push_back(word);
			}
			word = "";
		}
	}

	// Sort the word list alphabetically
	sort(words.begin(), words.end(), compare);

	// Output to console
	int length = words.size();
	cout << "\nSentences: " << sentences << endl;
	cout << "Words: " << length << "\n" << endl;

	cout << findWordFreq(words, length) << endl;
}