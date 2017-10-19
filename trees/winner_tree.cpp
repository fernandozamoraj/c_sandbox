#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>

using namespace std;

template<class T>
class LoserTree{

private:
	T* tree;
	int length;
	const int INFINITY_LT = INT_MAX;

public:
	LoserTree(const T* initialArray, int len){
		tree = NULL;
		createTree(initialArray, len);
	}

	void removeByValue(int value){

		int idx = -1;

		for (int i = 0; i<length; i++){
			if (tree[i] == value){
				idx = i;
				break;
			}
		}

		if (idx > -1){
			removeItem(idx);
		}
	}

	void removeItem(int idx){

		
		if (idx >-1 && idx < length){
			int offset = 0;

			cout << "Removing: " << tree[idx] << endl;

			for (int i = 0; i<length; i++){
				if (i == idx){
					tree[i] = INFINITY_LT;
				}
			}
		}
	}

	void createTree(const int* initialArray, int len){

		if (len < 1)
			return;

		tree = new T[len];
		this->length = len;

		for (int i = 0; i<len; i++){
			tree[i] = initialArray[i];
		}
	}


	int getWinner(){
		int tempLength = this->length;
		T* tempArray = this->tree;
		T* newArray = NULL;
		
		displayArray(tempArray, tempLength);
		
		do{

			if (tempArray != NULL && tempArray != tree){
				delete [] tempArray;
			}
			

			if (newArray != NULL){
				tempArray = newArray;
			}

			newArray = new int[tempLength / 2];
			int k = 0;
			for (int j = 0; j<tempLength; j += 2){

				if (tempArray[j] < tempArray[j + 1]){
					newArray[k] = tempArray[j];
				}
				else{
					newArray[k] = tempArray[j + 1];
				}
				k++;
			}

			displayArray(newArray, tempLength/2);

			tempLength = tempLength / 2;
		} while (tempLength > 1);
		
		int result = newArray[0];
		
		delete [] newArray;

		return result;
	}

	T* getSorted(){

		int length = this->length;
		int* temp = new int[length];
		for (int i = 0; i<length; i++){
			T winner = getWinner();
			cout << "Winner is " << winner << endl;
			removeByValue(winner);
			temp[i] = winner;
		}

		return temp;
	}

	void displayArray(const int* arr, int len){

		cout << endl;
		cout << "[ ";
		for (int i = 0; i<len; i++){
			if (arr[i] == INFINITY_LT){
				cout << "_, ";
				continue;
			}

			cout << arr[i] << ", ";
		}
		cout << "]" << endl;
	}

};

int main(int argc, char* argv[])
{
	int newArr[] = { 3, 1, 2, 5, 6, 85, 75, 10 };
	LoserTree<int> lTree(newArr, 8);
	int *sorted = lTree.getSorted();
	lTree.displayArray(sorted, 8);
	delete [] sorted;

	char ch;
	cin >> ch;
	

	return 0;
}