// Document.cpp     Santiago Isaac  VT     ECE 3574  Jan 28 2026
//  implementation file for the Document class

#include "Document.hpp"
#include "Syllabizer.hpp"
#include <iostream> 
#include <unordered_map>

Document::Document(int value) { 
	this->localvalue = value;
}

Document::Document(string text){ 
	contents = cleanText(text);
	char* bufferc = new char[contents.size()+1]; /*! Copies string into char array*/
	strcpy(bufferc, contents.c_str());
	const char* delim = " \t\n\r\"\'.?!-;:#$&()*1234567890,"; 
	tokens.clear();
	char* token = strtok(bufferc, delim); /*! Finds first instance of delimiters and returns first word between*/
	while(token){
		tokens.push_back(Token(token));	/*! Saves word as token*/
		token = strtok(nullptr, delim); /*! Iterates while delimiters remain*/
	}
	delete[] bufferc;
}

Document::Document(const Document& doc2){ 
	this->contents = doc2.contents;
	this->filename = doc2.filename;
	this->localvalue = doc2.localvalue;
	this->tokens = doc2.tokens;
}

string Document::cleanText(string dirty){ 
	string dummy = dirty;
	for(auto i = dummy.begin(); i!=dummy.end();){
		if(static_cast<int>(*i)>127){ /*! Erases extended ascii*/
			i = dummy.erase(i);
		} else { 
			*i = tolower(*i); /*! Lowercases characters*/
			i++;
		}
	}
	return dummy;
}

bool comp(const std::pair<string, int>&a, const pair<string, int>&b){ /*! Compares pairs of <string,int> for sorting tuples*/
    if(a.second!=b.second){
		return a.second > b.second;
	}
	return a.first < b.first;
}

int Document::computecounts(int len){ 
	map<string,int> tuples;
	string tuple = "";
	if(len<=0 || len>numtokens() || len > 4){ /*! Invalid tuple counts*/
		return 0;
	}
	for(int i = 0; i<numtokens()-len+1; i++){
		for(int j = 0; j<len; j++){
			tuple = tuple+tokens[i+j].get(); /*! Creates tuples of length len*/
			if(j<len-1){
				tuple = tuple + " ";
			}
		}
		tuples[tuple]++; /*! Increments map using tuple as key*/
		tuple = ""; /*! Reset current typle*/
	}
	tupleC[len] = tuples; /*! Saves computed tuple count*/
	return (int)tuples.size(); /*! Returns number of tuples*/
}

int Document::gettuplecount(int len, int num, string& tuple, int& count){ 
	if(len<=0||len>4){ /*! Invalid tuple count*/
		return -2;
	}
	if( tupleC.find(len)==tupleC.end() || tupleC[len].empty()){ /*! Not computed tuple count*/
		return -1;
	}
	if(num<0 || num>=tupleC[len].size()){ /*! Invalid num*/
		return -2;
	}
	vector<std::pair<string,int>> tuplesV(tupleC[len].begin(), tupleC[len].end());
    sort(tuplesV.begin(), tuplesV.end(), comp); /*! Sorts tuples*/
	tuple = tuplesV[num].first; /*! Returns and saves values*/
	count = tuplesV[num].second;
	return num;
}

Document& Document::operator=(const Document& doc2){ 
	if(this!=&doc2){
		this->contents = doc2.contents;
		this->filename = doc2.filename;
		this->localvalue = doc2.localvalue;
		this->tokens = doc2.tokens;
	}
	return *this;
}

bool Document::operator==(const Document& doc2) const{ 
	if(filename!=doc2.filename){
		return false;
	}
	if(contents!=doc2.contents){
		return false;
	}
	if(tokens.size()!=doc2.tokens.size()){
		return false;
	}
	for(size_t i = 0; i<tokens.size(); i++){
		if(tokens[i]!=doc2.tokens[i]){
			return false;
		}
	}
	return true;
}

int Document::load(string fileName){ 
	std::ifstream file(fileName);
	if(!file){ /*! Checks valid file*/
		return -1;
	}
	filename = fileName;
	std::ostringstream buffer;
	buffer << file.rdbuf();
	contents = cleanText(buffer.str());
	char* bufferc = new char[contents.size()+1];
	strcpy(bufferc, contents.c_str()); /*! Save file contents as char array*/
	const char* delim = " \t\n\r\"\'.?!-;:#$&()*1234567890,";
	tokens.clear();
	char* token = strtok(bufferc, delim); /*! Finds first delimiter and returns first word*/
	while(token){
		Token token1 = Token(token);
		token1.setlexinfo(&lex);
		tokens.push_back(token1);	/*! Store word as token*/
		token = strtok(nullptr, delim); /*! Iterate while delimiters remain*/
	}
	delete[] bufferc;
	return static_cast<int>(buffer.str().size());
}

int Document::numtokens() const{ 
	if(contents.empty()){
		return 0;
	}
	return static_cast<int>(tokens.size());
}

