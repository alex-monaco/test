#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<string> floodfill_operator(vector<string> inputlines,int yloc,int xloc, char newchar) {
  //Create a copy of the input
  vector<string> newlines = inputlines;
  //Create old character variable for reference
  string bchar = ".";
  char backgroundchar = bchar[0];
  newlines[yloc][xloc] = newchar;

  //Go through every character in the input file.
  for(unsigned int q=1;q<(newlines.size()-1);q++) {
    for(unsigned int i=1;i<(newlines[q].size()-1);i++) {
      //Make sure locations is at an old foreground character
      if (newlines[q][i] != backgroundchar&&newlines[q][i] != newchar){
        //Check if location is next to/above/below new foreground character
        if (newlines[q][i+1] == newchar||newlines[q][i-1] == newchar||newlines[q+1][i] == newchar||newlines[q-1][i] == newchar){
          //Place new character
          newlines[q][i] = newchar;
          //Set vector locations back to the start
          q=1;
          i=1;
        }
      }
    }
  }
  //Return the new changed copy of input
  return newlines;
}

vector<string> erosion_operator(vector<string> inputlines,char foregroundchar,char backgroundchar) {
  //Create a copy of the input
  vector<string> newlines = inputlines;

  //Go through every character in the input file.
  for(unsigned int q=0;q<inputlines.size();q++) {
    for(unsigned int i=0;i<inputlines[q].size();i++) {
      //Check if every charcter in plus grid around is a foreground character
      if (inputlines[q][i]==foregroundchar&&inputlines[q][i+1]==foregroundchar&&inputlines[q][i-1]==foregroundchar&&inputlines[q+1][i]==foregroundchar&&inputlines[q-1][i]==foregroundchar)
        //Place a foreground character
        newlines[q][i] = foregroundchar;
      else
        //If not, place a background character
        newlines[q][i] = backgroundchar;
    }
  }
  //Return the new changed copy of input
  return newlines;
}

vector<string> dilation_operator(vector<string> inputlines,char foregroundchar) {
  //Create a copy of the input
  vector<string> newlines = inputlines;

  //Go through every character in the input file.
  for(unsigned int q=1;q<(inputlines.size()-1);q++) {
    for(unsigned int i=1;i<(inputlines[q].size()-1);i++) {
      //Check for foreground character
      if (inputlines[q][i+1] == foregroundchar||inputlines[q][i-1] == foregroundchar||inputlines[q+1][i] == foregroundchar||inputlines[q-1][i] == foregroundchar)
        //Place new character
        newlines[q][i] = foregroundchar;
    }
  }
  //Return the new changed copy of input
  return newlines;
}

vector<string> replace_operator(vector<string> inputlines,char oldchar,char newchar) {
  //Create a copy of the input
  vector<string> newlines = inputlines;

  //Go through every character in the input file.
  for(unsigned int q=0;q<inputlines.size();q++) {
    for(unsigned int i=0;i<inputlines[q].size();i++) {
      //Check for original charcters
      if (inputlines[q][i] == oldchar) {
        //Replace old character with new character where if statement appplies (On copy)
        newlines[q][i] = newchar;
      }
    }
  }
  //Return the new changed copy of input
  return newlines;
}

int main(int argc, char* argv[])
{
  //Assign arguments to variables
  string inputfile = argv[1];
  string outputfile = argv[2];
  string operation_type = argv[3];

  //Establish vectors to store strings of lines from the input and a vector to write changed lines to.
  vector<string> inputlines;
  vector<string> newlines;
  //String to store characters from each line of the input.
  string line;

  //Open input and output file
  ifstream oldfile(inputfile.c_str());
  ofstream newfile(outputfile.c_str());

  //Read input file one line at a time
  while(getline(oldfile,line))
  {
    inputlines.push_back(line);
  }

  //Check which operation we are applying (if statments below)
  if(operation_type == "replace"){
    //Assign extra arguments to variables
    string ochar = argv[4];
    char oldchar = ochar[0];
    string nchar = argv[5];
    char newchar = nchar[0];
    newlines = replace_operator(inputlines, oldchar, newchar);
  }
  if(operation_type == "dilation"){
    //Assign extra arguments to variables
    string tchar = argv[4];
    char foregroundchar = tchar[0];
    newlines = dilation_operator(inputlines, foregroundchar);
  }
  if(operation_type == "erosion"){
    //Assign extra arguments to variables
    string tchar = argv[4];
    char foregroundchar = tchar[0];
    string bchar = argv[5];
    char backgroundchar = bchar[0];
    newlines = erosion_operator(inputlines, foregroundchar, backgroundchar);
  }
  if(operation_type == "floodfill"){
    //Assign extra arguments to variables
    string nchar = argv[6];
    char newchar = nchar[0];
    //assign locations where to floodfill
    string yl = argv[4];
    int yloc = atoi(yl.c_str());
    string xl = argv[5];
    int xloc = atoi(xl.c_str());
    newlines = floodfill_operator(inputlines,yloc,xloc,newchar);
  }

  //Write to output file one line at a time.
  for(unsigned int i = 0;i<newlines.size();i++) {
    //Write a line to the output file then go to new line.
    newfile << newlines[i] << endl;
  }

  return 0;
}
