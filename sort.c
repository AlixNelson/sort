#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * get_array(int *out_size) {
    int *array = NULL; // 定义一个空指针，用于动态数组
    char *input = NULL; // 定义一个空指针，用于输入字符串
    char *token = NULL; // 定义一个空指针，用于分割字符串
    int size = 0;  // 定义一个变量，用于记录数组的大小
    const char *delimiter = ","; // 定义一个字符串，用于分隔输入的字符串

    printf("输入数组长度，以字符串类型时的长度为准");
    if (scanf("%d", &size) != 1 || size <= 0) { // 检查输入有效性
        printf("无效的数组长度\n");
        return NULL;
    }
    getchar(); // 清空输入缓存

    int buffer_size = size * 12 + 1;
    input = (char *)malloc(buffer_size * sizeof(char));
    if (input == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        free(input);
        printf("内存分配失败\n");
        return NULL;
    }

    printf("以字符串形式输入数组吗，用',’分隔");
    if (fgets(input, buffer_size, stdin) == NULL) {
        free(input);
        free(array);
        printf("输入错误\n");
        return NULL;
    }

    input[strcspn(input, "\n")] = '\0'; // 去掉输入字符串中可能存在的换行符

    token = strtok(input, delimiter); // 调用 strtok 函数，以 delimiter 为分隔符，将输入的字符串分割成多个字符串
    int i = 0;
    while (token!= NULL && i < size) {
        array[i] = atoi(token); // 调用 atoi 函数，将字符串转换为整数
        i++;
        token = strtok(NULL, delimiter); // 调用 strtok 函数，以 NULL 为参数，继续分割字符串
    }

    while (i < size) {
        array[i] = 0; // 数组元素初始化为 0
        i++;
    }

    free(input); // 释放输入字符串的内存

    *out_size = size;
    return array;
}

void * bubble_sort(int *array, int size) {
    for (int i = 0; i < size - 1;i ++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int lomuto(int *array, int low, int high) {
    int pivot = array[high]; // 以最右值为基准值
    int i = low - 1; // 第一次传入时i = -1

    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) { // 若快指针的元素小于基准值，则交换
            i++; // 第一次迭代时i = 0，这就是为什么上面要将i初始化为low - 1
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    // 最后一步，当快指针完成遍历后，慢指针的位置就是最后一个小于基准值的值，因此将二者交换
    // 此时慢指针的位置就是交换后分区基准值的索引
    int temp = array[i+1];
    array[i+1] = pivot;
    array[high] = temp;
    return i + 1;
}

void quick_sort_lomuto(int *array, int low, int high) { // 排序主函数，递归分区操作
    if(low < high) {
        int pivot_index =  lomuto(array, low, high); // 第一次分区，获取基准值
        quick_sort_lomuto(array, low, pivot_index - 1); // 递归操作左数组
        quick_sort_lomuto(array, pivot_index + 1, high); // 递归操作右数组
    }
}

void print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

int main() {
    int size;
    int *array = get_array(&size);
    // 调用任意排序函数
    if (array) {
        printf("原始数组: ");
        print_array(array, size);

        // 调用排序函数，这里使用快速排序
        quick_sort_lomuto(array, 0, size - 1);
        printf("排序后数组: ");
        print_array(array, size);

        free(array);
        
    }
    system("pause");
    return 0;
}