#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define nl(x) for(int i = 0; i < x; i++) printf("\n");
#define BUFFER_SIZE 5

using namespace std;

int main() {
	vector<vector<int>>run; // run
	vector<int>memory;
	vector<int>fileContent;
	int r; // Test Case
	int amount;
	int tmp;
	FILE* input = NULL;
	FILE* output = NULL;
	input = fopen("replacement_input.txt", "r"); // input file open with "read"
	output = fopen("replacement_output.txt", "w"); // output file open with "write"
	if (input == NULL) { // open fail
		printf("FILE(input.txt) Reading Fail.\n");
		return 1;
	}
	if (output == NULL) { // open fail
		printf("FILE(output.txt) Writting Fail.\n");
		return 1;
	}
	printf("FILE Reading and Writting are ready.\n");
	fscanf(input, "%d", &r); // input testCase
	printf("---------------------------------------\n");
	printf("testCase: %d\n", r); // check testCase
	printf("---------------------------------------\n");
	for (int testCase = 0; testCase < r; testCase++) {
		fscanf(input, "%d", &amount); // input amount
		printf("amount: %d\n", amount); // check amount
		int minValue; // minimum value
		int minIndex = 0; // index of minimum value
		bool isFreeze[BUFFER_SIZE] = { false, false, false, false, false }; // 동결된 버퍼 T/F
		int freezeCount = 0;
		int inputCount = 0; // 더 읽어올 데이터가 있는지 찾기 위한 count
		int tmpCount = 0;
		int readCount = 0;
		// 이후 Replacement Selection
		int i = 0;
		for (int j = 0; j < BUFFER_SIZE; j++) {
			fscanf(input, "%d", &tmp); readCount++;
			memory.push_back(tmp);
			printf("Value(%d): %d\n", j, memory.at(j));
		}
		while (1) {
			bool flag = true; // 동결되지 않은 가장 첫 Value, Index를 minValue, minIndex로 설정하기 위함
			// Buffer 5 안의 가장 작은 값 찾기
			for (int j = 0; j < BUFFER_SIZE; j++) { // find minimum in memory(buffer)
				printf("Find the smallest value\n");
				if (isFreeze[j] || memory.at(j) == -1) { // 동결되어 있거나 빈 데이터(-1)를 가지고 있다면 건너뜀
					printf("Index %d (value: %d) is skipped. ", j, memory.at(j));
					if (isFreeze[j]) printf("(reason: Freeze)\n");
					else printf("(reason: empty)\n");
					continue;
				}
				if (flag) { // min에 동결되어 있거나 빈 데이터(-1)가 아닌 가장 첫 값 대입
					flag = false;
					minValue = memory.at(j);
					minIndex = j;
				}
				if (memory.at(j) < minValue) {
					minValue = memory.at(j);
					minIndex = j;
				}
				printf("minValue: %d (Index: %d)\n", minValue, minIndex);
			}
			// 정상적으로 들어갈 수 있다면
			if (i == 0 || (fileContent.back() <= minValue)) {
				fileContent.push_back(minValue);
				printf("- Delete: %d(%d)\n", memory.at(minIndex), minIndex);
				memory.erase(memory.begin() + minIndex);
				inputCount++;
				if (readCount == amount) { // 더 읽어올 데이터가 없다면
					tmpCount++;
					memory.insert(memory.begin() + minIndex, -1);
				}
				else { // 더 읽어올 데이터가 있다면
					fscanf(input, "%d", &tmp); readCount++;
					memory.insert(memory.begin() + minIndex, tmp);
					printf("+ Insert: %d(%d)\n", memory.at(minIndex), minIndex);
					printf("(readCount: %d)\n", readCount);
				}
			}
			// 동결
			else {
				isFreeze[minIndex] = true;
				printf("[%d Index is frozen]\n", minIndex);
				freezeCount++;
				printf("[freezeCount: %d]\n", freezeCount);
			}
			i++;
			// 모두 동결된 상태라면
			if (freezeCount + tmpCount == 5) {
				printf("[RUN %d ADDED]\n", run.size());
				run.push_back(fileContent);
				for (int cnt = 0; cnt < fileContent.size(); cnt++) {
					printf("%d ", fileContent.at(cnt));
				}
				printf("\n");
				fileContent.clear(); // 저장된 fileContent의 모든 요소 삭제
				freezeCount = 0;
				i = 0;
				for (int cnt = 0; cnt < 5; cnt++) isFreeze[cnt] = false; // isFreeze 전부 false로 초기화
			}
			if (inputCount == amount) {
				printf("[CASE %d COMPLETED]\n", testCase + 1);
				break;
			}
		}
		// Text File에 출력하기
		fprintf(output, "%d\n", run.size());
		printf("%d\n", run.size());
		for (int i = 0; i < run.size(); i++) {
			for (int j = 0; j < run.at(i).size(); j++) {
				fprintf(output, "%d ", run.at(i).at(j));
				printf("%d ", run.at(i).at(j));
			}
			fprintf(output, "\n");
			printf("\n");
		}
		// 모든 vector 초기화
		run.clear();
		fileContent.clear();
		memory.clear();
		printf("---------------------------------------\n");
	}
	fclose(input);
	fclose(output);
	system("pause");
	return 0;
}