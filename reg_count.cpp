#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main()
{
	unordered_map<string, int> cnt;
	//string s = "this is a test. the test has a number of chars that are repeated. the number of occourances must be noticed later";
	string s="10.1.20.299";
	//regex pattern {R"(\w+)"};
	//regex  e{R"((\d{1,3})((.{1,3}){3}))"};
	regex  e{R"((\d{1,3}).(\d{1,3}).(\d{1,3}).(\d{1,3}))"};
	if(regex_match(s.begin(),s.end(),e)) 
	{
		cout<<s<<" matches  ";
		bool iscorrect = true;
		// now the check for validity.
		smatch v_smatch; 
		regex_match(s,v_smatch,e);
		for(auto i:v_smatch) {
				if(i > 255) iscorrect = false;
		}
		if(!iscorrect) cout<<" but is not correct\n";
		else cout<<" and is  correct\n";
	}
	else cout<<s<<" do-not match\n";
	
}
