#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 
#include <sstream> 
#include <Windows.h>

using namespace std;

struct Time {				// this structure will help us to not be confused in numbers.
	int start;
	int end;
};

int main()
{
	vector<Time> interval;						//The main array
	Time time;									//time and str are just auxiliary parameters
	string str;
	cout << "Please enter the intervals below. Press \"Enter\" again when finished:\n";
	getline(cin, str);
	while (str != "") {							//if we got an empry line, thet means we've reached the end
		istringstream ss(str);
		while (ss >> time.start) {				//read intervals
			ss >> time.end;
			interval.push_back(time);			//push to array
		}
		getline(cin, str);
	}
	for (unsigned int i = 0; i < interval.size() - 1; i++) {
		for (unsigned int j = i + 1; j < interval.size(); j++) {//compare current inteerval with the further ones
			if (!(interval[i].start > interval[j].end			//if intersect - merge
				|| interval[j].start > interval[i].end)) {
				interval[i].start = min(interval[i].start, interval[j].start);
				interval[i].end = max(interval[i].end, interval[j].end);
				interval.erase(interval.begin() + j);
				i--;											//As we erased interval[j], we have to decrease the index to account for removed element
				break;
			}
		}
	}

	for (unsigned int i = 0; i < interval.size() - 1; i++)			//sorting
		for (unsigned int j = 0; j < interval.size() - i - 1; j++)
			if (interval[j].start > interval[j + 1].start) {
				int x = interval[j].start;
				interval[j].start = interval[j + 1].start;
				interval[j + 1].start = x;
				x = interval[j].end;
				interval[j].end = interval[j + 1].end;
				interval[j + 1].end = x;
			}
	cout << "Here are the spaces:\n";
	for (unsigned int i = 0; i < interval.size() - 1; i++) {		//now we can list the spaces easily
		if (interval[i].end < interval[i + 1].start)
			cout << interval[i].end << " " << interval[i + 1].start << "\n";
	}
	interval.clear();
	system("pause");
}

