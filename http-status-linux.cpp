#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

int response_code(const char* url, const bool display_text = true)
{
	long response_text;
	CURL *curl = curl_easy_init();

	if(curl) {
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
		res = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_text);
		curl_easy_cleanup(curl);
	}

	if (display_text)
	{
		if (response_text == 0)
		{
			cout << "Remote server is offline or unreachable, connection timed out.\n";
			return 0;
		}
		cout << url << "\t" << "Response: " << response_text << " ";
		// 100s
		if (to_string(response_text) == "100") { cout << "Continue"; }
		else if (to_string(response_text) == "101") { cout << "Switching Protocols"; }
		else if (to_string(response_text) == "102") { cout << "Processing"; }
		// 200s
		else if (to_string(response_text) == "200") { cout << "OK"; }
		else if (to_string(response_text) == "201") { cout << "Created"; }
		else if (to_string(response_text) == "202") { cout << "Accepted"; }
		else if (to_string(response_text) == "203") { cout << "Non-Authoritative Information"; }
		else if (to_string(response_text) == "204") { cout << "No Content"; }
		else if (to_string(response_text) == "205") { cout << "Reset Content"; }
		else if (to_string(response_text) == "206") { cout << "Partial Content"; }
		else if (to_string(response_text) == "207") { cout << "Multi-Status"; }
		else if (to_string(response_text) == "208") { cout << "Already Reported"; }
		else if (to_string(response_text) == "226") { cout << "IM Used"; }
		// 300s
		else if (to_string(response_text) == "300") { cout << "Multiple Choices"; }
		else if (to_string(response_text) == "301") { cout << "Moved Permanently"; }
		else if (to_string(response_text) == "302") { cout << "Found"; }
		else if (to_string(response_text) == "303") { cout << "See Other"; }
		else if (to_string(response_text) == "304") { cout << "Not Modified"; }
		else if (to_string(response_text) == "305") { cout << "Use Proxy"; }
		else if (to_string(response_text) == "306") { cout << "Switch Proxy"; }
		else if (to_string(response_text) == "307") { cout << "Temporary Redirect"; }
		else if (to_string(response_text) == "308") { cout << "Permanent Redirect"; }
		// 400s
		else if (to_string(response_text) == "400") { cout << "Bad Request"; }
		else if (to_string(response_text) == "401") { cout << "Unauthorized"; }
		else if (to_string(response_text) == "402") { cout << "Payment Required"; }
		else if (to_string(response_text) == "403") { cout << "Forbidden"; }
		else if (to_string(response_text) == "404") { cout << "Not Found"; }
		else if (to_string(response_text) == "405") { cout << "Method Not Allowed"; }
		else if (to_string(response_text) == "406") { cout << "Not Acceptable"; }
		else if (to_string(response_text) == "407") { cout << "Proxy Authentication Required"; }
		else if (to_string(response_text) == "408") { cout << "Request Timeout"; }
		else if (to_string(response_text) == "409") { cout << "Conflict"; }
		else if (to_string(response_text) == "410") { cout << "Gone"; }
		else if (to_string(response_text) == "411") { cout << "Length Required"; }
		else if (to_string(response_text) == "412") { cout << "Precondition Failed"; }
		else if (to_string(response_text) == "413") { cout << "Request Entity Too Large"; }
		else if (to_string(response_text) == "414") { cout << "Request-URI Too Long"; }
		else if (to_string(response_text) == "415") { cout << "Unsupported Media Type"; }
		else if (to_string(response_text) == "416") { cout << "Requested Range Not Satisfiable"; }
		else if (to_string(response_text) == "417") { cout << "Expectation Failed"; }
		else if (to_string(response_text) == "418") { cout << "I\'m a teapot"; } // :)
		else if (to_string(response_text) == "419") { cout << "Authentication Timeout"; }
		else if (to_string(response_text) == "420") { cout << "Method Failure"; }
		else if (to_string(response_text) == "421") { cout << "Misdirected Request"; }
		else if (to_string(response_text) == "422") { cout << "Unprocessable Entity"; }
		else if (to_string(response_text) == "423") { cout << "Locked"; }
		else if (to_string(response_text) == "424") { cout << "Failed Dependency"; }
		else if (to_string(response_text) == "426") { cout << "Upgrade Required"; }
		else if (to_string(response_text) == "428") { cout << "Precondition Required"; }
		else if (to_string(response_text) == "429") { cout << "Too Many Requests"; }
		else if (to_string(response_text) == "431") { cout << "Request Header Fields Too Large"; }
		else if (to_string(response_text) == "440") { cout << "Login Timeout"; }
		else if (to_string(response_text) == "444") { cout << "No Response"; }
		else if (to_string(response_text) == "449") { cout << "Retry With"; }
		else if (to_string(response_text) == "450") { cout << "Blocked by Windows Parental Controls"; }
		else if (to_string(response_text) == "451") { cout << "Unavailable For Legal Reasons"; }
		else if (to_string(response_text) == "494") { cout << "Request Header Too Large"; }
		else if (to_string(response_text) == "495") { cout << "Cert Error"; }
		else if (to_string(response_text) == "496") { cout << "No Cert"; }
		else if (to_string(response_text) == "497") { cout << "HTTP to HTTPS"; }
		else if (to_string(response_text) == "498") { cout << "Token Expired/Invalid"; }
		else if (to_string(response_text) == "499") { cout << "Client Closed Request"; }
		// 500s
		else if (to_string(response_text) == "500") { cout << "Internal Server Error"; }
		else if (to_string(response_text) == "501") { cout << "Not Implemented"; }
		else if (to_string(response_text) == "502") { cout << "Bad Gateway"; }
		else if (to_string(response_text) == "503") { cout << "Service Unavailable"; }
		else if (to_string(response_text) == "504") { cout << "Gateway Timeout"; }
		else if (to_string(response_text) == "505") { cout << "HTTP Version Not Supported"; }
		else if (to_string(response_text) == "506") { cout << "Variant Also Negotiates"; }
		else if (to_string(response_text) == "507") { cout << "Insufficient Storage"; }
		else if (to_string(response_text) == "508") { cout << "Loop Detected"; }
		else if (to_string(response_text) == "509") { cout << "Bandwidth Limit Exceeded"; }
		else if (to_string(response_text) == "510") { cout << "Not Extended"; }
		else if (to_string(response_text) == "511") { cout << "Network Authentication Required"; }
		else if (to_string(response_text) == "520") { cout << "Unknown Error"; }
		else if (to_string(response_text) == "598") { cout << "Network Read Timeout Error"; }
		else if (to_string(response_text) == "599") { cout << "Network Connect Timeout Error"; }
		cout << "\n";
	}
	return response_text;
}

