/////////////////////////////////////
// Michael Iuso					   //
// Disk scheduling simulator       //
/////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

void fcfs(int blocks[], int arraysize, int current); // first come first serve
void sstf(int blocks[], int arraysize, int current); // shortest seek time first
void scan(int blocks[], int arraysize, int current); // scan
void cscan(int blocks[], int arraysize, int current); // circular scan
void swap(int i, int j, int blocks[]); // used for sorting
void quickSort(int blocks[], int left, int right); // sorting algorithm
int movement(int x, int y); // head movement

int main() {
	int blocks[] = { 10, 30, 25, 55, 100, 5, 20, 150, 65 }; // values from homework problem #3
	int arraysize = 9;
	int current = 51;

	fcfs(blocks, arraysize, current);
	sstf(blocks, arraysize, current);
	scan(blocks, arraysize, current);
	cscan(blocks, arraysize, current);

	return 0;
}

void fcfs(int blocks[], int arraysize, int current) {
	cout << "fcfs: ";
	int head = current;
	int distance = 0;

	cout << head << " ";
	for (int i = 0; i < arraysize; i++) {
		distance += abs(movement(head, blocks[i]));
		head = blocks[i];
		cout << head << " ";
	}

	cout << endl;
	cout << "Head movement: " << distance << endl;
	cout << endl;
}

void sstf(int blocks[], int arraysize, int current) {
	cout << "sstf: ";
	int head = current, temp = arraysize, distance = 0, min = abs(movement(head, blocks[0])), i = 0, j = 0;
	int *minSearch; // to find the min value 
	int minInd = 0; // index of min
	minSearch = new int[arraysize]; // new array to find min

									// initialize all elements of minSearch to 0 (none are defined as the min yet)

	for (i = 0; i < arraysize; i++)
		minSearch[i] = 0;

	cout << head << " ";

	// while loop must continue for as many times as size of the array

	while (temp) {
		for (i = 0; i < arraysize; i++) {
			if (minSearch[i] == 0 && abs((movement(head, blocks[i])) < min)) {
				min = abs(movement(head, blocks[i]));
				minInd = i;
			}
		}

		// a min has been found

		minSearch[minInd] = 1;
		distance += abs(movement(head, blocks[minInd]));

		// update the head

		head = blocks[minInd];
		cout << head << " ";

		// update min 

		j = 0;
		while (head == blocks[minInd] && j < arraysize) {
			if (minSearch[j] == 0) {
				minInd = j;
				min = abs(movement(head, blocks[j]));
				break;
			}
			j++;
		}
		temp--;
	}

	cout << endl;
	cout << "Head movement: " << distance << endl;
	cout << endl;
}

void scan(int blocks[], int arraysize, int current) {
	cout << "scan: ";
	int head = current, distance = 0, *temp, n = 0, i = 0;
	int headInd; // index of head

	temp = new int[arraysize + 2]; // new array to account for extra value (0)
	temp[0] = 0;
	temp[1] = head;

	for (i = 2; i < arraysize + 2; i++) {
		temp[i] = blocks[n];
		n++;
	}

	quickSort(temp, 0, arraysize + 1);

	for (i = 0; i < arraysize + 2; i++) {
		if (temp[i] == head)
			headInd = i;
	}

	cout << head << " ";

	// values left of head

	for (i = headInd - 1; i >= 0; i--) {
		cout << temp[i] << " ";
		distance += abs(movement(head, temp[i]));
		head = temp[i];
	}

	// value right of head

	for (i = headInd + 1; i < arraysize + 2; i++) {
		distance += abs(movement(head, temp[i]));
		cout << temp[i] << " ";
		head = temp[i];
	}

	cout << endl;
	cout << "Head movement: " << distance << endl;
	cout << endl;
}

void cscan(int blocks[], int arraysize, int current) {
	cout << "c-scan: ";
	int head = current, distance = 0, *temp, n = 0, i = 0;
	int headInd;

	temp = new int[arraysize + 3]; // new array to account for extra values (0 and 200)
	temp[0] = 0;
	temp[1] = head;
	temp[2] = 200;

	for (i = 3; i < arraysize + 3; i++) {
		temp[i] = blocks[n];
		n++;
	}

	quickSort(temp, 0, arraysize + 2);

	for (i = 0; i < arraysize + 3; i++) {
		if (temp[i] == head)
			headInd = i;
	}

	cout << head << " ";

	// values left of head

	for (i = 0; i < headInd; i++) {
		cout << temp[i] << " ";
		distance += abs(movement(head, temp[i]));
		head = temp[i];
		if (head == 0)
		{

		}
	}

	// values right of head

	for (i = headInd + 1; i < arraysize + 3; i++) {
		distance += abs(movement(head, temp[i]));
		cout << temp[i] << " ";
		head = temp[i];
	}

	cout << endl;
	cout << "Head movement: " << distance << endl;
	cout << endl;
}

void swap(int i, int j, int *a) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void quickSort(int blocks[], int left, int right) {
	int i = left, j = right, tmp, min = (left + right) / 2, pivot = blocks[min];

	while (i <= j) {
		while (blocks[i] < pivot)
			i++;
		while (blocks[j] > pivot)
			j--;
		if (i <= j) {
			swap(i, j, blocks);
			i++;
			j--;
		}
	};

	if (left < j)
		quickSort(blocks, left, j);
	if (i < right)
		quickSort(blocks, i, right);
}

int movement(int x, int y) {
	return x - y;
}
