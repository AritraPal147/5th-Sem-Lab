/*
Define a struct person as follows: 
struct person
{
	int id;
	char *name;
	int age;
	int height;
	int weight;
}; 
Write a menu driven program to read the data of ‘n’ students from a file and 
store them in a dynamically allocated array of struct person. Implement the 
min-heap or max-heap and its operations based on the menu options. 

Sample Input/Output:
MAIN MENU (HEAP)
1. Read Data
2. Create a Min-heap based on the age
3. Create a Max-heap based on the weight
4. Display weight of the youngest person
5. Insert a new person into the Min-heap
6. Delete the oldest person
7. Exit

Enter option: 1 
Id	Name		Age	Height	Weight
0	Adarsh Hota	39	77	231
1	Levi Maier	56	77	129
2	Priya Kumari	63	78	240
3	Dorothy Helton	47	72	229
4	Florence Smith	24	75	171
5	Erica Anyan	38	73	102
6	Norma Webster	23	75	145

Enter option: 4
Weight of youngest student: 65.77 kg

Note#: Other menu choices are similarly verified.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
	int id;
	char name[20];
	int age;
	int height;
	int weight;
};

void swap(struct person *a, struct person *b) {
	struct person temp = *a;
	*a = *b;
	*b = temp;
}

void minHeapify(struct person *arr, int n, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if (left < n && arr[left].age < arr[smallest].age) 
		smallest = left;
	if (right < n && arr[right].age < arr[smallest].age)
		smallest = right;
	if (smallest != i) {
		swap(&arr[smallest], &arr[i]);
		minHeapify(arr, n, smallest);
	}
}

void buildMinHeap(struct person *arr, int n) {
	for (int i=n/2-1; i>=0; i--)
		minHeapify(arr, n, i);
}

void maxHeapify(struct person *arr, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if (left < n && arr[left].weight > arr[largest].weight)
		largest = left;
	if (right < n && arr[right].weight > arr[largest].weight)
		largest = right;
	if (largest != i) {
		swap(&arr[largest], &arr[i]);
		maxHeapify(arr, n, largest);
	}	
}

void buildMaxHeap(struct person *arr, int n) {
	for (int i=n/2-1; i>=0; i--)
		maxHeapify(arr, n, i);
}

struct person *insertPerson(struct person *arr, int *n) {
	struct person newPerson;
	
	printf("Enter ID: ");
	scanf("%d", &newPerson.id);
	printf("Enter Name: ");
	scanf("%[^,]", newPerson.name);
	printf("Enter Age: ");
	scanf("%d", &newPerson.age);
	printf("Enter Height: ");
	scanf("%d", &newPerson.height);
	printf("Enter Weight: ");
	scanf("%d", &newPerson.weight);
	
	(*n)++;
	buildMinHeap(arr, *n);
	arr = (struct person*) realloc(arr, (*n) * sizeof(struct person));
	arr[*n - 1] = newPerson;
	buildMinHeap(arr, *n);
	
	return arr;
}

struct person *deleteOldestPerson(struct person *arr, int *n) {
	if (*n > 0) {
		buildMinHeap(arr, *n);
		swap(&arr[0], &arr[*n - 1]);
		(*n)--;
		arr = (struct person*) realloc(arr, (*n) * sizeof(struct person));
		buildMinHeap(arr, *n);
	} else
		printf("No data available to delete\n");
	
	return arr;
}

void displayYoungestWeight(struct person *arr, int n) {
	if (n > 0) {
		buildMinHeap(arr, n);
		printf("Weight of the youngest person: %d\n", arr[0].weight);	
	} else
		printf("No data available\n");
}

struct person *readData(struct person *arr, int *n) {
	if (arr != NULL) {
		free(arr);
		*n = 0;
	}
	char *fileName = "input.dat";
	
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Error opening input file.\n");
		exit(1);
	}
	
	printf("Enter number of elements to be read from file: ");
	scanf("%d", n);
	
	arr = (struct person*) realloc(arr, (*n) * sizeof(struct person));
	
	int countEle = 0;
	while (countEle != *n) {
		fscanf(file, "%d,%[^,],%d,%d,%d", &arr[countEle].id, arr[countEle].name, &arr[countEle].age, &arr[countEle].height, &arr[countEle].weight);
		countEle++;
	}
	
	fclose(file);
	printf("Data read from file\n");
	return arr;
}

void display(struct person* arr, int n) {
	printf("Id\tName\t\t\tAge\tHeight\tWeight\n");
	for(int i=0; i<n; i++) 
		printf("%d\t%s\t\t%d\t%d\t%d\n", arr[i].id, arr[i].name, arr[i].age, arr[i].height, arr[i].weight);
	printf("\n");
}

int main() {
	int choice, n = 0;
	struct person *arr = NULL;
	
	do {
		printf("MAIN MENU (HEAP)\n");
		printf("1. Read Data\n");
		printf("2. Create a Min-Heap based on the age\n");
		printf("3. Create a Max-Heap based on the weight\n");
		printf("4. Display weight of the youngest person\n");
		printf("5. Insert a new person into the Min-Heap\n");
		printf("6. Delete the oldest person\n");
		printf("7. Exit\n");
		
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1:
				arr = readData(arr, &n);
				display(arr, n);
				break;
			case 2:
				if (n > 0) {
					buildMinHeap(arr, n);
					printf("Min Heap Created\n\n");
					display(arr, n);
				} else
					printf("No data available\n");
				break;
			case 3:
				if (n > 0) {
					buildMaxHeap(arr, n);
					printf("Max Heap Created\n\n");
					display(arr, n);
				} else
					printf("No data available\n");
			case 4:
				displayYoungestWeight(arr, n);
				break;
			case 5:
				arr = insertPerson(arr, &n);
				printf("New Person Inserted into the Min-Heap\n");
				display(arr, n);
				break;
			case 6:
				arr = deleteOldestPerson(arr, &n);
				printf("Oldest Person Deleted From Min-Heap\n");
				display(arr, n);
			case 7:
				break;
			default:
				printf("Invalid option selected");
		}
	} while(choice != 7);
}
