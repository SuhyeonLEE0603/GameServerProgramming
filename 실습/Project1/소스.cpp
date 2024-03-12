#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;

constexpr int CACHE_LINE_SIZE = 64;

int main()
{
	for (int i = 0; i < 20; ++i) {
		const int size = 1024 << i;
		char* a = (char*)malloc(size);
		unsigned int index = 0;
		int tmp = 0;
		auto start = high_resolution_clock::now();
		for (int j = 0; j < 100000000; ++j) {
			tmp += a[index % size];
			index += CACHE_LINE_SIZE * 11;
		}
		auto dur = high_resolution_clock::now() - start;
		cout << "Size : " << size / 1024 << "K, ";
		cout << "Time " << duration_cast<milliseconds>(dur).count();
		cout << " msec " << tmp << endl;
	}
}