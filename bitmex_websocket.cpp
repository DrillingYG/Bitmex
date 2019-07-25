#include "api_key.h"
#include "bitmex_websocket.h"

void urlParser(string & url, vector<string> & parsedUrl) {
	CURLU * h;
	CURLUcode uc;
	char * scheme = nullptr;
	char * netloc = nullptr;
	char * path = nullptr;
	char * params = nullptr;
	char * query = nullptr;
	char * fragment = nullptr;
	h = curl_url();
	uc = curl_url_set(h, CURLUPART_URL, url.c_str(), 0);

	uc = curl_url_get(h, CURLUPART_SCHEME, &scheme, 0);
	uc = curl_url_get(h, CURLUPART_HOST, &netloc, 0);
	uc = curl_url_get(h, CURLUPART_PATH, &path, 0);
	uc = curl_url_get(h, CURLUPART_OPTIONS, &params, 0);
	uc = curl_url_get(h, CURLUPART_QUERY, &query, 0);
	uc = curl_url_get(h, CURLUPART_FRAGMENT, &fragment, 0);

	parsedUrl.push_back((scheme == nullptr ? "" : string(scheme)));
	parsedUrl.push_back((netloc == nullptr ? "" : string(netloc)));
	parsedUrl.push_back((path == nullptr ? "" : string(path)));
	parsedUrl.push_back((params == nullptr ? "" : string(params)));
	parsedUrl.push_back((query == nullptr ? "" : string(query)));
	parsedUrl.push_back((fragment == nullptr ? "" : string(fragment)));


	curl_url_cleanup(h);

	curl_free(scheme);
	curl_free(netloc);
	curl_free(path);
	curl_free(params);
	curl_free(query);
	curl_free(fragment);
}

BitMEXWebsocket::BitMEXWebsocket(const char * pEndpoint, const char * pSymbol, const char * pApi_key, const char * pApi_secret) {
	string endpoint(pEndpoint);
	string symbol(pSymbol);
	string api_key(pApi_key);
	string api_secret(pApi_key);

	this->endpoint = endpoint;
	this->symbol = symbol;

	try {
		raiseError(api_key, api_secret);
	}
	catch (string & errorString) {
		cout << "Exception : " << errorString << endl;
	}

	this->api_key = api_key;
	this->api_secret = api_secret;

	//this->data = map<vector<string>, int>();
	//this->keys = map<vector<string>, int>();
	this->exited = false;
	string wsURL;
	__get_url(wsURL);
	cout << "wsURL : " << wsURL;
};


void BitMEXWebsocket::raiseError(const string & api_key, const string & api_secret) {
	if (api_key != "" && api_secret == "") {
		throw out_of_range("api_secret is required if api_key is provided");
	}
	if (api_key == "" && api_secret != "") {
		throw out_of_range("api_key is required if api_secret is provided");
	}
}

void BitMEXWebsocket::__get_url(string & wsURL) {
	vector<string> symbolSubs{ "execution", "instrument", "order", "orderBookL2", "position", "quote", "trade" };
	vector<string> subscriptions;
	wsURL = "";
	for (auto subs : symbolSubs) {
		string subscript = subs + ":" + this->symbol;
		subscriptions.push_back(subscript);
	}
	subscriptions.push_back("margin");

	vector<string> parsedUrl;
	urlParser(this->endpoint, parsedUrl);

	for (int a = 0; a < parsedUrl.size(); a = a + 1) cout << parsedUrl[a] << endl;

	int pos = parsedUrl[0].find("http");

	if (pos != string::npos) {
		parsedUrl[0].replace(pos, 4, "ws");
	}


	parsedUrl[2] = "/realtime?subscribe=";
	for (auto subs : subscriptions) {
		parsedUrl[2] += subs;
		if (subs != "margin") parsedUrl[2] += ",";
	}

	wsURL = parsedUrl[0] + "://";
	wsURL += parsedUrl[1];
	wsURL += parsedUrl[2];
	if (parsedUrl[4] != "") {
		wsURL += "?";
		wsURL += parsedUrl[4];
	}
	if (parsedUrl[5] != "") {
		wsURL += "#";
		wsURL += parsedUrl[5];
	}

}

void BitMEXWebsocket::__connect(string& wsURL) {
	//https://docs.websocketpp.org/md_tutorials_utility_client_utility_client.html

	int conn_timeout = 5;

}