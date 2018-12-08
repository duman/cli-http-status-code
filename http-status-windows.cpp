#include <iostream>
#include <string>
#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "Wininet")

int response_code(const std::string& url, const bool display_text = true);

int main(int argc, char* argv[])
{
	std::string response_text = argv[1];
	if (response_text.length() < 3)
	{
		std::cout << "Please make sure that you have entered a valid URL or a valid status code.\n";
		return 0;
	}
	if (response_text.length() == 3)
	{
		// 100s
		if (response_text == "100") { std::cout << "Continue"; }
		else if (response_text == "101") { std::cout << "Switching Protocols"; }
		else if (response_text == "102") { std::cout << "Processing"; }
		// 200s
		else if (response_text == "200") { std::cout << "OK"; }
		else if (response_text == "201") { std::cout << "Created"; }
		else if (response_text == "202") { std::cout << "Accepted"; }
		else if (response_text == "203") { std::cout << "Non-Authoritative Information"; }
		else if (response_text == "204") { std::cout << "No Content"; }
		else if (response_text == "205") { std::cout << "Reset Content"; }
		else if (response_text == "206") { std::cout << "Partial Content"; }
		else if (response_text == "207") { std::cout << "Multi-Status"; }
		else if (response_text == "208") { std::cout << "Already Reported"; }
		else if (response_text == "226") { std::cout << "IM Used"; }
		// 300s
		else if (response_text == "300") { std::cout << "Multiple Choices"; }
		else if (response_text == "301") { std::cout << "Moved Permanently"; }
		else if (response_text == "302") { std::cout << "Found"; }
		else if (response_text == "303") { std::cout << "See Other"; }
		else if (response_text == "304") { std::cout << "Not Modified"; }
		else if (response_text == "305") { std::cout << "Use Proxy"; }
		else if (response_text == "306") { std::cout << "Switch Proxy"; }
		else if (response_text == "307") { std::cout << "Temporary Redirect"; }
		else if (response_text == "308") { std::cout << "Permanent Redirect"; }
		// 400s
		else if (response_text == "400") { std::cout << "Bad Request"; }
		else if (response_text == "401") { std::cout << "Unauthorized"; }
		else if (response_text == "402") { std::cout << "Payment Required"; }
		else if (response_text == "403") { std::cout << "Forbidden"; }
		else if (response_text == "404") { std::cout << "Not Found"; }
		else if (response_text == "405") { std::cout << "Method Not Allowed"; }
		else if (response_text == "406") { std::cout << "Not Acceptable"; }
		else if (response_text == "407") { std::cout << "Proxy Authentication Required"; }
		else if (response_text == "408") { std::cout << "Request Timeout"; }
		else if (response_text == "409") { std::cout << "Conflict"; }
		else if (response_text == "410") { std::cout << "Gone"; }
		else if (response_text == "411") { std::cout << "Length Required"; }
		else if (response_text == "412") { std::cout << "Precondition Failed"; }
		else if (response_text == "413") { std::cout << "Request Entity Too Large"; }
		else if (response_text == "414") { std::cout << "Request-URI Too Long"; }
		else if (response_text == "415") { std::cout << "Unsupported Media Type"; }
		else if (response_text == "416") { std::cout << "Requested Range Not Satisfiable"; }
		else if (response_text == "417") { std::cout << "Expectation Failed"; }
		else if (response_text == "418") { std::cout << "I\'m a teapot"; } // :)
		else if (response_text == "419") { std::cout << "Authentication Timeout"; }
		else if (response_text == "420") { std::cout << "Method Failure"; }
		else if (response_text == "421") { std::cout << "Misdirected Request"; }
		else if (response_text == "422") { std::cout << "Unprocessable Entity"; }
		else if (response_text == "423") { std::cout << "Locked"; }
		else if (response_text == "424") { std::cout << "Failed Dependency"; }
		else if (response_text == "426") { std::cout << "Upgrade Required"; }
		else if (response_text == "428") { std::cout << "Precondition Required"; }
		else if (response_text == "429") { std::cout << "Too Many Requests"; }
		else if (response_text == "431") { std::cout << "Request Header Fields Too Large"; }
		else if (response_text == "440") { std::cout << "Login Timeout"; }
		else if (response_text == "444") { std::cout << "No Response"; }
		else if (response_text == "449") { std::cout << "Retry With"; }
		else if (response_text == "450") { std::cout << "Blocked by Windows Parental Controls"; }
		else if (response_text == "451") { std::cout << "Unavailable For Legal Reasons"; }
		else if (response_text == "494") { std::cout << "Request Header Too Large"; }
		else if (response_text == "495") { std::cout << "Cert Error"; }
		else if (response_text == "496") { std::cout << "No Cert"; }
		else if (response_text == "497") { std::cout << "HTTP to HTTPS"; }
		else if (response_text == "498") { std::cout << "Token Expired/Invalid"; }
		else if (response_text == "499") { std::cout << "Client Closed Request"; }
		// 500s
		else if (response_text == "500") { std::cout << "Internal Server Error"; }
		else if (response_text == "501") { std::cout << "Not Implemented"; }
		else if (response_text == "502") { std::cout << "Bad Gateway"; }
		else if (response_text == "503") { std::cout << "Service Unavailable"; }
		else if (response_text == "504") { std::cout << "Gateway Timeout"; }
		else if (response_text == "505") { std::cout << "HTTP Version Not Supported"; }
		else if (response_text == "506") { std::cout << "Variant Also Negotiates"; }
		else if (response_text == "507") { std::cout << "Insufficient Storage"; }
		else if (response_text == "508") { std::cout << "Loop Detected"; }
		else if (response_text == "509") { std::cout << "Bandwidth Limit Exceeded"; }
		else if (response_text == "510") { std::cout << "Not Extended"; }
		else if (response_text == "511") { std::cout << "Network Authentication Required"; }
		else if (response_text == "520") { std::cout << "Unknown Error"; }
		else if (response_text == "598") { std::cout << "Network Read Timeout Error"; }
		else if (response_text == "599") { std::cout << "Network Connect Timeout Error"; }
	}
	if (response_text.length() > 3)
	{
		if (response_text.substr(0, 5) == "http:" || response_text.substr(0, 6) == "https:")
		{
			response_code(response_text);
			return 0;
		}
		else
		{
			response_text.insert(0, "http://");
			response_code(response_text);
			return 0;
		}
	}
}