int main(int argc, char* argv[])
{
	string response_text = argv[1];
	if (response_text.length() < 3)
	{
		cout << "Please make sure that you have entered a valid URL or a valid status code.\n";
		return 0;
	}
	if (response_text.length() == 3)
	{
		if (!isdigit(response_text[0]) || !isdigit(response_text[1]) || !isdigit(response_text[2]))
		{
			cout << "Please make sure that you have entered a valid URL or a valid status code.\n";
			return 0;
		}
		// 100s
		if (response_text == "100") { cout << "Continue"; }
		else if (response_text == "101") { cout << "Switching Protocols"; }
		else if (response_text == "102") { cout << "Processing"; }
		// 200s
		else if (response_text == "200") { cout << "OK"; }
		else if (response_text == "201") { cout << "Created"; }
		else if (response_text == "202") { cout << "Accepted"; }
		else if (response_text == "203") { cout << "Non-Authoritative Information"; }
		else if (response_text == "204") { cout << "No Content"; }
		else if (response_text == "205") { cout << "Reset Content"; }
		else if (response_text == "206") { cout << "Partial Content"; }
		else if (response_text == "207") { cout << "Multi-Status"; }
		else if (response_text == "208") { cout << "Already Reported"; }
		else if (response_text == "226") { cout << "IM Used"; }
		// 300s
		else if (response_text == "300") { cout << "Multiple Choices"; }
		else if (response_text == "301") { cout << "Moved Permanently"; }
		else if (response_text == "302") { cout << "Found"; }
		else if (response_text == "303") { cout << "See Other"; }
		else if (response_text == "304") { cout << "Not Modified"; }
		else if (response_text == "305") { cout << "Use Proxy"; }
		else if (response_text == "306") { cout << "Switch Proxy"; }
		else if (response_text == "307") { cout << "Temporary Redirect"; }
		else if (response_text == "308") { cout << "Permanent Redirect"; }
		// 400s
		else if (response_text == "400") { cout << "Bad Request"; }
		else if (response_text == "401") { cout << "Unauthorized"; }
		else if (response_text == "402") { cout << "Payment Required"; }
		else if (response_text == "403") { cout << "Forbidden"; }
		else if (response_text == "404") { cout << "Not Found"; }
		else if (response_text == "405") { cout << "Method Not Allowed"; }
		else if (response_text == "406") { cout << "Not Acceptable"; }
		else if (response_text == "407") { cout << "Proxy Authentication Required"; }
		else if (response_text == "408") { cout << "Request Timeout"; }
		else if (response_text == "409") { cout << "Conflict"; }
		else if (response_text == "410") { cout << "Gone"; }
		else if (response_text == "411") { cout << "Length Required"; }
		else if (response_text == "412") { cout << "Precondition Failed"; }
		else if (response_text == "413") { cout << "Request Entity Too Large"; }
		else if (response_text == "414") { cout << "Request-URI Too Long"; }
		else if (response_text == "415") { cout << "Unsupported Media Type"; }
		else if (response_text == "416") { cout << "Requested Range Not Satisfiable"; }
		else if (response_text == "417") { cout << "Expectation Failed"; }
		else if (response_text == "418") { cout << "I\'m a teapot"; } // :)
		else if (response_text == "419") { cout << "Authentication Timeout"; }
		else if (response_text == "420") { cout << "Method Failure"; }
		else if (response_text == "421") { cout << "Misdirected Request"; }
		else if (response_text == "422") { cout << "Unprocessable Entity"; }
		else if (response_text == "423") { cout << "Locked"; }
		else if (response_text == "424") { cout << "Failed Dependency"; }
		else if (response_text == "426") { cout << "Upgrade Required"; }
		else if (response_text == "428") { cout << "Precondition Required"; }
		else if (response_text == "429") { cout << "Too Many Requests"; }
		else if (response_text == "431") { cout << "Request Header Fields Too Large"; }
		else if (response_text == "440") { cout << "Login Timeout"; }
		else if (response_text == "444") { cout << "No Response"; }
		else if (response_text == "449") { cout << "Retry With"; }
		else if (response_text == "450") { cout << "Blocked by Windows Parental Controls"; }
		else if (response_text == "451") { cout << "Unavailable For Legal Reasons"; }
		else if (response_text == "494") { cout << "Request Header Too Large"; }
		else if (response_text == "495") { cout << "Cert Error"; }
		else if (response_text == "496") { cout << "No Cert"; }
		else if (response_text == "497") { cout << "HTTP to HTTPS"; }
		else if (response_text == "498") { cout << "Token Expired/Invalid"; }
		else if (response_text == "499") { cout << "Client Closed Request"; }
		// 500s
		else if (response_text == "500") { cout << "Internal Server Error"; }
		else if (response_text == "501") { cout << "Not Implemented"; }
		else if (response_text == "502") { cout << "Bad Gateway"; }
		else if (response_text == "503") { cout << "Service Unavailable"; }
		else if (response_text == "504") { cout << "Gateway Timeout"; }
		else if (response_text == "505") { cout << "HTTP Version Not Supported"; }
		else if (response_text == "506") { cout << "Variant Also Negotiates"; }
		else if (response_text == "507") { cout << "Insufficient Storage"; }
		else if (response_text == "508") { cout << "Loop Detected"; }
		else if (response_text == "509") { cout << "Bandwidth Limit Exceeded"; }
		else if (response_text == "510") { cout << "Not Extended"; }
		else if (response_text == "511") { cout << "Network Authentication Required"; }
		else if (response_text == "520") { cout << "Unknown Error"; }
		else if (response_text == "598") { cout << "Network Read Timeout Error"; }
		else if (response_text == "599") { cout << "Network Connect Timeout Error"; }
		cout << "\n";
	}
	if (response_text.length() > 3)
	{
		response_code(response_text.c_str());
		return 0;
	}
}
