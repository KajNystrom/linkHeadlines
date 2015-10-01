#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <simstring/simstring.h>



// Utility functions. I forgot how much I dislike C++.
int stringToWString(std::wstring &ws, const std::string &s){
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
    return 0;
}

//Find matches to unicode input strings given algorithm and threshold. 
void retrieve(simstring::reader& dbr, const std::wstring& query, int measure, double threshold){
    // Retrieve similar strings into a string vector.
    std::vector<std::wstring> xstrs;
    dbr.retrieve(query, measure, threshold, std::back_inserter(xstrs));


    // Output the retrieved strings separated by ", ".
    if ((int)xstrs.size() >0){
    	std :: wcout << query << L" <<>> ";
    	for (int i = 0;i < (int)xstrs.size();++i) {
    		std::wcout << (i != 0 ? L", " : L"") << xstrs[i];
    	}
    	std::wcout << std::endl;
    }
}

int main(int argc, char *argv[])
{
	double coefficient;
	if( argc > 1 ) {
		coefficient = atof(argv[1]);  // alternative strtod
	   }
	//Open output file
	//std::ofstream outfile;
	//outfile.open("/home/osboxes/workspace/linkHeadlines/src/testdata/bubblaHeadlines");

    // Activate std::wcout.
    std::locale::global(std::locale("")); 
    std::wcout.imbue(std::locale(""));

    // Open a SimString database for writing (with std::wstring).
    //This part is for generating the db of bubbla headlines. Not generally needed.
    simstring::ngram_generator gen(3, false);
    std::string line;
    std::wstring wline;
    simstring::writer_base<std::wstring> dbw(gen, "bubblaUnicode.db");
	std::ifstream bubblaHeadlinesFile("/home/osboxes/workspace/linkHeadlines/src/testdata/bubblaHeadlinesConverted");
    while (std::getline(bubblaHeadlinesFile, line)){
    	stringToWString(wline, line);
    	//std::wcout << L"inserting bubbla headline: " << wline << std::endl;
    	dbw.insert(wline);
    }

    dbw.close();
    //End of bubbla db gen part


    // Open the database for reading.
    simstring::reader dbr;
    dbr.open("bubblaUnicode.db");

    // Output  strings from Unicode queries.
    std::ifstream soundcloudHeadlinesFile("/home/osboxes/workspace/linkHeadlines/src/testdata/soundcloudHeadlines");
    int i=0;
    while (std::getline(soundcloudHeadlinesFile, line))
    {
    	i++;
    	stringToWString(wline, line);
    	//This is where the magic is called. You can experiment with any of the commented out lines below.

    	//retrieve(dbr, wline, simstring::cosine, coefficient);
    	//Recommended cosine coefficient around 0.4

    	retrieve(dbr, wline, simstring::overlap, coefficient);
    	//Recommended overlap coefficient: around

    	//retrieve(dbr, wline, simstring::dice, coefficient);
    	//Recommended dice coefficient: around

    	//Recommended exact coefficient: None. Will not work.
    }
    //std::cout << "Processed " << i << " calls with coefficient " << coefficient << std::endl;


    //outfile.close();
    return 0;
}
