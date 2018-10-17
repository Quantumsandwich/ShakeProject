#include <sstream> // for istringstream
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <iostream>
#include "shake.h"
#include "english_stem.h"

using namespace std;

//This function removes specials
string RemoveSpecials(string str) {
  int i = 0, len = str.length();
  while (i < len) {
    char c = str[i];
    if (((c >= '0')&&(c <= '9')) || ((c >= 'A')&&(c <= 'Z')) || ((c >= 'a')&&(c <= 'z')) || c == '\'' || c == ' ') {
      if ((c >= 'A')&&(c <= 'Z')) str[i] += 32; //Assuming dictionary contains small letters only.
      ++i;
    } else {
      str.erase(i, 1);
      --len;
    }
  }
  return str;
}


int shake::doall(string theword){


  string filename = "/home/class/SoftDev/Shakespeare/Shakespeare.txt";
  
  
	theword = RemoveSpecials(theword);
	stemming::english_stem<char, std::char_traits<char> > StemEnglish;
	StemEnglish(theword);
	


  map<string, vector<int> > refs; // The map of words/references
  string word, line;
  ifstream infile(filename); // open the file
  int position = 0;
  while (!infile.fail()) {
    getline(infile, line); // get the next line of code
    line = RemoveSpecials(line);
    istringstream lineStream(line); // Create a string stream of the line
    while (lineStream >> word) { // get the next word
    		StemEnglish(word);
      refs[word].push_back(position); // push the word and the line position on the vector for this word
      //cout << position << "\n";//i used this for debugging to make sure position was actually changing
    }
    position = infile.tellg(); // get the poistion of the next line
  }
  infile.close();
  infile.open(filename);
  //At this point I have my map built
  char goagain = 'y';
  while(goagain=='y' || goagain=='Y'){

    theword = RemoveSpecials(theword);

    int howmany = 10;	//How many to search for

    vector<int> values;
    values = refs[theword];
    //At this point I have a vector "values" with entries of the indicies of each occurance of a word.
    int i = 0;
    int results = 0;
    while(i<howmany){

      infile.seekg(values[i], infile.beg);
      getline(infile, line); // get the next line of code
      cout << line << "<br>";

      i++;
      if(values[i]==values.back()){break;}
    }
    
    while(1){
    		infile.seekg(values[results], infile.beg);
      getline(infile, line); // get the next line of code
    		results++;
    		if(values[results]==values.back()){break;}
    	}
		cout << "<br>Showing results 1 through " << i << " out of " << (results);
    goagain = 'n';


  }


	return 1;
}