int response_code(const std::string& url, const bool display_text)
{
	const auto h_open = InternetOpenA("DumanSTUDIOS", INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
	const auto h_file = InternetOpenUrlA(h_open, url.c_str(), nullptr, 0, INTERNET_FLAG_RELOAD, 0);
	char response_text[256];
	DWORD response_text_size = sizeof(response_text);

	if (!HttpQueryInfoA(h_file, HTTP_QUERY_STATUS_CODE, &response_text, &response_text_size, nullptr))
	{
		if (display_text)
			std::cout << "Remote server is offline or unreachable.\n";
		InternetCloseHandle(h_open);
		InternetCloseHandle(h_file);
		return -1;
	}

	if (display_text)
	{
		std::cout << url << "\t" << "Response: " << response_text << " ";
		// 100s
		if (static_cast<std::string>(response_text) == "100") { std::cout << "Continue"; }
		else if (static_cast<std::string>(response_text) == "101") { std::cout << "Switching Protocols"; }
		else if (static_cast<std::string>(response_text) == "102") { std::cout << "Processing"; }
		// 200s
		else if (static_cast<std::string>(response_text) == "200") { std::cout << "OK"; }
		else if (static_cast<std::string>(response_text) == "201") { std::cout << "Created"; }
		else if (static_cast<std::string>(response_text) == "202") { std::cout << "Accepted"; }
		else if (static_cast<std::string>(response_text) == "203") { std::cout << "Non-Authoritative Information"; }
		else if (static_cast<std::string>(response_text) == "204") { std::cout << "No Content"; }
		else if (static_cast<std::string>(response_text) == "205") { std::cout << "Reset Content"; }
		else if (static_cast<std::string>(response_text) == "206") { std::cout << "Partial Content"; }
		else if (static_cast<std::string>(response_text) == "207") { std::cout << "Multi-Status"; }
		else if (static_cast<std::string>(response_text) == "208") { std::cout << "Already Reported"; }
		else if (static_cast<std::string>(response_text) == "226") { std::cout << "IM Used"; }
		// 300s
		else if (static_cast<std::string>(response_text) == "300") { std::cout << "Multiple Choices"; }
		else if (static_cast<std::string>(response_text) == "301") { std::cout << "Moved Permanently"; }
		else if (static_cast<std::string>(response_text) == "302") { std::cout << "Found"; }
		else if (static_cast<std::string>(response_text) == "303") { std::cout << "See Other"; }
		else if (static_cast<std::string>(response_text) == "304") { std::cout << "Not Modified"; }
		else if (static_cast<std::string>(response_text) == "305") { std::cout << "Use Proxy"; }
		else if (static_cast<std::string>(response_text) == "306") { std::cout << "Switch Proxy"; }
		else if (static_cast<std::string>(response_text) == "307") { std::cout << "Temporary Redirect"; }
		else if (static_cast<std::string>(response_text) == "308") { std::cout << "Permanent Redirect"; }
		// 400s
		else if (static_cast<std::string>(response_text) == "400") { std::cout << "Bad Request"; }
		else if (static_cast<std::string>(response_text) == "401") { std::cout << "Unauthorized"; }
		else if (static_cast<std::string>(response_text) == "402") { std::cout << "Payment Required"; }
		else if (static_cast<std::string>(response_text) == "403") { std::cout << "Forbidden"; }
		else if (static_cast<std::string>(response_text) == "404") { std::cout << "Not Found"; }
		else if (static_cast<std::string>(response_text) == "405") { std::cout << "Method Not Allowed"; }
		else if (static_cast<std::string>(response_text) == "406") { std::cout << "Not Acceptable"; }
		else if (static_cast<std::string>(response_text) == "407") { std::cout << "Proxy Authentication Required"; }
		else if (static_cast<std::string>(response_text) == "408") { std::cout << "Request Timeout"; }
		else if (static_cast<std::string>(response_text) == "409") { std::cout << "Conflict"; }
		else if (static_cast<std::string>(response_text) == "410") { std::cout << "Gone"; }
		else if (static_cast<std::string>(response_text) == "411") { std::cout << "Length Required"; }
		else if (static_cast<std::string>(response_text) == "412") { std::cout << "Precondition Failed"; }
		else if (static_cast<std::string>(response_text) == "413") { std::cout << "Request Entity Too Large"; }
		else if (static_cast<std::string>(response_text) == "414") { std::cout << "Request-URI Too Long"; }
		else if (static_cast<std::string>(response_text) == "415") { std::cout << "Unsupported Media Type"; }
		else if (static_cast<std::string>(response_text) == "416") { std::cout << "Requested Range Not Satisfiable"; }
		else if (static_cast<std::string>(response_text) == "417") { std::cout << "Expectation Failed"; }
		else if (static_cast<std::string>(response_text) == "418") { std::cout << "I\'m a teapot"; } // :)
		else if (static_cast<std::string>(response_text) == "419") { std::cout << "Authentication Timeout"; }
		else if (static_cast<std::string>(response_text) == "420") { std::cout << "Method Failure"; }
		else if (static_cast<std::string>(response_text) == "421") { std::cout << "Misdirected Request"; }
		else if (static_cast<std::string>(response_text) == "422") { std::cout << "Unprocessable Entity"; }
		else if (static_cast<std::string>(response_text) == "423") { std::cout << "Locked"; }
		else if (static_cast<std::string>(response_text) == "424") { std::cout << "Failed Dependency"; }
		else if (static_cast<std::string>(response_text) == "426") { std::cout << "Upgrade Required"; }
		else if (static_cast<std::string>(response_text) == "428") { std::cout << "Precondition Required"; }
		else if (static_cast<std::string>(response_text) == "429") { std::cout << "Too Many Requests"; }
		else if (static_cast<std::string>(response_text) == "431") { std::cout << "Request Header Fields Too Large"; }
		else if (static_cast<std::string>(response_text) == "440") { std::cout << "Login Timeout"; }
		else if (static_cast<std::string>(response_text) == "444") { std::cout << "No Response"; }
		else if (static_cast<std::string>(response_text) == "449") { std::cout << "Retry With"; }
		else if (static_cast<std::string>(response_text) == "450") { std::cout << "Blocked by Windows Parental Controls"; }
		else if (static_cast<std::string>(response_text) == "451") { std::cout << "Unavailable For Legal Reasons"; }
		else if (static_cast<std::string>(response_text) == "494") { std::cout << "Request Header Too Large"; }
		else if (static_cast<std::string>(response_text) == "495") { std::cout << "Cert Error"; }
		else if (static_cast<std::string>(response_text) == "496") { std::cout << "No Cert"; }
		else if (static_cast<std::string>(response_text) == "497") { std::cout << "HTTP to HTTPS"; }
		else if (static_cast<std::string>(response_text) == "498") { std::cout << "Token Expired/Invalid"; }
		else if (static_cast<std::string>(response_text) == "499") { std::cout << "Client Closed Request"; }
		// 500s
		else if (static_cast<std::string>(response_text) == "500") { std::cout << "Internal Server Error"; }
		else if (static_cast<std::string>(response_text) == "501") { std::cout << "Not Implemented"; }
		else if (static_cast<std::string>(response_text) == "502") { std::cout << "Bad Gateway"; }
		else if (static_cast<std::string>(response_text) == "503") { std::cout << "Service Unavailable"; }
		else if (static_cast<std::string>(response_text) == "504") { std::cout << "Gateway Timeout"; }
		else if (static_cast<std::string>(response_text) == "505") { std::cout << "HTTP Version Not Supported"; }
		else if (static_cast<std::string>(response_text) == "506") { std::cout << "Variant Also Negotiates"; }
		else if (static_cast<std::string>(response_text) == "507") { std::cout << "Insufficient Storage"; }
		else if (static_cast<std::string>(response_text) == "508") { std::cout << "Loop Detected"; }
		else if (static_cast<std::string>(response_text) == "509") { std::cout << "Bandwidth Limit Exceeded"; }
		else if (static_cast<std::string>(response_text) == "510") { std::cout << "Not Extended"; }
		else if (static_cast<std::string>(response_text) == "511") { std::cout << "Network Authentication Required"; }
		else if (static_cast<std::string>(response_text) == "520") { std::cout << "Unknown Error"; }
		else if (static_cast<std::string>(response_text) == "598") { std::cout << "Network Read Timeout Error"; }
		else if (static_cast<std::string>(response_text) == "599") { std::cout << "Network Connect Timeout Error"; }
		std::cout << "\n";
	}
	InternetCloseHandle(h_open);
	InternetCloseHandle(h_file);
	return atoi(response_text);
}
