// Document.hpp     Santiago Isaac  VT     ECE 3574  Jan 28 2026
//  header file for the Document class

#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Lexicon.hpp"
#include "DocumentWorker.h"

using std::string;
using std::vector;
using std::map;
using std::pair;

class Token{
    private:
        string content = "";
    
    public:
        WordInfo info{};
        Token(); /*! Default constructor for token class*/
        Token(string word); /*! Token cconstructor with string input*/
        Token(const Token& tok); /*! Token constructor with reference to other token*/
        Token& operator=(const Token& tok); /*! Token copy constructor*/
        bool operator==(const Token& tok) const; /*! Token equality operator*/
        bool operator!=(const Token& tok) const; /*! Token inequality operator */
        string get() const; /*! Returns token contents*/
        void setlexinfo(); /*! Sets wordinfo based on lexicon*/
        string getHTML(); /*! Returns decorated HTML of word*/
        string getHTML() const;
};

class Document {
    private:
        int localvalue;
        string filename = "";
        string contents = "";
        map<int, map<string, int>> tupleC;
        vector<Token> tokens{};

    public:
        Document(int value=0); /*! Default constructor for Document*/
        Document(string text);  /*! Document constructor with text*/
        Document(const Document& doc2); /*! Document constructor with reference to other document*/

        string cleanText(string dirty); /*! Function to remove extended ascii and lowercase text*/
        int computecounts(int len); /*! Computes tuples of length len*/
        int gettuplecount(int len, int num, string& tuple, int& count); /*! Returns num most common tuple of length len*/

        Document& operator=(const Document& doc2); /*! Document copy constructor*/
        bool operator==(const Document& doc2) const; /*! Document equality operator*/
        int load(string fileName); /*! Loads a file into a document given a string for a filename*/
        int numtokens() const; /*! Returns number of tokens*/
        int numsyllables(); /*! Returns number of syllables in a document*/
        int numsentences(); /*! Function to find number of sentences in a document*/
        int numhardwords(); /*! Function to return number of hard words*/
        int numchar(); /*! Returns number of characters in a document*/
        int numunique(); /*! Returns number of unique words*/
        double getreadingease();/*! Return reading ease using formula*/
        double getfkgradelevel();/*! Return fk-grade Level using formula*/
        double getgfgradelevel();  /*! Return gf-grade Level using formula*/

        string& gethtmlcontents() const; /*! Return htmlized contents*/
        string& getsyllabizedcontents() const;

        void extracttokens(int numthreads);

        friend class DocumentWorker;
};

#endif // DOCUMENT_HPP