/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "queue.h" 
#include "map.h"
#include "random.h"
#include "filelib.h"
using namespace std;

/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "queue.h" 
#include "map.h"
#include "random.h"
#include "filelib.h"
using namespace std;

const int TEXT_LENGTH = 2000; 

/*
	Analyzing each model length string and documenting the chars that come after it. 
*/
void analyze(string str, char ch, Map <string, Vector<char> > & frequencies) { 
	Vector <char> vec; 
	if (frequencies.containsKey(str.substr(0,str.length()-1))) { 
		frequencies[str.substr(0,str.length()-1)].add(ch);
	} else { 
		Vector <char> vec;
		vec.add(ch);
		frequencies.put(str.substr(0,str.length()-1),vec);
	}
} 
/*
	finding the most frequent string in the text
*/

string mostFrequent(Map <string, Vector<char> > frequencies) { 
	string mostFrequent = ""; 
	int longestVec = 0; 
	foreach (string str in frequencies) { 
		Vector <char> currentVector = frequencies.get(str); 
		if (currentVector.size() > longestVec) { 
			longestVec = currentVector.size(); 
			mostFrequent = str; 
		}
	}
	return mostFrequent;
}

/*
	randomly choosing the following char
*/

char randomizeChar(string str, Map < string, Vector<char> > frequencies) { 
	Vector <char> vec = frequencies[str]; 
	int maxIndex = vec.size() - 1; 
	int index = randomInteger(0,maxIndex); 
	return vec[index]; 
}

/*
	generating the text
*/

string generatedText(Map < string, Vector<char> > frequencies,int model) { 
	string result = ""; 
	string mostFreq = mostFrequent(frequencies);
	result += mostFreq; 
	while(true) { 
		string currentStr = result.substr(result.length()-model, model); 
		char nextChar = randomizeChar(currentStr, frequencies); 
		result += nextChar; 
		if (result.length() == TEXT_LENGTH) break; 
	}
	return result; 
}


int main() { 
	string currentStr = ""; 
	string previousStr = ""; 
	Map <string,Vector<char> > frequencies; 
	/*
		getting the file and the model from the user. 
	*/
	int model;
	while(true) { 
		model = getInteger ("the model has to be between 1 and 10: ");
		if (model > 0 && model <=10) break;
	}	
	ifstream infile;
	promptUserForFile(infile,"input file: ");
	/*
		reading each char from the file and analyzing it. 
	*/
	char ch; 
	while(infile.get(ch)) {
		currentStr += ch;
		if(currentStr.length() == model+1) {
			analyze(currentStr, ch, frequencies);
			currentStr = currentStr.substr(1);
		}
	}
	infile.close(); 
	cout<<generatedText(frequencies,model)<<endl;
	return 0; 
}
