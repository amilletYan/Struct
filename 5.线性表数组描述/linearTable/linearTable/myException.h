#include <string>
#include <iostream>
using namespace std;
class illegalParameterValue
{
public:
	illegalParameterValue(string s = "value error")
	{
		message = s;
	}
	void output(){ cout << message << endl; }
private:
	string message;
};