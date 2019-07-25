#pragma once
#include "api_key.h"
#include <vector>
#include <map>

class BitMEXWebsocket {
#define MAX_TABLE_LEN 200

private:
	string symbol;
	string api_key;
	string api_secret;
	string endpoint;
	bool exited;

	void raiseError(const string & api_key, const string & api_secret);
		
public:
	BitMEXWebsocket(const char * pEndpoint, const char * pSymbol, const char * pApi_key, const char * pApi_secret);

	void __get_url(string & wsURL);
	void __connect(string & wsURL);

};

void urlParser(string & url, vector<string>& parsedUrl);

//testcomment