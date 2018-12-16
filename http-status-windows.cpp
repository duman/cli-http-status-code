#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <Windows.h>
#include <WinInet.h>
#include <curl/curl.h>
#include <regex>
#pragma comment(lib, "Wininet")

int response_code(const std::string& url, const bool display_text = true);
size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);

int main(int argc, char* argv[])
{
	std::string response_text = argv[1];
	std::string regex_rule = "^(?:http(s)?:\\/\\/)?[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:/?#[\\]@!\\$&'\\(\\)\\*\\+,;=.]+$";

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide_regex_rule = converter.from_bytes(regex_rule);
	std::wstring wide_domain = converter.from_bytes(response_text);
	std::wregex rx(wide_regex_rule);
	if (!regex_match(wide_domain, rx) && response_text.length() > 3)
	{
		std::cout << "Please make sure that you have entered a valid URL.\n\n";
		exit(EXIT_FAILURE);
	}
	if (response_text.length() < 3)
	{
		std::cout << "Please make sure that you have entered a valid URL or a valid status code.\n\n";
		exit(EXIT_FAILURE);
	}
	if (response_text.length() == 3)
	{
		// 100s
		if (response_text == "100") { std::cout << "Continue\n\nDescription: The initial part of a request has been received and has not yet been rejected by the server. The server intends to send a final response after the request has been fully received and acted upon."; }
		else if (response_text == "101") { std::cout << "Switching Protocols\n\nDescription: The server understands and is willing to comply with the client's request, via the Upgrade header field, for a change in the application protocol being used on this connection."; }
		else if (response_text == "102") { std::cout << "Processing\n\nDescription: An interim response used to inform the client that the server has accepted the complete request, but has not yet completed it."; }
		// 200s
		else if (response_text == "200") { std::cout << "OK\n\nDescription: The request has succeeded."; }
		else if (response_text == "201") { std::cout << "Created\n\nDescription: The request has been fulfilled and has resulted in one or more new resources being created."; }
		else if (response_text == "202") { std::cout << "Accepted\n\nDescription: The request has been accepted for processing, but the processing has not been completed. The request might or might not eventually be acted upon, as it might be disallowed when processing actually takes place."; }
		else if (response_text == "203") { std::cout << "Non-Authoritative Information\n\nDescription: The request was successful but the enclosed payload has been modified from that of the origin server's 200 OK response by a transforming proxy."; }
		else if (response_text == "204") { std::cout << "No Content\n\nDescription: The server has successfully fulfilled the request and that there is no additional content to send in the response payload body."; }
		else if (response_text == "205") { std::cout << "Reset Content\n\nDescription: The server has fulfilled the request and desires that the user agent reset the \"document view\", which caused the request to be sent, to its original state as received from the origin server."; }
		else if (response_text == "206") { std::cout << "Partial Content\n\nDescription: The server is successfully fulfilling a range request for the target resource by transferring one or more parts of the selected representation that correspond to the satisfiable ranges found in the request's Range header field."; }
		else if (response_text == "207") { std::cout << "Multi-Status\n\nDescription: A Multi-Status response conveys information about multiple resources in situations where multiple status codes might be appropriate."; }
		else if (response_text == "208") { std::cout << "Already Reported\n\nDescription: Used inside a DAV: propstat response element to avoid enumerating the internal members of multiple bindings to the same collection repeatedly."; }
		else if (response_text == "226") { std::cout << "IM Used\n\nDescription: The server has fulfilled a GET request for the resource, and the response is a representation of the result of one or more instance-manipulations applied to the current instance."; }
		// 300s
		else if (response_text == "300") { std::cout << "Multiple Choices\n\nDescription: The target resource has more than one representation, each with its own more specific identifier, and information about the alternatives is being provided so that the user (or user agent) can select a preferred representation by redirecting its request to one or more of those identifiers."; }
		else if (response_text == "301") { std::cout << "Moved Permanently\n\nDescription: The target resource has been assigned a new permanent URI and any future references to this resource ought to use one of the enclosed URIs."; }
		else if (response_text == "302") { std::cout << "Found\n\nDescription: The target resource resides temporarily under a different URI. Since the redirection might be altered on occasion, the client ought to continue to use the effective request URI for future requests."; }
		else if (response_text == "303") { std::cout << "See Other\n\nDescription: The server is redirecting the user agent to a different resource, as indicated by a URI in the Location header field, which is intended to provide an indirect response to the original request."; }
		else if (response_text == "304") { std::cout << "Not Modified\n\nDescription: A conditional GET or HEAD request has been received and would have resulted in a 200 OK response if it were not for the fact that the condition evaluated to false."; }
		else if (response_text == "305") { std::cout << "Use Proxy\n\nDescription: Defined in a previous version of this specification and is now deprecated, due to security concerns regarding in-band configuration of a proxy."; }
		else if (response_text == "306") { std::cout << "Switch Proxy\n\nDescription: Subsequent requests should use the specified proxy."; }
		else if (response_text == "307") { std::cout << "Temporary Redirect\n\nDescription: The target resource resides temporarily under a different URI and the user agent MUST NOT change the request method if it performs an automatic redirection to that URI."; }
		else if (response_text == "308") { std::cout << "Permanent Redirect\n\nDescription: The target resource has been assigned a new permanent URI and any future references to this resource ought to use one of the enclosed URIs."; }
		// 400s
		else if (response_text == "400") { std::cout << "Bad Request\n\nDescription: The server cannot or will not process the request due to something that is perceived to be a client error (e.g., malformed request syntax, invalid request message framing, or deceptive request routing)."; }
		else if (response_text == "401") { std::cout << "Unauthorized\n\nDescription: The request has not been applied because it lacks valid authentication credentials for the target resource."; }
		else if (response_text == "402") { std::cout << "Payment Required\n\nDescription: Reserved for future use."; }
		else if (response_text == "403") { std::cout << "Forbidden\n\nDescription: The server understood the request but refuses to authorize it."; }
		else if (response_text == "404") { std::cout << "Not Found\n\nDescription: The origin server did not find a current representation for the target resource or is not willing to disclose that one exists."; }
		else if (response_text == "405") { std::cout << "Method Not Allowed\n\nDescription: The method received in the request-line is known by the origin server but not supported by the target resource."; }
		else if (response_text == "406") { std::cout << "Not Acceptable\n\nDescription: The target resource does not have a current representation that would be acceptable to the user agent, according to the proactive negotiation header fields received in the request, and the server is unwilling to supply a default representation."; }
		else if (response_text == "407") { std::cout << "Proxy Authentication Required\n\nDescription: Similar to 401 Unauthorized, but it indicates that the client needs to authenticate itself in order to use a proxy."; }
		else if (response_text == "408") { std::cout << "Request Timeout\n\nDescription: The server did not receive a complete request message within the time that it was prepared to wait."; }
		else if (response_text == "409") { std::cout << "Conflict\n\nDescription: The request could not be completed due to a conflict with the current state of the target resource. This code is used in situations where the user might be able to resolve the conflict and resubmit the request."; }
		else if (response_text == "410") { std::cout << "Gone\n\nDescription: The target resource is no longer available at the origin server and that this condition is likely to be permanent."; }
		else if (response_text == "411") { std::cout << "Length Required\n\nDescription: The server refuses to accept the request without a defined Content-Length."; }
		else if (response_text == "412") { std::cout << "Precondition Failed\n\nDescription: One or more conditions given in the request header fields evaluated to false when tested on the server."; }
		else if (response_text == "413") { std::cout << "Payload Too Large\n\nDescription: The server is refusing to process a request because the request payload is larger than the server is willing or able to process."; }
		else if (response_text == "414") { std::cout << "Request-URI Too Long\n\nDescription: The server is refusing to service the request because the request-target is longer than the server is willing to interpret."; }
		else if (response_text == "415") { std::cout << "Unsupported Media Type\n\nDescription: The origin server is refusing to service the request because the payload is in a format not supported by this method on the target resource."; }
		else if (response_text == "416") { std::cout << "Requested Range Not Satisfiable\n\nDescription: None of the ranges in the request's Range header field overlap the current extent of the selected resource or that the set of ranges requested has been rejected due to invalid ranges or an excessive request of small or overlapping ranges."; }
		else if (response_text == "417") { std::cout << "Expectation Failed\n\nDescription: The expectation given in the request's Expect header field could not be met by at least one of the inbound servers."; }
		else if (response_text == "418") { std::cout << "I\'m a teapot\n\nDescription: Any attempt to brew coffee with a teapot should result in the error code \"418 I'm a teapot\". The resulting entity body MAY be short and stout."; } // :)
		else if (response_text == "419") { std::cout << "Authentication Timeout\n\nDescription: Not a part of the HTTP standard, 419 Authentication Timeout denotes that previously valid authentication has expired. It is used as an alternative to 401 Unauthorized in order to differentiate from otherwise authenticated clients being denied access to specific server resources."; }
		else if (response_text == "420") { std::cout << "Method Failure / Enhance Your Calm (Twitter)\n\nDescription 1: Not part of the HTTP standard, but defined by Spring in the HttpStatus class to be used when a method failed. This status code is deprecated by Spring.\n\nDescription 2: Not part of the HTTP standard, but returned by version 1 of the Twitter Search and Trends API when the client is being rate limited. Other services may wish to implement the 429 Too Many Requests response code instead."; }
		else if (response_text == "421") { std::cout << "Misdirected Request\n\nDescription: The request was directed at a server that is not able to produce a response. This can be sent by a server that is not configured to produce responses for the combination of scheme and authority that are included in the request URI."; }
		else if (response_text == "422") { std::cout << "Unprocessable Entity\n\nDescription: The server understands the content type of the request entity (hence a 415 Unsupported Media Type status code is inappropriate), and the syntax of the request entity is correct (thus a 400 Bad Request status code is inappropriate) but was unable to process the contained instructions."; }
		else if (response_text == "423") { std::cout << "Locked\n\nDescription: The source or destination resource of a method is locked."; }
		else if (response_text == "424") { std::cout << "Failed Dependency\n\nDescription: The method could not be performed on the resource because the requested action depended on another action and that action failed."; }
		else if (response_text == "425") { std::cout << "Unordered Collection\n\nDescription: Defined in drafts of WebDAV Advanced Collections Protocol, but not present in Web Distributed Authoring and Versioning (WebDAV) Ordered Collections Protocol."; }
		else if (response_text == "426") { std::cout << "Upgrade Required\n\nDescription: The server refuses to perform the request using the current protocol but might be willing to do so after the client upgrades to a different protocol."; }
		else if (response_text == "428") { std::cout << "Precondition Required\n\nDescription: The origin server requires the request to be conditional."; }
		else if (response_text == "429") { std::cout << "Too Many Requests\n\nDescription: The user has sent too many requests in a given amount of time (\"rate limiting\")."; }
		else if (response_text == "431") { std::cout << "Request Header Fields Too Large\n\nDescription: The server is unwilling to process the request because its header fields are too large. The request MAY be resubmitted after reducing the size of the request header fields."; }
		else if (response_text == "440") { std::cout << "Login Timeout\n\nDescription: A Microsoft extension. Indicates that your session has expired."; }
		else if (response_text == "444") { std::cout << "No Response\n\nDescription: A non-standard status code used to instruct nginx to close the connection without sending a response to the client, most commonly used to deny malicious or malformed requests."; }
		else if (response_text == "449") { std::cout << "Retry With\n\nDescription: A Microsoft extension. The request should be retried after performing the appropriate action. Often search-engines or custom applications will ignore required parameters. Where no default action is appropriate, the Aviongoo website sends a \"HTTP / 1.1 Retry with valid parameters : param1, param2, . . .\" response. The applications may choose to learn, or not."; }
		else if (response_text == "450") { std::cout << "Blocked by Windows Parental Controls\n\nDescription: A Microsoft extension. This error is given when Windows Parental Controls are turned on and are blocking access to the given webpage"; }
		else if (response_text == "451") { std::cout << "Unavailable For Legal Reasons\n\nDescription: The server is denying access to the resource as a consequence of a legal demand."; }
		else if (response_text == "494") { std::cout << "Request Header Too Large\n\nDescription: Nginx internal code similar to 431 but it was introduced earlier."; }
		else if (response_text == "495") { std::cout << "Cert Error\n\nDescription: Nginx internal code used when SSL client certificate error occurred to distinguish it from 4XX in a log and an error page redirection."; }
		else if (response_text == "496") { std::cout << "No Cert\n\nDescription: Nginx internal code used when client didn't provide certificate to distinguish it from 4XX in a log and an error page redirection."; }
		else if (response_text == "497") { std::cout << "HTTP to HTTPS\n\nDescription: Nginx internal code used for the plain HTTP requests that are sent to HTTPS port to distinguish it from 4XX in a log and an error page redirection."; }
		else if (response_text == "498") { std::cout << "Token Expired / Invalid\n\nDescription: Returned by ArcGIS for Server. A code of 498 indicates an expired or otherwise invalid token."; }
		else if (response_text == "499") { std::cout << "Client Closed Request (Nginx)/Token required (Esri)\n\nDescription 1: Used in Nginx logs to indicate when the connection has been closed by client while the server is still processing its request, making server unable to send a status code back.\n\nDescription 2: Returned by ArcGIS for Server. A code of 499 indicates that a token is required (if no token was submitted)."; }
		// 500s
		else if (response_text == "500") { std::cout << "Internal Server Error\n\nDescription: The server encountered an unexpected condition that prevented it from fulfilling the request."; }
		else if (response_text == "501") { std::cout << "Not Implemented\n\nDescription: The server does not support the functionality required to fulfill the request."; }
		else if (response_text == "502") { std::cout << "Bad Gateway\n\nDescription: The server, while acting as a gateway or proxy, received an invalid response from an inbound server it accessed while attempting to fulfill the request."; }
		else if (response_text == "503") { std::cout << "Service Unavailable\n\nDescription: The server is currently unable to handle the request due to a temporary overload or scheduled maintenance, which will likely be alleviated after some delay."; }
		else if (response_text == "504") { std::cout << "Gateway Timeout\n\nDescription: The server, while acting as a gateway or proxy, did not receive a timely response from an upstream server it needed to access in order to complete the request."; }
		else if (response_text == "505") { std::cout << "HTTP Version Not Supported\n\nDescription: The server does not support, or refuses to support, the major version of HTTP that was used in the request message."; }
		else if (response_text == "506") { std::cout << "Variant Also Negotiates\n\nDescription: The server has an internal configuration error: the chosen variant resource is configured to engage in transparent content negotiation itself, and is therefore not a proper end point in the negotiation process."; }
		else if (response_text == "507") { std::cout << "Insufficient Storage\n\nDescription: The method could not be performed on the resource because the server is unable to store the representation needed to successfully complete the request."; }
		else if (response_text == "508") { std::cout << "Loop Detected\n\nDescription: The server terminated an operation because it encountered an infinite loop while processing a request with \"Depth: infinity\". This status indicates that the entire operation failed."; }
		else if (response_text == "509") { std::cout << "Bandwidth Limit Exceeded (Apache)\n\nDescription: This status code is not specified in any RFCs. Its use is unknown."; }
		else if (response_text == "510") { std::cout << "Not Extended\n\nDescription: The policy for accessing the resource has not been met in the request. The server should send back all the information necessary for the client to issue an extended request."; }
		else if (response_text == "511") { std::cout << "Network Authentication Required\n\nDescription: The client needs to authenticate to gain network access."; }
		// CLOUDFLARE START
		else if (response_text == "520") { std::cout << "Unknown Error (CloudFlare)\n\nDescription: A generic response when the origin server returns something unexpected"; }
		else if (response_text == "521") { std::cout << "Web Server Is Down (CloudFlare)\n\nDescription: The origin server is refusing connections from CloudFlare"; }
		else if (response_text == "522") { std::cout << "Connection Timed Out (CloudFlare)\n\nDescription: A TCP handshake cannot be negotiated with the origin server"; }
		else if (response_text == "523") { std::cout << "Origin Is Unreachable (CloudFlare)\n\nDescription: CloudFlare can't reach the origin server (e.g. because of a DNS error)"; }
		else if (response_text == "524") { std::cout << "A Timeout Occurred (CloudFlare)\n\nDescription: A TCP connection to the origin server was completed, but a response wasn't received in time"; }
		else if (response_text == "525") { std::cout << "SSL Handshake Failed (CloudFlare)\n\nDescription: A SSL/TLS handshake couldn't be negotiated with the origin server"; }
		else if (response_text == "526") { std::cout << "Invalid SSL Certificate (CloudFlare)\n\nDescription: The SSL/TSL certificate presented by the origin server couldn't be validated"; }
		// CLOUDFLARE END
		else if (response_text == "598") { std::cout << "Network Read Timeout Error\n\nDescription: This status code is not specified in any RFCs, but is used by Microsoft HTTP proxies to signal a network read timeout behind the proxy to a client in front of the proxy."; }
		else if (response_text == "599") { std::cout << "Network Connect Timeout Error\n\nDescription: This status code is not specified in any RFCs, but is used by Microsoft HTTP proxies to signal a network connect timeout behind the proxy to a client in front of the proxy."; }
		std::cout << "\n";
	}
	if (response_text.length() > 3) // unicode is not supported yet
	{
		std::string header_enable = "DumanDIGITAL";
		if (argc > 2)
		{
			header_enable.clear();
			header_enable = argv[2];
		}
		if (response_text.substr(0, 5) == "http:" || response_text.substr(0, 6) == "https:")
		{
			response_code(response_text);
			if (header_enable == "-h" || header_enable == "h")
			{
				CURL *curl = curl_easy_init();
				if (curl)
				{
					std::cout << "\nHeader:\n";
					curl_easy_setopt(curl, CURLOPT_URL, response_text.c_str());
					curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
					// curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
					// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
					curl_easy_setopt(curl, CURLOPT_USERAGENT, "DumanDIGITAL");
					curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
					std::string response_string;
					std::string header_string;
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
					curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
					char* url;
					long response_code;
					double elapsed;
					curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
					curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
					curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

					curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					curl = NULL;
					std::cout << header_string;
				}
			}
			else {
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			response_text.insert(0, "https://");
			response_code(response_text);
			if (header_enable == "-h" || header_enable == "h")
			{
				CURL *curl = curl_easy_init();
				if (curl)
				{
					std::cout << "\nHeader:\n";
					curl_easy_setopt(curl, CURLOPT_URL, response_text.c_str());
					curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
					// curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
					// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
					curl_easy_setopt(curl, CURLOPT_USERAGENT, "DumanDIGITAL");
					curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
					std::string response_string;
					std::string header_string;
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
					curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
					char* url;
					long response_code;
					double elapsed;
					std::string header_in;
					curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
					curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
					curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

					curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					curl = NULL;
					std::cout << header_string;
				}
			}
			else {
				exit(EXIT_SUCCESS);
			}
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
			std::cout << "Remote server is offline or unreachable.\n\n";
		InternetCloseHandle(h_open);
		InternetCloseHandle(h_file);
		exit(EXIT_FAILURE);
	}

	if (display_text)
	{
		std::cout << url << "\t" << "Response: " << response_text << " ";
		// 100s
		if (static_cast<std::string>(response_text) == "100") { std::cout << "Continue\n\nDescription: The initial part of a request has been received and has not yet been rejected by the server. The server intends to send a final response after the request has been fully received and acted upon."; }
		else if (static_cast<std::string>(response_text) == "101") { std::cout << "Switching Protocols\n\nDescription: The server understands and is willing to comply with the client's request, via the Upgrade header field, for a change in the application protocol being used on this connection."; }
		else if (static_cast<std::string>(response_text) == "102") { std::cout << "Processing\n\nDescription: An interim response used to inform the client that the server has accepted the complete request, but has not yet completed it."; }
		// 200s
		else if (static_cast<std::string>(response_text) == "200") { std::cout << "OK\n\nDescription: The request has succeeded."; }
		else if (static_cast<std::string>(response_text) == "201") { std::cout << "Created\n\nDescription: The request has been fulfilled and has resulted in one or more new resources being created."; }
		else if (static_cast<std::string>(response_text) == "202") { std::cout << "Accepted\n\nDescription: The request has been accepted for processing, but the processing has not been completed. The request might or might not eventually be acted upon, as it might be disallowed when processing actually takes place."; }
		else if (static_cast<std::string>(response_text) == "203") { std::cout << "Non-Authoritative Information\n\nDescription: The request was successful but the enclosed payload has been modified from that of the origin server's 200 OK response by a transforming proxy."; }
		else if (static_cast<std::string>(response_text) == "204") { std::cout << "No Content\n\nDescription: The server has successfully fulfilled the request and that there is no additional content to send in the response payload body."; }
		else if (static_cast<std::string>(response_text) == "205") { std::cout << "Reset Content\n\nDescription: The server has fulfilled the request and desires that the user agent reset the \"document view\", which caused the request to be sent, to its original state as received from the origin server."; }
		else if (static_cast<std::string>(response_text) == "206") { std::cout << "Partial Content\n\nDescription: The server is successfully fulfilling a range request for the target resource by transferring one or more parts of the selected representation that correspond to the satisfiable ranges found in the request's Range header field."; }
		else if (static_cast<std::string>(response_text) == "207") { std::cout << "Multi-Status\n\nDescription: A Multi-Status response conveys information about multiple resources in situations where multiple status codes might be appropriate."; }
		else if (static_cast<std::string>(response_text) == "208") { std::cout << "Already Reported\n\nDescription: Used inside a DAV: propstat response element to avoid enumerating the internal members of multiple bindings to the same collection repeatedly."; }
		else if (static_cast<std::string>(response_text) == "226") { std::cout << "IM Used\n\nDescription: The server has fulfilled a GET request for the resource, and the response is a representation of the result of one or more instance-manipulations applied to the current instance."; }
		// 300s
		else if (static_cast<std::string>(response_text) == "300") { std::cout << "Multiple Choices\n\nDescription: The target resource has more than one representation, each with its own more specific identifier, and information about the alternatives is being provided so that the user (or user agent) can select a preferred representation by redirecting its request to one or more of those identifiers."; }
		else if (static_cast<std::string>(response_text) == "301") { std::cout << "Moved Permanently\n\nDescription: The target resource has been assigned a new permanent URI and any future references to this resource ought to use one of the enclosed URIs."; }
		else if (static_cast<std::string>(response_text) == "302") { std::cout << "Found\n\nDescription: The target resource resides temporarily under a different URI. Since the redirection might be altered on occasion, the client ought to continue to use the effective request URI for future requests."; }
		else if (static_cast<std::string>(response_text) == "303") { std::cout << "See Other\n\nDescription: The server is redirecting the user agent to a different resource, as indicated by a URI in the Location header field, which is intended to provide an indirect response to the original request."; }
		else if (static_cast<std::string>(response_text) == "304") { std::cout << "Not Modified\n\nDescription: A conditional GET or HEAD request has been received and would have resulted in a 200 OK response if it were not for the fact that the condition evaluated to false."; }
		else if (static_cast<std::string>(response_text) == "305") { std::cout << "Use Proxy\n\nDescription: Defined in a previous version of this specification and is now deprecated, due to security concerns regarding in-band configuration of a proxy."; }
		else if (static_cast<std::string>(response_text) == "306") { std::cout << "Switch Proxy\n\nDescription: Subsequent requests should use the specified proxy."; }
		else if (static_cast<std::string>(response_text) == "307") { std::cout << "Temporary Redirect\n\nDescription: The target resource resides temporarily under a different URI and the user agent MUST NOT change the request method if it performs an automatic redirection to that URI."; }
		else if (static_cast<std::string>(response_text) == "308") { std::cout << "Permanent Redirect\n\nDescription: The target resource has been assigned a new permanent URI and any future references to this resource ought to use one of the enclosed URIs."; }
		// 400s
		else if (static_cast<std::string>(response_text) == "400") { std::cout << "Bad Request\n\nDescription: The server cannot or will not process the request due to something that is perceived to be a client error (e.g., malformed request syntax, invalid request message framing, or deceptive request routing)."; }
		else if (static_cast<std::string>(response_text) == "401") { std::cout << "Unauthorized\n\nDescription: The request has not been applied because it lacks valid authentication credentials for the target resource."; }
		else if (static_cast<std::string>(response_text) == "402") { std::cout << "Payment Required\n\nDescription: Reserved for future use."; }
		else if (static_cast<std::string>(response_text) == "403") { std::cout << "Forbidden\n\nDescription: The server understood the request but refuses to authorize it."; }
		else if (static_cast<std::string>(response_text) == "404") { std::cout << "Not Found\n\nDescription: The origin server did not find a current representation for the target resource or is not willing to disclose that one exists."; }
		else if (static_cast<std::string>(response_text) == "405") { std::cout << "Method Not Allowed\n\nDescription: The method received in the request-line is known by the origin server but not supported by the target resource."; }
		else if (static_cast<std::string>(response_text) == "406") { std::cout << "Not Acceptable\n\nDescription: The target resource does not have a current representation that would be acceptable to the user agent, according to the proactive negotiation header fields received in the request, and the server is unwilling to supply a default representation."; }
		else if (static_cast<std::string>(response_text) == "407") { std::cout << "Proxy Authentication Required\n\nDescription: Similar to 401 Unauthorized, but it indicates that the client needs to authenticate itself in order to use a proxy."; }
		else if (static_cast<std::string>(response_text) == "408") { std::cout << "Request Timeout\n\nDescription: The server did not receive a complete request message within the time that it was prepared to wait."; }
		else if (static_cast<std::string>(response_text) == "409") { std::cout << "Conflict\n\nDescription: The request could not be completed due to a conflict with the current state of the target resource. This code is used in situations where the user might be able to resolve the conflict and resubmit the request."; }
		else if (static_cast<std::string>(response_text) == "410") { std::cout << "Gone\n\nDescription: The target resource is no longer available at the origin server and that this condition is likely to be permanent."; }
		else if (static_cast<std::string>(response_text) == "411") { std::cout << "Length Required\n\nDescription: The server refuses to accept the request without a defined Content-Length."; }
		else if (static_cast<std::string>(response_text) == "412") { std::cout << "Precondition Failed\n\nDescription: One or more conditions given in the request header fields evaluated to false when tested on the server."; }
		else if (static_cast<std::string>(response_text) == "413") { std::cout << "Payload Too Large\n\nDescription: The server is refusing to process a request because the request payload is larger than the server is willing or able to process."; }
		else if (static_cast<std::string>(response_text) == "414") { std::cout << "Request-URI Too Long\n\nDescription: The server is refusing to service the request because the request-target is longer than the server is willing to interpret."; }
		else if (static_cast<std::string>(response_text) == "415") { std::cout << "Unsupported Media Type\n\nDescription: The origin server is refusing to service the request because the payload is in a format not supported by this method on the target resource."; }
		else if (static_cast<std::string>(response_text) == "416") { std::cout << "Requested Range Not Satisfiable\n\nDescription: None of the ranges in the request's Range header field overlap the current extent of the selected resource or that the set of ranges requested has been rejected due to invalid ranges or an excessive request of small or overlapping ranges."; }
		else if (static_cast<std::string>(response_text) == "417") { std::cout << "Expectation Failed\n\nDescription: The expectation given in the request's Expect header field could not be met by at least one of the inbound servers."; }
		else if (static_cast<std::string>(response_text) == "418") { std::cout << "I\'m a teapot\n\nDescription: Any attempt to brew coffee with a teapot should result in the error code \"418 I'm a teapot\". The resulting entity body MAY be short and stout."; } // :)
		else if (static_cast<std::string>(response_text) == "419") { std::cout << "Authentication Timeout\n\nDescription: Not a part of the HTTP standard, 419 Authentication Timeout denotes that previously valid authentication has expired. It is used as an alternative to 401 Unauthorized in order to differentiate from otherwise authenticated clients being denied access to specific server resources."; }
		else if (static_cast<std::string>(response_text) == "420") { std::cout << "Method Failure / Enhance Your Calm (Twitter)\n\nDescription 1: Not part of the HTTP standard, but defined by Spring in the HttpStatus class to be used when a method failed. This status code is deprecated by Spring.\n\nDescription 2: Not part of the HTTP standard, but returned by version 1 of the Twitter Search and Trends API when the client is being rate limited. Other services may wish to implement the 429 Too Many Requests response code instead."; }
		else if (static_cast<std::string>(response_text) == "421") { std::cout << "Misdirected Request\n\nDescription: The request was directed at a server that is not able to produce a response. This can be sent by a server that is not configured to produce responses for the combination of scheme and authority that are included in the request URI."; }
		else if (static_cast<std::string>(response_text) == "422") { std::cout << "Unprocessable Entity\n\nDescription: The server understands the content type of the request entity (hence a 415 Unsupported Media Type status code is inappropriate), and the syntax of the request entity is correct (thus a 400 Bad Request status code is inappropriate) but was unable to process the contained instructions."; }
		else if (static_cast<std::string>(response_text) == "423") { std::cout << "Locked\n\nDescription: The source or destination resource of a method is locked."; }
		else if (static_cast<std::string>(response_text) == "424") { std::cout << "Failed Dependency\n\nDescription: The method could not be performed on the resource because the requested action depended on another action and that action failed."; }
		else if (static_cast<std::string>(response_text) == "425") { std::cout << "Unordered Collection\n\nDescription: Defined in drafts of WebDAV Advanced Collections Protocol, but not present in Web Distributed Authoring and Versioning (WebDAV) Ordered Collections Protocol."; }
		else if (static_cast<std::string>(response_text) == "426") { std::cout << "Upgrade Required\n\nDescription: The server refuses to perform the request using the current protocol but might be willing to do so after the client upgrades to a different protocol."; }
		else if (static_cast<std::string>(response_text) == "428") { std::cout << "Precondition Required\n\nDescription: The origin server requires the request to be conditional."; }
		else if (static_cast<std::string>(response_text) == "429") { std::cout << "Too Many Requests\n\nDescription: The user has sent too many requests in a given amount of time (\"rate limiting\")."; }
		else if (static_cast<std::string>(response_text) == "431") { std::cout << "Request Header Fields Too Large\n\nDescription: The server is unwilling to process the request because its header fields are too large. The request MAY be resubmitted after reducing the size of the request header fields."; }
		else if (static_cast<std::string>(response_text) == "440") { std::cout << "Login Timeout\n\nDescription: A Microsoft extension. Indicates that your session has expired."; }
		else if (static_cast<std::string>(response_text) == "444") { std::cout << "No Response\n\nDescription: A non-standard status code used to instruct nginx to close the connection without sending a response to the client, most commonly used to deny malicious or malformed requests."; }
		else if (static_cast<std::string>(response_text) == "449") { std::cout << "Retry With\n\nDescription: A Microsoft extension. The request should be retried after performing the appropriate action. Often search-engines or custom applications will ignore required parameters. Where no default action is appropriate, the Aviongoo website sends a \"HTTP / 1.1 Retry with valid parameters : param1, param2, . . .\" response. The applications may choose to learn, or not."; }
		else if (static_cast<std::string>(response_text) == "450") { std::cout << "Blocked by Windows Parental Controls\n\nDescription: A Microsoft extension. This error is given when Windows Parental Controls are turned on and are blocking access to the given webpage"; }
		else if (static_cast<std::string>(response_text) == "451") { std::cout << "Unavailable For Legal Reasons\n\nDescription: The server is denying access to the resource as a consequence of a legal demand."; }
		else if (static_cast<std::string>(response_text) == "494") { std::cout << "Request Header Too Large\n\nDescription: Nginx internal code similar to 431 but it was introduced earlier."; }
		else if (static_cast<std::string>(response_text) == "495") { std::cout << "Cert Error\n\nDescription: Nginx internal code used when SSL client certificate error occurred to distinguish it from 4XX in a log and an error page redirection."; }
		else if (static_cast<std::string>(response_text) == "496") { std::cout << "No Cert\n\nDescription: Nginx internal code used when client didn't provide certificate to distinguish it from 4XX in a log and an error page redirection."; }
		else if (static_cast<std::string>(response_text) == "497") { std::cout << "HTTP to HTTPS\n\nDescription: Nginx internal code used for the plain HTTP requests that are sent to HTTPS port to distinguish it from 4XX in a log and an error page redirection."; }
		else if (static_cast<std::string>(response_text) == "498") { std::cout << "Token Expired / Invalid\n\nDescription: Returned by ArcGIS for Server. A code of 498 indicates an expired or otherwise invalid token."; }
		else if (static_cast<std::string>(response_text) == "499") { std::cout << "Client Closed Request (Nginx)/Token required (Esri)\n\nDescription 1: Used in Nginx logs to indicate when the connection has been closed by client while the server is still processing its request, making server unable to send a status code back.\n\nDescription 2: Returned by ArcGIS for Server. A code of 499 indicates that a token is required (if no token was submitted)."; }
		// 500s
		else if (static_cast<std::string>(response_text) == "500") { std::cout << "Internal Server Error\n\nDescription: The server encountered an unexpected condition that prevented it from fulfilling the request."; }
		else if (static_cast<std::string>(response_text) == "501") { std::cout << "Not Implemented\n\nDescription: The server does not support the functionality required to fulfill the request."; }
		else if (static_cast<std::string>(response_text) == "502") { std::cout << "Bad Gateway\n\nDescription: The server, while acting as a gateway or proxy, received an invalid response from an inbound server it accessed while attempting to fulfill the request."; }
		else if (static_cast<std::string>(response_text) == "503") { std::cout << "Service Unavailable\n\nDescription: The server is currently unable to handle the request due to a temporary overload or scheduled maintenance, which will likely be alleviated after some delay."; }
		else if (static_cast<std::string>(response_text) == "504") { std::cout << "Gateway Timeout\n\nDescription: The server, while acting as a gateway or proxy, did not receive a timely response from an upstream server it needed to access in order to complete the request."; }
		else if (static_cast<std::string>(response_text) == "505") { std::cout << "HTTP Version Not Supported\n\nDescription: The server does not support, or refuses to support, the major version of HTTP that was used in the request message."; }
		else if (static_cast<std::string>(response_text) == "506") { std::cout << "Variant Also Negotiates\n\nDescription: The server has an internal configuration error: the chosen variant resource is configured to engage in transparent content negotiation itself, and is therefore not a proper end point in the negotiation process."; }
		else if (static_cast<std::string>(response_text) == "507") { std::cout << "Insufficient Storage\n\nDescription: The method could not be performed on the resource because the server is unable to store the representation needed to successfully complete the request."; }
		else if (static_cast<std::string>(response_text) == "508") { std::cout << "Loop Detected\n\nDescription: The server terminated an operation because it encountered an infinite loop while processing a request with \"Depth: infinity\". This status indicates that the entire operation failed."; }
		else if (static_cast<std::string>(response_text) == "509") { std::cout << "Bandwidth Limit Exceeded (Apache)\n\nDescription: This status code is not specified in any RFCs. Its use is unknown."; }
		else if (static_cast<std::string>(response_text) == "510") { std::cout << "Not Extended\n\nDescription: The policy for accessing the resource has not been met in the request. The server should send back all the information necessary for the client to issue an extended request."; }
		else if (static_cast<std::string>(response_text) == "511") { std::cout << "Network Authentication Required\n\nDescription: The client needs to authenticate to gain network access."; }
		// CLOUDFLARE START
		else if (static_cast<std::string>(response_text) == "520") { std::cout << "Unknown Error (CloudFlare)\n\nDescription: A generic response when the origin server returns something unexpected"; }
		else if (static_cast<std::string>(response_text) == "521") { std::cout << "Web Server Is Down (CloudFlare)\n\nDescription: The origin server is refusing connections from CloudFlare"; }
		else if (static_cast<std::string>(response_text) == "522") { std::cout << "Connection Timed Out (CloudFlare)\n\nDescription: A TCP handshake cannot be negotiated with the origin server"; }
		else if (static_cast<std::string>(response_text) == "523") { std::cout << "Origin Is Unreachable (CloudFlare)\n\nDescription: CloudFlare can't reach the origin server (e.g. because of a DNS error)"; }
		else if (static_cast<std::string>(response_text) == "524") { std::cout << "A Timeout Occurred (CloudFlare)\n\nDescription: A TCP connection to the origin server was completed, but a response wasn't received in time"; }
		else if (static_cast<std::string>(response_text) == "525") { std::cout << "SSL Handshake Failed (CloudFlare)\n\nDescription: A SSL/TLS handshake couldn't be negotiated with the origin server"; }
		else if (static_cast<std::string>(response_text) == "526") { std::cout << "Invalid SSL Certificate (CloudFlare)\n\nDescription: The SSL/TSL certificate presented by the origin server couldn't be validated"; }
		// CLOUDFLARE END
		else if (static_cast<std::string>(response_text) == "598") { std::cout << "Network Read Timeout Error\n\nDescription: This status code is not specified in any RFCs, but is used by Microsoft HTTP proxies to signal a network read timeout behind the proxy to a client in front of the proxy."; }
		else if (static_cast<std::string>(response_text) == "599") { std::cout << "Network Connect Timeout Error\n\nDescription: This status code is not specified in any RFCs, but is used by Microsoft HTTP proxies to signal a network connect timeout behind the proxy to a client in front of the proxy."; }
		std::cout << "\n";
	}
	InternetCloseHandle(h_open);
	InternetCloseHandle(h_file);
	return atoi(response_text);
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}
