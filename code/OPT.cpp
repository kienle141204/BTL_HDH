#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 30

// Ham kiem tra xem trang c� trong bo nho kh�ng
bool isInMemory(int frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Ham tim vi tri cua trang can thay the theo thuat toan OPT
int findReplacementIndex(int frames[], int numFrames, int referenceString[], int currentReferenceIndex, int totalReferences) {
    int farthest = currentReferenceIndex;
    int indexToReplace = -1;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentReferenceIndex; j < totalReferences; j++) {
            if (frames[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }

        // Neu khong tim thay trang trong chuoi tham chieu con lai
        if (j == totalReferences) {
            return i;
        }
    }

    return (indexToReplace == -1) ? 0 : indexToReplace;
}

int main() {
    int numFrames, numReferences;
    int frames[MAX_FRAMES], referenceString[MAX_REFERENCES];

    // Nhap so khung trang
    printf("Nhap so khung trang: ");
    scanf("%d", &numFrames);

    // Nhap chuoi tham chieu trang
    printf("Nhap so trang tham chieu ");
    scanf("%d", &numReferences);

    printf("Nhap chuoi trang tham chieu: ");
    for (int i = 0; i < numReferences; i++) {
        scanf("%d", &referenceString[i]);
    }

    // Khoi tao khung trang
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    int pageFaults = 0;
    for (int i = 0; i < numReferences; i++) {
        int currentPage = referenceString[i];

        // Kiem tra xem trang hien tai da co trong bo nho chua
        if (!isInMemory(frames, numFrames, currentPage)) {
            int replacementIndex = findReplacementIndex(frames, numFrames, referenceString, i + 1, numReferences);
            frames[replacementIndex] = currentPage;
            pageFaults++;

            // In trang thai cua khung trang
            printf("Khung trang sau khi truy cap trang %d: ", currentPage);
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    printf("- ");
                } else {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }

    printf("Tong so loi trang: %d\n", pageFaults);

    return 0;
}

