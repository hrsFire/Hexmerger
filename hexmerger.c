#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hexmerger.h"

int main(int argc, const char *argv[]) {
    const char* file1;
    const char* file2;
    const char* destinationFile;

    if (argc >= 4) {
        file1 = argv[1];
        file2 = argv[2];
        destinationFile = argv[3];

        int mergeResult = merge(file1, file2, destinationFile);

        if (mergeResult >= 0) {
            printf("merge successful");
        } else {
            printf("merge error: ");

            if(mergeResult == -1) {
                printf("IO error");
            }
        }

        printf("\n");
    } else {
        print_usage();
    }
}

void print_usage() {
    printf("Usage:\n");
    printf("\thexmerger file1 file2 destinationFile\n");
    printf("\n");
    printf("\tfile1 ... contains data\n");
    printf("\tfile2 ... contains keys\n");
}

int merge(const char* file1, const char* file2, const char* destinationFile) {
    FILE* fp1;
    FILE* fp2;
    FILE* fpDestination;

    fp1 = fopen(file1, "rb");
    fp2 = fopen(file2, "rb");
    fpDestination = fopen(destinationFile, "wb");

    if (fp1 != NULL && fp2 != NULL && fpDestination != NULL) {
        int i = 1;
        char chr1;
        char chr2;
        char chrDest;

        while (true) {
            chr1 = fgetc(fp1);
            chr2 = fgetc(fp2);

            if (feof(fp1) || feof(fp2)) {
                break;
            }

            if (is_header_section(i)) {
                chrDest = chr2;
            } else {
                chrDest = chr1;
            }

            fputc(chrDest, fpDestination);

            i++;
        }

        // close all file pointers
        fclose(fp1);
        fclose(fp2);
        fclose(fpDestination);

        return SUCCESS;
    }

    return IO_ERROR;
}

bool is_header_section(int pos) {
    for(int bottom = HEADER_START, top = HEADER_END; top <= HEADER_MAX_VALUE; bottom = top + HEADER_GAP +1, top = bottom + HEADER_LEN -1) {
        if (pos >= bottom && pos <= top) {
            return true;
        }
    }

    return false;
}