#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<string.h>
#include <stdint.h>
#include <WinSock2.h>

// ��� ��� ���
void usage() { 
    printf("syntax : add-nbo <file1> <file2>\n");
    printf("sample : add-nbo a.bin c.bin");
}

// ���Ͽ��� 4����Ʈ�� �о���� ��, ��Ʈ��ũ ����Ʈ ������ ȣ��Ʈ ����Ʈ ������ ��ȯ�� ���� ��ȯ�ϴ� �Լ�
uint32_t readInt(char* fileName) {
    FILE* fp = fopen(fileName, "rb"); // ������ ���� ���Ϸ� ����
    if (fp == nullptr) {
        fprintf(stderr, "fopen returns null %s\n", strerror(errno)); //���� �޼��� ���
        exit(EXIT_FAILURE);
    }
    uint32_t n;
    size_t readLen = fread(&n, 1, sizeof(n), fp);  //4����Ʈ�� �ϳ��� �о��
    if (readLen != sizeof(n)) {  //4����Ʈ�� �������� ������
        fprintf(stderr, "fread return %lu\n", readLen);// ���� �޽��� ���
        exit(EXIT_FAILURE);
    }
    n = ntohl(n); // ��Ʈ��ũ ����Ʈ ������ ȣ��Ʈ ����Ʈ ������ ��ȯ
    fclose(fp);
    return n;
}

int main(int argc, char* argv[]) {
    if (argc != 3) { //argc�� 3���� �ƴ϶��
        usage();  //��� ��� ���
        exit(EXIT_FAILURE);
    }

    uint32_t n1 = readInt(argv[1]);  // ù ��° ���Ͽ��� 4����Ʈ �о����
    uint32_t n2 = readInt(argv[2]);  // �� ��° ���Ͽ��� 4����Ʈ �о����
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, n1 + n2, n1 + n2); // �� ���� ���� ��� ���
}
