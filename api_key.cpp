#include <ctime>
#include <cstdint>
#include <cstring>
#include "commonHeader.h"
#include "KISA_SHA256.h"

uint64_t generate_nonce(void) {
	return time(NULL) + 3600;
}

string generate_signature(string secret, string verb, string url, uint64_t nonce, string data) {
	string signature;
	CURLU * h;
	CURLUcode uc;
	char * path;
	char * query;

	h = curl_url();
	if (!h) return "";

	uc = curl_url_set(h, CURLUPART_URL, url.c_str(), 0);

	uc = curl_url_get(h, CURLUPART_PATH, &path, 0);
	uc = curl_url_get(h, CURLUPART_QUERY, &query, 0);
	if (!uc) {
		int len = strlen(path) + 1 + strlen(query);
		cout << "path_before : " << path << endl;
		strncat(path, "?", 1);
		strncat(path, query, strlen(query));
		*(path + len) = '\0';
		cout << "path_after : " << path << endl;
	}

	BYTE hash[32];
	string message = verb + string(path) + to_string(nonce) + data;
	
	SHA256_Encrpyt(reinterpret_cast<const BYTE*>(const_cast<char *>(message.c_str())), message.length(),hash);
	
	curl_url_cleanup(h);
	return signature;
}