int Document::numsyllables(){ 
	if(contents.empty()){
		return 0;
	}
	int count = 0;
	for(int i = 0; i<tokens.size(); i++){/*! Add up syllables in each token*/
		string word = tokens[i].get();
		vector<int> dummy = Syllabizer::syllabize(word);
		count+=static_cast<int>(dummy.size());
	}
	return count;
}
int Document::numsentences(){ 
	if(contents.empty()){
		return 0;
	}
	int count = 0;
	for(int i = 0; i<contents.length(); i++){
		char test = contents[i];
		if(test=='!'||test=='?'){ /*! Check for ! and ?*/
			count++;
		} else if (test=='.'){ /*! Check for . not part of ...*/
			if(i+1<contents.length()&&contents[i+1]!='.'){
				count++;
			} else if (i+1==contents.length()) {
				count++;
			} else {
				while(i+1<contents.length()&&contents[i+1]=='.'){
					i++;
				}
			}
		}
	}
	return count;
}
int Document::numhardwords(){ 
	if(contents.empty()){
		return 0;
	}
	int count = 0;
	for(int i = 0; i<tokens.size(); i++){ /*! Check each token for more than 2 syllables*/
		string word = tokens[i].get();
		vector<int> dummy = Syllabizer::syllabize(word);
		if(dummy.size()>2){
			count++;
		}
	}
	return count;
}

int Document::numchar(){ 
	return static_cast<int>(contents.length());
}

int Document::numunique(){
	std::unordered_map<std::string, int> freq;
	for(const auto& tok : tokens){
		freq[tok.get()]++;
	}
	return static_cast<int>(freq.size());
}

double Document::getreadingease(){ 
	if(contents.empty()){
		return -1;
	}
	double res = 206.835-1.015*(static_cast<double>(numtokens())/static_cast<double>(numsentences()))-84.6*(static_cast<double>(numsyllables())/static_cast<double>(numtokens()));
	return res;
}
double Document::getfkgradelevel(){ 
	if(contents.empty()){
		return -1;
	}
	double res = .39*(static_cast<double>(numtokens())/static_cast<double>(numsentences()))+11.8*(static_cast<double>(numsyllables())/static_cast<double>(numtokens()))-15.59;
	return res;
}
double Document::getgfgradelevel(){
	if(contents.empty()){
		return -1;
	}
	double res = .4*((static_cast<double>(numtokens())/static_cast<double>(numsentences()))+25*(static_cast<double>(numhardwords())/static_cast<double>(numtokens())));
	return res;
}

string& Document::gethtmlcontents() const{
	string res = "";
	for(auto& tok: tokens){
		res += tok.getHTML() + " ";
	}
	if (!res.empty()){
		res.pop_back();
	}
	return res;
}

Token::Token(){ 
	content = "";
}

Token::Token(string word){ 
	content = word;
}

Token::Token(const Token& tok){ 
	content = tok.content;
	info = tok.info;
}

Token& Token::operator=(const Token& tok){ 
	if(this!=&tok){
		content = tok.content;
		info = tok.info;
	}
	return *this;
}

bool Token::operator==(const Token& tok) const{ 
	return (content==tok.content);
}

bool Token::operator!=(const Token& tok) const{ 
	return !(*this==tok);
}

string Token::get() const{ 
	return content;
}

void Token::setlexinfo(){
	Lexicon& lexicon = Lexicon::getInstance();
	info.isStop = lexicon.isStopWord(this->content);
	info.pos = lexicon.gettype(this->content);
}

string Token::getHTML(){
	string res = this->content;
	if(info.isStop){
		res = "<i>"+res+"</i>";
		return res;
	}
	string front = "";
	string back = "</span>";
	switch(info.pos){
		case PARTS_OF_SPEECH::NOUN:
			front = "<span style=\"color:#FF0000;\">";
			break;
		case PARTS_OF_SPEECH::VERB:
			front = "<span style=\"color:#00FF00;\">";
			break;
		case PARTS_OF_SPEECH::ADJECTIVE:
			front = "<span style=\"color:#0000FF;\">";
			break;
		case PARTS_OF_SPEECH::ADVERB:
			front = "<span style=\"color:#0000FF;\">";
			break;
		case PARTS_OF_SPEECH::CONJUNCTION:
			front = "<span style=\"color:#FF00FF;\">";
			break;
		case PARTS_OF_SPEECH::UNKNOWN:
			return res + "[?]";
		default:
			front = "<span style=\"color:#000000;\">";
	}
	res = front + res + back;
	return res;
}

string Token::getHTML() const{
	string res = this->content;
	if(info.isStop){
		res = "<i>"+res+"</i>";
		return res;
	}
	string front = "";
	string back = "</span>";
	switch(info.pos){
		case PARTS_OF_SPEECH::NOUN:
			front = "<span style=\"color:#FF0000;\">";
			break;
		case PARTS_OF_SPEECH::VERB:
			front = "<span style=\"color:#00FF00;\">";
			break;
		case PARTS_OF_SPEECH::ADJECTIVE:
			front = "<span style=\"color:#0000FF;\">";
			break;
		case PARTS_OF_SPEECH::ADVERB:
			front = "<span style=\"color:#0000FF;\">";
			break;
		case PARTS_OF_SPEECH::CONJUNCTION:
			front = "<span style=\"color:#FF00FF;\">";
			break;
		case PARTS_OF_SPEECH::UNKNOWN:
			return res + "[?]";
		default:
			front = "<span style=\"color:#000000;\">";
	}
	res = front + res + back;
	return res;
}