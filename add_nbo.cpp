#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<string.h>
#include <stdint.h>
#include <WinSock2.h>

// 사용 방법 출력
void usage() { 
    printf("syntax : add-nbo <file1> <file2>\n");
    printf("sample : add-nbo a.bin c.bin");
}

// 파일에서 4바이트를 읽어들인 후, 네트워크 바이트 오더를 호스트 바이트 오더로 변환한 값을 반환하는 함수
uint32_t readInt(char* fileName) {
    FILE* fp = fopen(fileName, "rb"); // 파일을 이진 파일로 열기
    if (fp == nullptr) {
        fprintf(stderr, "fopen returns null %s\n", strerror(errno)); //에러 메세지 출력
        exit(EXIT_FAILURE);
    }
    uint32_t n;
    size_t readLen = fread(&n, 1, sizeof(n), fp);  //4바이트를 하나씩 읽어라
    if (readLen != sizeof(n)) {  //4바이트가 읽혀지지 않으면
        fprintf(stderr, "fread return %lu\n", readLen);// 에러 메시지 출력
        exit(EXIT_FAILURE);
    }
    n = ntohl(n); // 네트워크 바이트 오더를 호스트 바이트 오더로 변환
    fclose(fp);
    return n;
}

int main(int argc, char* argv[]) {
    if (argc != 3) { //argc가 3개가 아니라면
        usage();  //사용 방법 출력
        exit(EXIT_FAILURE);
    }

    uint32_t n1 = readInt(argv[1]);  // 첫 번째 파일에서 4바이트 읽어들임
    uint32_t n2 = readInt(argv[2]);  // 두 번째 파일에서 4바이트 읽어들임
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, n1 + n2, n1 + n2); // 두 값을 더한 결과 출력
}
