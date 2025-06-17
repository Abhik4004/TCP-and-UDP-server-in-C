#include<stdio.h>
#include<stdlib.h>

void toBinary(char *ipStr, char *binaryStr) {
    int n1, n2, n3 ,n4;
    sscanf(ipStr, "%d.%d.%d.%d", &n1, &n2, &n3, &n4);
    sprintf(binaryStr, "%08b.%08b.%08b.%08b", n1, n2, n3, n4);
}

void toDecimal(char *binaryStr, char *ipStr) {
    int n1, n2, n3 ,n4;
    n1 = strtol(binaryStr, NULL, 2);
    n2 = strtol(binaryStr + 8, NULL, 2);
    n3 = strtol(binaryStr + 16, NULL, 2);
    n4 = strtol(binaryStr + 32, NULL, 2);
    sprintf(ipStr, "%d.%d.%d.%d", n1, n2, n3, n4);
}

int main() {
    char ip[32];
    char binaryIp[64];
    char convertedIp[32];

    printf("{+} Enter IP address: ");
    fgets(ip, sizeof(ip) - 1, stdin);
    toBinary(ip, binaryIp);
    printf("%s\n", binaryIp);

    toDecimal(binaryIp, convertedIp);
    printf("%s\n", convertedIp);
}