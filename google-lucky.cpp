#include <duman.h> 

void replace_url(string&, const string&, const string&);

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
	replace_url(base_url, "\"", "\\\"");
	replace_url(base_url, "+", "%2B");
	base_url += "&btnI"; // feeling lucky button
	open_url(base_url.c_str());
}

void replace_url(string& str, const string& from, const string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
