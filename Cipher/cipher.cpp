#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// ------ preprocessing ----------
string text_to_uppercase(string s);
string conserve_alphabet(string s);
// -------------------------------

string getStringFreq(map<char, int> frequencies);
map<char, char> create_dtable(string fregActual, string freqLang);

bool pred(pair<char, int> i, pair<char, int> j) {return i.second > j.second;}

// ---------------------------------------------------
string decryptMessage(string message, string freqLang);
// --------------------------------------------------

int main()
{
    //original message
    string encrypted_message = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\nXof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF\nHGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\nZgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\nXof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz\ndn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon\nRdepdrw.\n(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";
    string freqLang = "TEOAISRHNUCMDLGWFPYKJBVQX";

    string decrypted_message = decryptMessage(encrypted_message, freqLang);
    cout<<decrypted_message<<endl;

    return 0;
}

string decryptMessage(string message, string freqLang)
{

    // Preprocessing part
    // convert every char in encrypted message to uppercase letter
    string processed_message = text_to_uppercase(message);
    // Save only the characters that belong to (a-z)
    processed_message = conserve_alphabet(processed_message);

    // Create a map that will store the frequencies of
    // every letter in the (already) processed encrypted message
    map<char, int> frequencies;
    for(auto letter : processed_message)
    {
        frequencies[letter]++;
    }

    // Get the frequencies in freqLang-fashion way 
    // and sorted in descending order. 
    string strFreq = getStringFreq(frequencies);

    // Create a dtable dictionary for storing the actual frequencies with
    // its corresponded value in freqLang
    map<char, char> dtable = create_dtable(strFreq, freqLang);
    
    // Traversing every character in message to replace them 
    // according to freqLang
    for(int i=0; i<message.size(); ++i)
    {
        char curr_char = message[i];
        // Check if the key exists in the map
        // wheter is uppercase or lowecase.
        // Since dtable only stores uppercase chars, I use toupper() to
        // convert from lowercase to uppercase
        if(dtable[curr_char] || dtable[toupper(curr_char)])
        {
            // If current character is uppercase, replace it by its 
            // corresponded value in dtable
            if(isupper(curr_char))
            {
                message[i] = dtable[curr_char];   
            }
            else
            {
                // If not, first convert the char
                // in uppercase and search it in the dtable
                // then convert the resultant char in dtable to lowercase 
                message[i] = tolower(dtable[toupper(curr_char)]); 
            }
        }   
    }

    return message;

}

string text_to_uppercase(string s)
{
    for(int i=0; i<s.size(); ++i)
    {
        s[i] = toupper(s[i]);
    }

    return s;
}

string conserve_alphabet(string s)
{
    int j = 0;
    for(int i=0; i<s.size(); ++i)
    {
        if(s[i] <= 'Z' && s[i] >= 'A')
        {
            s[j] = s[i];
            j++;
        }
    }

    s = s.substr(0, j);
    return s;
}

string getStringFreq(map<char, int> frequencies)
{
    // Vector of pairs to store every element located in frequencies
    // I create this vector because stl map does not allow 
    // sorting by value 
    vector<pair<char, int>> vec_frequencies;

    for(auto p : frequencies)
    {
        vec_frequencies.push_back(p);
    }

    // Sort by value the vector of pairs, the sorting is
    // in descending order. Pred is the function which makes that possible.
    sort(vec_frequencies.begin(), vec_frequencies.end(), pred);

    string freqEncrypted; 

    // Traversing the string array in order to add the sorted char keys 
    for(auto it = vec_frequencies.begin(); it != vec_frequencies.end(); ++it)
    {
        freqEncrypted.push_back(it->first);
    }

    return freqEncrypted;
}

map<char, char> create_dtable(string freqActual, string freqLang)
{
    // I'm assuming that freqLan and fregActual are both the same size.

    // dtable is a data structure based on a hash map that I made for storing the 
    // frequencies of the encrypted message and the freqLang in the same place,
    // in that way, the key of the dtable is the actual frequency and
    // the value is its corresponded value in freqLang  
    map<char, char> dtable;

    for(int i=0; i<freqLang.size(); ++i)
    {
        dtable[freqActual[i]] = freqLang[i];
    }

    return dtable;
}
