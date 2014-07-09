#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main()
{
	unordered_map<string, int> cnt;
	string s = "this is a test. the test has a number of chars that are repeated. the number of occourances must be noticed later";
	regex pattern {R"(\w+)"};
	for (sregex_iterator i{s.begin(),s.end(), pattern}; i!=s.end(); ++i)
		cnt[(*i).str()]++;
	for(auto i: cnt) cout<<i.first<<","<<i.second<<endl;
}
