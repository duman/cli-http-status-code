#include "duman.h"

int main(int argc, char* argv[])
{
	string base_url = "https://www.google.com/search?q=";

	char *query = GetCommandLine();
	if (*query == '"') {
		++query;
		while (*query)
			if (*query++ == '"')
				break;
	}
	else {
		while (*query && *query != ' ' && *query != '\t')
			++query;
	}

	while (*query == ' ' || *query == '\t')
		query++;

	base_url += query;
	replace_str(base_url, " ", "%20");
	replace_str(base_url, "\"", "\\\"");
	replace_str(base_url, "+", "%2B");
	base_url += "&btnI"; // feeling lucky button
	open_url(base_url.c_str());
}
