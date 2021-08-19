#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

ifstream inFile("grid.txt");
ifstream dict("words.txt");
ofstream out("puzzle.txt");
const int M = 8;
const int N = 8;
char c;
char grid[M][N] = {};
int row = 0;
int column = 0;
unordered_set<string> words;
unordered_set<string> revwords; //words in reverse


string reverse(string word){
  string rev;
  for(int i = word.length()-1; i >= 0; i--){
    //concatenate characters to the reverse
    rev = rev + word[i];
  }
  return rev;
}

void setUp(){
  string word;
  //put words from dictionary into unordered_set
  while (getline(dict, word)){
    if(word.length() >= 6){ //only search for words of length 6 or more
      words.insert(word);
      revwords.insert(reverse(word));
    }
  }
  //create grid in 2d array
  while (inFile.get(c)){
      if (c != ' ' && c != '\n'){
          grid[row][column] = c;
          if (column == M){
              column = 0;
              row++;
              //cout << c << endl;
          }
          else{
              column++;
              //cout << c << " ";
          }
      }
  }
  //print out grid
  for (int i = 0; i < M; i++){
      for (int j = 0; j < N; j++)
      {
          cout << grid[i][j] << " ";
      }
      cout << endl;
  }
}

//searches for word in grid
void findWord(int x, int y, const string &word){
    // horizontal
    if (x + word.size() <= M) {
        int i = 0;
        while (i < word.size() && grid[x + i][y] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << word << " from (" << x << ", " << y << ") to ("
          << x+i-1 << ", " << y << ")" << endl;
        }
    }
    // vertical
    if (y + word.size() <= N) {
        int i = 0;
        while (i < word.size() && grid[x][y+i] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << word << " from (" << x << ", " << y << ") to ("
          << x << ", " << y+i-1 << ")" << endl;
        }
    }
    // diagonal top left to bottom right
    if ((x + word.size() <= M) && (y + word.size() <= N)) {
        int i = 0;
        while (i < word.size() && grid[x+i][y+i] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << word << " from (" << x+i-1 << ", " << y+i-1 << ") to ("
          << x << ", " << y << ")" << endl;
        }
    }
    // diagonal bottom left to top right
    if ((x + word.size() <= M) && (y + word.size() <= N)) {
        int i = 0;
        while (i < word.size() && grid[x+i][y-i] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << word << " from (" << x+i-1 << ", " << y-i-1 << ") to ("
          << x << ", " << y << ")" << endl;
        }
    }
}

//searches for reverse word in grid
void findReverse(int x, int y, const string &word) {
    // horizontal
    if (x + word.size() <= M) {
        int i = 0;
        while (i < word.size() && grid[x + i][y] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << reverse(word) << " from (" << x+i-1 << ", " << y << ") to ("
          << x << ", " << y << ")" << endl;
        }
    }
    // vertical
    if (y + word.size() <= N) {
        int i = 0;
        while (i < word.size() && grid[x][y+i] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << reverse(word) << " from (" << x << ", " << y+i-1 << ") to ("
          << x << ", " << y << ")" << endl;
        }
    }
    // diagonal top left to bottom right
    if ((x + word.size() <= M) && (y + word.size() <= N)) {
        int i = 0;
        while (i < word.size() && grid[x+i][y+i] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << reverse(word) << " from (" << x << ", " << y << ") to ("
          << x+i-1 << ", " << y+i-1 << ")" << endl;
        }
    }
    // diagonal bottom left to top right
    if ((x + word.size() <= M) && (y + word.size() <= N)) {
        int i = 0;
        while (i < word.size() && grid[x+i][y-i] == word[i]) i++;
        if (i == word.size()){
          //put word and location in puzzle.txt
          out << reverse(word) << " from (" << x << ", " << y << ") to ("
          << x+i-1 << ", " << y-i-1 << ")" << endl;
        }
    }
}

int main(){

    setUp();

    //for each character in grid
    for (int x = 0; x < M; x++){
        for (int y = 0; y < N; y++){
            //check for each word (length >= 6) in dictionary
            for (string w : words){
              findWord(x, y, w);
              findReverse(x, y, reverse(w));
            }
        }
    }

    return 0;
}
