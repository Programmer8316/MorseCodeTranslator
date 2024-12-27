#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//method loads array with morse code for each letter(A-Z)
bool loadMorseArray(string morseCodes[], ifstream &morseFile)
{
    char letter;
    string code;
    int index = 0;
    
    while(morseFile >> letter >> ws && morseFile >> code)
    {
        if(letter >= 'A' && letter <= 'Z') 
        {
            morseCodes[letter - 'A'] = code;
            index++;
        }    
    }
    
    return index == 26;
}

//method translates english text to morse code and write them to a file
void genMorse(string &morse, string input, string morseCodes[])
{
    for(char letter : input) 
    {
        if(letter == ' ') 
            morse += " ";
        else if(letter == '.') 
            morse += ".";
        else if(letter >= 'A' && letter <= 'Z')
        {
            int index = letter - 'A'; 
            morse += morseCodes[index] + " "; 
        }
    }
}

int main()
{
    string morseCodes[26];
    
    ifstream readFile("text.txt");
    ifstream morseFile("morseLetters.txt");
    ofstream writeFile("morse.txt");
    
    if(readFile)
    {
        if(writeFile)
        {
            if(loadMorseArray(morseCodes, morseFile))
            {
                string input, morse;
                int countLines = 0;
                
                while(getline(readFile, input))
                {
                    morse = "";
                    genMorse(morse, input, morseCodes);
                    countLines++;
                    
                    writeFile << morse << endl;
                }
                
                readFile.close();
                writeFile.close();
                
                cout << "Translation complete. " << countLines << " lines translated." << endl;
            }
        }
        
        else
            cout << "Error, unable to open file \"morse.txt\".";
    }
    
    else
        cout << "Error, unable to open file \"text.txt\".";
    
    return 0;
}