#include <iostream>
#include <map>
#define CATCH_CONFIG_MAIN  // This line tells Catch to provide a main() function
                           // - do this in one cpp file only
#include "catch.hpp"       // This line provides access to all Catch macros
                           // - do not modify catch.hpp
#include "Document.hpp"
#include <cassert>    
#include <cstdlib>
#include <iostream>
#include "Syllabizer.hpp"
using namespace std;

// TEST_CASE("Constructor test Doc"){
//     Document D1("fkdfsjsal fsdkfjsdl fjkadlfj alfjkalf");
//     REQUIRE(D1.numtokens() == 4);
//     Document D2(D1);
//     REQUIRE(D2.numtokens() == 4);
// }

// TEST_CASE("Copying and equality Doc"){
//     Document D1("fkdfsjsal fsdkfjsdl fjkadlfj alfjkalf");
//     Document D2("fjlsdfjlsjf");
//     REQUIRE(!(D1==D2));
//     D2 = D1;
//     REQUIRE(D1==D2);
// }

// TEST_CASE("Constructor test Token"){
//     Token T1("test");
//     REQUIRE(T1.get()=="test");
//     Token T2(T1);
//     REQUIRE(T2.get()=="test");
// }

// TEST_CASE("Copying and equality Token"){
//     Token T1("fkdfsjsal");
//     Token T2("fjlsdfjlsjf");
//     REQUIRE(!(T1==T2));
//     T2 = T1;
//     REQUIRE(T1==T2);
// }

// TEST_CASE("Loading from a file"){
//     Document D1;
//     REQUIRE(D1.numtokens()==0);//known file
//     REQUIRE(D1.load("quick-brown-fox.txt")==44);
//     REQUIRE(D1.numtokens()==9);//unknown file
//     REQUIRE(D1.load("jfldsfjakf.txt")==-1);
//     REQUIRE(D1.numtokens()==9);
// }

// TEST_CASE("Token generation and count computations"){
//     Document D1;
//     string dummyT;
//     int dummyC;
//     REQUIRE(D1.load("quick-brown-fox.txt")==44);
//     REQUIRE(D1.numtokens()==9);
//     //Unique tokens
//     REQUIRE(D1.computecounts(1)==8);
//     //2 tuples not calculated yet
//     REQUIRE(D1.gettuplecount(3, 2, dummyT, dummyC)==-1);
//     REQUIRE(D1.computecounts(2)==8);
//     //2 tuples calculated
//     REQUIRE(D1.gettuplecount(2, 7, dummyT, dummyC)==7);
//     REQUIRE(dummyT == "the quick");
//     REQUIRE(dummyC==1);
//     //-4 tuples invalid
//     REQUIRE(D1.gettuplecount(-4, 2, dummyT, dummyC)==-2);
//     //7 tuples too big
//     REQUIRE(D1.gettuplecount(7, 2, dummyT, dummyC)==-2);
// }

string teststring1("Would you needlessly ignore me... without proof of a disreputable action? For what reason am I thus disregarded? It will not stand! I will plead my case before a jury of my peers, and will see justice done.");
TEST_CASE("Reading Level Test 1", "") {

Document D(teststring1);
CHECK(D.numtokens() == 38);
CHECK(D.numsyllables() == 54);
CHECK(D.numsentences() == 4);
CHECK(D.numhardwords() == 4);
double ease = D.getreadingease();
double fklevel = D.getfkgradelevel();
double gflevel = D.getgfgradelevel();
CHECK(((76 < ease) && (ease < 78)));
CHECK(((4 < fklevel) && (fklevel < 5)));
CHECK(((4 < gflevel) && (gflevel < 5)));
}
TEST_CASE("Reading Level Test 2", "") {
Document D;
D.load("gettysburg.txt");
CHECK(D.numtokens() == 272);
CHECK(D.numsyllables() == 370);
CHECK(D.numsentences() == 10);
CHECK(D.numhardwords() == 24);
double ease = D.getreadingease();
double fklevel = D.getfkgradelevel();
double gflevel = D.getgfgradelevel();
CHECK(((63 < ease) && (ease < 65)));
CHECK(((11 < fklevel) && (fklevel < 12)));
CHECK(((11 < gflevel) && (gflevel < 12)));
}
TEST_CASE("Reading Level Test 3", "") {
Document D;
D.load("C:/Data/Text/thereisnofile.txt");
CHECK(D.numsentences() == 0);
double ease = D.getreadingease();
CHECK(ease == -1);
}