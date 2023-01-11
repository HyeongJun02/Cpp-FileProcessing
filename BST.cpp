#pragma warning (disable:4996)

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

/*
0. testCase
1. 삽입할 키의 개수 i
2. 삽입할 i개의 키 (값은 1 이상의 정수, 중복 X)
3. 검색할 키의 개수 s1
4. 검색할 s1개의 키 (존재하는 키만)
5. 삭제할 키의 개수 d
6. 삭제할 d개의 키
7. 검색할 키의 개수 s2
8. 검색할 s2개의 키
*/

string result = "";
vector<int>address; // 값의 주소값
vector<vector<int>>value; // 주소값을 가진 vector 생성

void BSTInsert(int tmp);
void BSTSearch(int tmp);
void BSTDelete(int tmp);
int BSTFindLastIndex(int tmp);
int BSTFindFirstIndex(int tmp);

int BSTFindAddressIndex;

// Insert
void BSTInsert(int tmp) {
	printf("=====BSTInsert START=====\n");
	printf("find the %d\n", tmp);
	int findIndex = 0;
	while (true) {
		printf("findIndex: %d\n", findIndex);
		if (tmp < value.at(findIndex).at(0)) {
			if (value.at(findIndex).at(1) == -1) {
				value.at(findIndex).at(1) = tmp;
				address.push_back(tmp);
				address.push_back(-1);
				address.push_back(-1);
				value.push_back(address);
				address.clear();
				break;
			}
			else {
				findIndex = BSTFindFirstIndex(value.at(findIndex).at(1));
			}
		}
		else if (tmp > value.at(findIndex).at(0)) {
			if (value.at(findIndex).at(2) == -1) {
				value.at(findIndex).at(2) = tmp;
				address.push_back(tmp);
				address.push_back(-1);
				address.push_back(-1);
				value.push_back(address);
				address.clear();
				break;
			}
			else {
				findIndex = BSTFindFirstIndex(value.at(findIndex).at(2));
			}
		}
	}
	printf("=====BSTInsert END=====\n");
}
// Search (= write result)
void BSTSearch(int tmp) {
	printf("=====BSTSearch START=====\n");
	int findIndex = 0;
	while (true) {
		printf("findIndex: %d\n", findIndex);
		printf("tmp: %d\nvalue.at(findIndex).at(0): %d\n", tmp, value.at(findIndex).at(0));
		if (tmp == value.at(findIndex).at(0)) {
			break;
		}
		else if (tmp < value.at(findIndex).at(0)) {
			result += "0";
			printf("Recent Result: %s\n", result.c_str());
			findIndex = BSTFindFirstIndex(value.at(findIndex).at(1));
		}
		else if (tmp > value.at(findIndex).at(0)) {
			result += "1";
			printf("Recent Result: %s\n", result.c_str());
			findIndex = BSTFindFirstIndex(value.at(findIndex).at(2));
		}
	}
	printf("=====BSTSearch END=====\n");
}
// Delete
void BSTDelete(int tmp) {
	printf("=====BSTDelete START=====\n");
	int index;
	int rootFlag = false; // root인 경우 예외처리
	if (tmp == value.at(0).at(0)) rootFlag = true;
	index = BSTFindFirstIndex(tmp);
	if (rootFlag) { // root 제거인 경우
		// 자식이 없을 경우
		if ((value.at(0).at(1) == -1) && (value.at(0).at(2) == -1)) {
			printf("[root] 자식이 없습니다.\n");
			printf("Change [root] to [NULL]\n");
			value.erase(value.begin() + 0);
			//value.at(0).clear();
		}
		// 자식이 1개 존재할 경우
		else if ((value.at(0).at(1) == -1) || (value.at(0).at(2) == -1)) {
			printf("[root] 자식이 1개 있습니다.\n");
			printf("Change [root] to [NULL]\n");
			value.erase(value.begin() + 0);
			//value.at(0).clear();
		}
		// 자식이 2개 존재할 경우
		else {
			printf("[root] 자식이 2개 있습니다.\n");
			//int lastIndex = BSTFindLastIndex(tmp);
			// root의 idx1, idx2 저장
			int deleteNodeIdx1 = value.at(index).at(1);
			int deleteNodeIdx2 = value.at(index).at(2);

			int rightChildMin = value.at(index).at(2);
			int saveChild;
			while (true) {
				printf("rightChildMin: %d\n", rightChildMin);
				int rightChildIndex = BSTFindFirstIndex(rightChildMin);
				int saveParentIndex = BSTFindLastIndex(rightChildMin);
				if (value.at(rightChildIndex).at(1) == -1) { // 자식 node에 왼쪽 자식이 X
					if (value.at(rightChildIndex).at(2) != -1) { // 오른쪽 자식이 O
						//int replaceNodeParentIndex = BSTFindFirstIndex(rightChildMin); // 대체할 node의 부모
						// 대체할 node의 부모 중 대체 node 쪽 값 변경
						int tmpRightChildRight = value.at(rightChildIndex).at(2);
						value.at(saveParentIndex).at(1) = tmpRightChildRight;
						value.at(rightChildIndex).at(1) = deleteNodeIdx1;
						value.at(rightChildIndex).at(2) = deleteNodeIdx2;
						//int tmpRightChildParent = BSTFindFirstIndex(tmpRightChildRight);
						//value.at(tmpRightChildParent).at(BSTFindAddressIndex) = tmpRightChildRight;
					}
					else { // 오른쪽 자식이 X
						value.at(rightChildIndex).at(1) = deleteNodeIdx1;
						value.at(rightChildIndex).at(2) = deleteNodeIdx2;
					}
					break;
				}
				else {
					rightChildMin = value.at(rightChildIndex).at(1);
				}
			}

			// 삭제할 node 삭제
			value.erase(value.begin() + index);
		}
	}
	else { // root 제거가 아닌 경우
		//value.at(index).at(BSTFindAddressIndex) = -1; // 임시 변경
		//printf("임시 변경 Complete\n");
		index = BSTFindLastIndex(tmp);
		// 현재 index는 부모 node의 주소값

		int saveIndex1 = index; // 부모 node의 주소값
		int saveIndex2 = BSTFindAddressIndex; // 부모 node의 삭제하려는 node index값
		printf("saveIndex1, saveIndex2 Complete\n");

		index = BSTFindFirstIndex(tmp);
		// 현재 index는 삭제하려는 node의 주소값

		int idx1 = value.at(index).at(1); // 삭제하려는 값의 왼쪽 자식값
		int idx2 = value.at(index).at(2); // 삭제하려는 값의 오른쪽 자식값

		printf("index: %d\n", index);
		// 자식이 없을 경우
		if ((value.at(index).at(1) == -1) && (value.at(index).at(2) == -1)) {
			printf("자식이 없습니다.\n");
			printf("Change [%2d] to [NULL]\n", value.at(index).at(0));
			value.at(saveIndex1).at(saveIndex2) = -1;
			value.erase(value.begin() + index);
			//value.at(index).clear();
		}
		// 자식이 1개 존재할 경우
		else if ((value.at(index).at(1) == -1) || (value.at(index).at(2) == -1)) {
			printf("자식이 1개 있습니다.\n");
			int child = (value.at(index).at(1) != -1) ? value.at(index).at(1) : value.at(index).at(2);
			printf("Change [%2d] to [%2d]\n", value.at(saveIndex1).at(saveIndex2), child);
			value.at(saveIndex1).at(saveIndex2) = child;
			value.erase(value.begin() + index);
			//value.at(index).clear();
		}
		// 자식이 2개 존재할 경우
		else {
			printf("자식이 2개 있습니다.\n");
			int lastIndex = BSTFindFirstIndex(tmp);
			// 삭제할 node의 idx1, idx2 저장
			int deleteNodeIdx1 = value.at(lastIndex).at(1);
			int deleteNodeIdx2 = value.at(lastIndex).at(2);

			int rightChildMin = value.at(index).at(2);
			int saveChild;
			while (true) {
				int rightChildIndex = BSTFindFirstIndex(rightChildMin);
				int saveParentIndex = BSTFindLastIndex(rightChildMin);
				if (value.at(rightChildIndex).at(1) == -1) { // 최소값 찾음 (자식 node가 왼쪽 자식이 X)
					if (rightChildMin == value.at(index).at(2)) { // 대체 node가 삭제 node의 바로 아래 자식일 경우
						//value.at(rightChildIndex).at(1) = idx1;
						//value.at(rightChildIndex).at(2) = -1;
						value.at(saveIndex1).at(saveIndex2) = rightChildMin;
						value.at(saveParentIndex).at(BSTFindAddressIndex) = -1;
						value.at(rightChildIndex).at(1) = deleteNodeIdx1;
						//value.at(rightChildIndex).at(2) = idx2;
						break;
					}
					// 대체할 node의 idx1, idx2 변경
					if (value.at(rightChildIndex).at(2) != -1) { // 오른쪽 자식이 O
						//int replaceNodeParentIndex = BSTFindFirstIndex(rightChildMin); // 대체할 node의 부모
						// 대체할 node의 부모 중 대체 node 쪽 값 변경
						int tmpRightChildRight = value.at(rightChildIndex).at(2);
						value.at(saveParentIndex).at(BSTFindAddressIndex) = tmpRightChildRight;

						//int tmpRightChildParent = BSTFindFirstIndex(tmpRightChildRight);
						//value.at(tmpRightChildParent).at(BSTFindAddressIndex) = tmpRightChildRight;
					}
					else { // 오른쪽 자식이 X
						value.at(saveParentIndex).at(BSTFindAddressIndex) = -1;
					}
					saveChild = rightChildMin;
					value.at(rightChildIndex).at(1) = deleteNodeIdx1;
					value.at(rightChildIndex).at(2) = deleteNodeIdx2;
					break;
				}
				else {
					rightChildMin = value.at(rightChildIndex).at(1);
				}
			}

			// 삭제할 node 삭제
			value.erase(value.begin() + index);
		}
	}
	printf("<Now>\n");
	for (int a = 0; a < value.size(); a++) {
		for (int b = 0; b < 3; b++) {
			printf("[%2d] ", value.at(a).at(b));
		}
		printf("\n");
	}
	printf("=====BSTDelete END=====\n");
}
// FindLastIndex
int BSTFindLastIndex(int tmp) {
	printf("=====BSTFindLastIndex START=====\n");
	int index = -1;
	bool stopFlag = false;
	for (int idx = 0; idx < value.size(); idx++) {
		for (int findValue = 1; findValue < 3; findValue++) {
			if (tmp == value.at(idx).at(findValue)) {
				index = idx;
				BSTFindAddressIndex = findValue;
				printf("Index is Founded: %d, %d\n", index, BSTFindAddressIndex);
				stopFlag = true;
				break;
			}
		}
		printf("stopFlag: %d\n", stopFlag);
		if (stopFlag) break;
	}
	printf("=====BSTFindLastIndex END=====\n");
	return index;
}
// FindFirstIndex
int BSTFindFirstIndex(int tmp) {
	printf("=====BSTFindFirstIndex START=====\n");
	int index = -1;
	bool stopFlag = false;
	for (int idx = 0; idx < value.size(); idx++) {
		printf("value.at(idx).at(0): %d\n", value.at(idx).at(0));
		if (tmp == value.at(idx).at(0)) {
			index = idx;
			BSTFindAddressIndex = 0;
			printf("Index is Founded: %d, %d\n", index, BSTFindAddressIndex);
			break;
		}
	}
	printf("=====BSTFindFirstIndex END=====\n");
 	return index;
}
// Main
int main() {
	int readCnt = 0; // read가 몇 번 이루어졌는지 확인
	FILE* input = NULL;
	FILE* output = NULL;
	input = fopen("bst_input.txt", "r"); // input file open with "read"
	output = fopen("bst_output.txt", "w"); // output file open with "write"
	if (input == NULL) { // open fail
		printf("FILE(input.txt) Reading: Fail.\n");
		system("pause");
		return 1;
	}
	if (output == NULL) { // open fail
		printf("FILE(output.txt) Writting: Fail.\n");
		system("pause");
		return 1;
	}
	printf("FILE Reading and Writting: Success\n");
	int testCase;
	fscanf(input, "%d", &testCase); // input testCase
	readCnt++;
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, testCase);
	printf("====================START====================\n");
	printf("testCase: %d\n", testCase); // check testCase
	printf("====================START====================\n");
	for (int testCaseCnt = 0; testCaseCnt < testCase; testCaseCnt++) {
		int i, s1, d, s2; // 삽입, 검색, 삭제, 검색

		// Insert
		fscanf(input, "%d", &i); // input insertCnt
		readCnt++;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, i);
		printf("insertCnt: %d\n", i); // check insertCnt
		for (int insertCnt = 0; insertCnt < i; insertCnt++) {
			int tmp;
			fscanf(input, "%d", &tmp); // input tmp
			readCnt++;
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, tmp);
			if (insertCnt == 0) {
				address.push_back(tmp);
				address.push_back(-1);
				address.push_back(-1);
				value.push_back(address);
				address.clear();
				printf("ROOT COMPLETE\n");
				continue;
			}
			printf("[%2d]START: BSTInsert(%d)\n", insertCnt, tmp);
			BSTInsert(tmp);
			printf("DONE\n");
		}
		for (int insertCnt = 0; insertCnt < i; insertCnt++) { // Check
			printf("[%d, %d, %d]\n", value.at(insertCnt).at(0), value.at(insertCnt).at(1), value.at(insertCnt).at(2));
		}

		printf("<Now>\n");
		for (int a = 0; a < value.size(); a++) {
			for (int b = 0; b < 3; b++) {
				printf("[%2d] ", value.at(a).at(b));
			}
			printf("\n");
		}

		printf("testCaseCnt: %d\n", testCaseCnt);
		printf("==Insert==\n");
		system("pause");

		// Search
		fscanf(input, "%d", &s1); // input insertCnt
		readCnt++;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, s1);
		printf("searchCnt: %d\n", s1); // check insertCnt
		for (int searchCnt = 0; searchCnt < s1; searchCnt++) {
			int tmp;
			fscanf(input, "%d", &tmp); // input tmp
			readCnt++;
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, tmp);
			result += "R"; // ROOT에서 출발
			BSTSearch(tmp);
			printf("\n>> %2d번째 - [%2d]의 결과: %s <<\n\n", searchCnt, tmp, result.c_str());
			fprintf(output, "%s\n", result.c_str());
			result = ""; // result 초기화
		}

		printf("<Now>\n");
		for (int a = 0; a < value.size(); a++) {
			for (int b = 0; b < 3; b++) {
				printf("[%2d] ", value.at(a).at(b));
			}
			printf("\n");
		}

		printf("testCaseCnt: %d\n", testCaseCnt);
		printf("==Search==\n");
		system("pause");

		// Delete
		fscanf(input, "%d", &d); // input deleteCnt
		readCnt++;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, d);
		printf("deleteCnt: %d\n", d); // check deleteCnt
		for (int deleteCnt = 0; deleteCnt < d; deleteCnt++) {
			int tmp;
			fscanf(input, "%d", &tmp); // input tmp
			readCnt++;
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, tmp);
			BSTDelete(tmp);
		}

		printf("<Now>\n");
		for (int a = 0; a < value.size(); a++) {
			for (int b = 0; b < 3; b++) {
				printf("[%2d] ", value.at(a).at(b));
			}
			printf("\n");
		}

		printf("testCaseCnt: %d\n", testCaseCnt);
		printf("==Delete==\n");
		system("pause");

		//Search
		fscanf(input, "%d", &s2); // input insertCnt
		readCnt++;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, s2);
		printf("searchCnt: %d\n", s2); // check insertCnt
		for (int searchCnt = 0; searchCnt < s2; searchCnt++) {
			int tmp;
			fscanf(input, "%d", &tmp); // input tmp
			readCnt++;
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> readCnt: %d, readValue: %d\n", readCnt, tmp);
			result += "R"; // ROOT에서 출발
			BSTSearch(tmp);
			printf("\n>> %2d번째 - [%2d]의 결과: %s <<\n\n", searchCnt, tmp, result.c_str());
			fprintf(output, "%s\n", result.c_str());
			result = ""; // result 초기화
		}

		printf("<Now>\n");
		for (int a = 0; a < value.size(); a++) {
			for (int b = 0; b < 3; b++) {
				printf("[%2d] ", value.at(a).at(b));
			}
			printf("\n");
		}

		printf("testCaseCnt: %d\n", testCaseCnt);
		printf("==Search==\n");
		system("pause");

		address.clear();
		value.clear();
	}

	fclose(input);
	fclose(output);
	system("pause");
	return 0;
}