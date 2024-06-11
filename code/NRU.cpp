#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
    int referenced;
    int modified;
    int page_num;
} Page;
void printPages(Page pages[], int num_pages) {
    printf("Trang\tTruy cập\tSửa đổi\n");
    for (int i = 0; i < num_pages; i++) {
        printf("%d\t%d\t\t%d\n", pages[i].page_num, pages[i].referenced, pages[i].modified);
    }
}
int isPageInMemory(Page pages[], int num_pages, int page_num) {
    for (int i = 0; i < num_pages; i++) {
        if (pages[i].page_num == page_num) {
            return i;
        }
    }
    return -1;
}
int selectPageToReplace(Page pages[], int num_pages) {
    int lowest_class = 4;
    int candidates[num_pages];
    int num_candidates = 0;
    for (int i = 0; i < num_pages; i++) {
        int page_class = (pages[i].referenced << 1) | pages[i].modified;
        if (page_class < lowest_class) {
            lowest_class = page_class;
            num_candidates = 0;
            candidates[num_candidates++] = i;
        } else if (page_class == lowest_class) {
            candidates[num_candidates++] = i;
        }
    }
    return candidates[rand() % num_candidates];
}
void resetReferenceBits(Page pages[], int num_pages) {
    for (int i = 0; i < num_pages; i++) {
        pages[i].referenced = 0;
    }
}
int main() {
    srand(time(NULL));
    int num_frames;
    printf("Nhập số lượng khung trang: ");
    scanf("%d", &num_frames);
    Page pages[num_frames];
    for (int i = 0; i < num_frames; i++) {
        pages[i].page_num = -1;
        pages[i].referenced = 0;
        pages[i].modified = 0;
    }
    int num_requests;
    printf("Nhập số lượng yêu cầu trang: ");
    scanf("%d", &num_requests);
    int page_requests[num_requests];
    printf("Nhập chuỗi các yêu cầu trang: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &page_requests[i]);
    }
    int page_faults = 0;
    for (int i = 0; i < num_requests; i++) {
        int page_num = page_requests[i];
        int page_index = isPageInMemory(pages, num_frames, page_num);
        if (page_index == -1) {
            page_faults++;
            int replace_index = selectPageToReplace(pages, num_frames);
            pages[replace_index].page_num = page_num;
            pages[replace_index].referenced = 1;
            pages[replace_index].modified = 0;
        } else {
            pages[page_index].referenced = 1;
        }
        if (i % 4 == 3) { // Đặt lại bit truy cập sau mỗi 4 yêu cầu trang
            resetReferenceBits(pages, num_frames);
        }
    }
    printf("\nTổng số trang lỗi: %d\n", page_faults);
    return 0;
}
