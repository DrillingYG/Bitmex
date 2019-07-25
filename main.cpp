//https://github.com/BitMEX/api-connectors/blob/master/official-ws/python/bitmex_websocket.py
#include <cstdio>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include "api_key.h"
#include "KISA_SHA256.h"
#include "spdlog\spdlog.h"
#include "bitmex_websocket.h"
#include "spdlog\sinks\basic_file_sink.h"
#include "spdlog\sinks\rotating_file_sink.h"

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")

typedef websocketpp::client<websocketpp::config::asio_client> client;

int main(void) {
	
	return 0;
}