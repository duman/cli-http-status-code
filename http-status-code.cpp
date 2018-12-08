#include "duman.h"

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
