#include <iostream>

using namespace std;

int main(){
	int f;
	cin >> f;
	const int total_time = 4 * 60;
	const int time_per_task = 45;
	const int task_count = 12;
	if ((task_count-f) * time_per_task <= total_time )
		cout << "YES";
	else 
		cout << "NO";
	return 0;
}