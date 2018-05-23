#include <duman.h> 

int main(int argc, char* argv[])
{
	string base_url = "https://www.google.com/search?q=";

	auto query = GetCommandLine();

	const auto l = strlen(argv[0]);

	if (query == strstr(query, argv[0]))
	{
		query = query + l;
		while (*query && isspace(*query))
			++query;
	}

	base_url += query;
	replace_str(base_url, "\"", "\\\"");
	replace_str(base_url, "+", "%2B");
	base_url += "&btnI"; // feeling lucky button
	open_url(base_url.c_str());
}
