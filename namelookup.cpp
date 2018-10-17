/***************************************************************************                   
 * namelookup.cpp  -  Program to display name statistics                                       
 *                                                                                             
 * copyright : (C) 2017 by Jim Skon                                                            
 *                                                                            
 * This program create an index US Census name                                       
 * Data on the frequency of names in response to requestes.                           
 * It then allows you to look up any name, giving the 10 closest matches               
 *                                                            
 *     
 *
 ***************************************************************************/
 
//I can add comments too!!! 
 
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
//#include "NameMap.h"
//#include "NameEntry.h"
#include "shake.h"
#include <string>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "english_stem.h"

#define XML_USE_STL

using namespace std;
using namespace cgicc; // Needed for AJAX functions.


int main() {
  // Object used for receiving AJAX call (and getting parameters)
  Cgicc cgi;    // Ajax object
  
  // Create AJAX objects to receive information from web page.
  form_iterator itname = cgi.getElement("name");

  // Retrieve the actual paramaters
  string name = **itname;

  
  /* send back the results */
  cout << "Content-Type: text/plain\n\n";
  
  int i = 0;
  shake m;
  i = m.doall(name);

  /* Results are comma delimited (name, percent, rank, name, ...) for up to 10 names */
return 0;
}

