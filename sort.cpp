// 5 種 sort : insertion, selection, bubble, quick, merge

#include <iostream>
using namespace std;

class Sort {
    public :
        int *a;
        int n; // array size

        void sort();

        void print() {
            for (int i = 0;i < n;i++) {
                cout << a[i];
            }
            cout << endl;
        };
};

class InsertionSort : public Sort {
    public :
        InsertionSort(int *a, int n) {
            this->a = a;
            this->n = n;
        };

        void sort() {
            int temp;
            // 從第 2 個值開始排序
            for (int i = 1;i < n;i++) {
                // 往前比較
                for (int j = i;j > 0;j--) {
                    // 前面還沒排序好
                    if (a[j] < a[j-1]) {
                        // swap
                        temp = a[j];
                        a[j] = a[j-1];
                        a[j-1] = temp;
                    }
                    // 這回合排序已完成
                    else 
                        break;
                }
            }
            // print result
            print();
        };
};

class SelectionSort : public Sort {
    public :
        SelectionSort(int *a, int n) {
            this->a = a;
            this->n = n;
        }

        void sort() {
            int min;
            int temp;
            // 找 n-1 回合的最小值
            for (int i = 0;i < n-1;i++) {
                // 先把自己設為這回合的最小值
                int min = i;
                // 每回合找最小值
                for (int j = i+1;j < n;j++) {
                    if (a[min] > a[j])
                        min = j;
                }
                // swap
                temp = a[i];
                a[i] = a[min];
                a[min] = temp;
            }
            // print result
            print();
        };
};

class BubbleSort : public Sort {
    public :
        BubbleSort(int *a, int n) {
            this->a = a;
            this->n = n;
        };

        void sort() {
            int temp;
            bool is_sorted; // 是否已排序完成
            // 排序 n-1 回合
            for (int i = n-1;i > 0;i--) {
                is_sorted = true;
                // 每回合把最大的放到後面
                for (int j = 0;j < i;j++) {
                    // 如果左邊較大
                    if (a[j] > a[j+1]) {
                        // swap
                        temp = a[j];
                        a[j] = a[j+1];
                        a[j+1] = temp;
                        // 未排序好
                        is_sorted = false;
                    }
                }
                // 若已排序好
                if (is_sorted)
                    break;
            }
            // print result
            print();
        };
};

class QuickSort : public Sort {
    public :
        QuickSort(int *a, int n) {
            this->a = a;
            this->n = n;
        };

        void sort() {
            quickSort(0, n-1);
            print();
        };

        void quickSort(int s, int e) {
            if (e > s) {
                // 起始作為 pivot key
                int pivot = s;
                // 
                int i = pivot;
                int j = e;
                int temp;
                // 做這回合的 swap
                while (true) {
                    // 左邊找大於 pivot
                    // 還沒找到底
                    while (true) {
                        if (a[i] > a[pivot])
                            break;
                        // 不能超過終點
                        if (i < e)
                            i++;
                        else 
                            break;
                    }
                    // 右邊找小於 pivot
                    while (true) {
                        if (a[j] <= a[pivot])
                            break;
                        // 不能超過起點
                        if (j > s)
                            j--;
                        else
                            break;
                    }
                    // 右邊還沒超過左邊
                    if (j > i) {
                        // swap
                        temp = a[j];
                        a[j] = a[i];
                        a[i] = temp;
                    }
                    // 超過了，將 pivot 和 j swap，結束這回合
                    else {
                        temp = a[pivot];
                        a[pivot] = a[j];
                        a[j] = temp;
                        pivot = j;
                        break;
                    }  
                };
                // 以 pivot 為分界，左右兩邊做 quick sort
                quickSort(s, pivot-1);
                quickSort(pivot+1, e);
            }
        };
};

class MergeSort : public Sort {
    public :
        MergeSort(int *a, int n) {
            this->a = a;
            this->n = n;
        };

        void sort() {
            // 回傳 sort 好的 array
            this->a = mergeSort(0, n-1);
            print();
        }; 

        // merge 左邊和右邊, 並回傳 merge 完的新 run
        int* merge(int* left, int left_len, int* right, int right_len) {
            int *new_run = new int[left_len+right_len];
            int i = 0, j = 0, k = 0;
            // 當左右的 run 都還有 data
            while (i < left_len && j < right_len) {
                if (left[i] < right[j]) {
                    new_run[k++] = left[i++];
                }
                else {
                    new_run[k++] = right[j++];
                }
            }
            // 當左邊的 run 還有 data
            while (i < left_len) {
                // 直接放進 new run
                new_run[k++] = left[i++]; 
            }
            // 當右邊的 run 還有 data
            while (j < right_len) {
                // 直接放進 new run
                new_run[k++] = right[j++];
            }
            //printNewRun(new_run, left_len+right_len);
            return new_run;
        }

        // print each new run
        void printNewRun(int* new_run, int n) {
            for (int i = 0;i < n;i++) {
                cout << new_run[i];
            }
            cout << endl;
        }

        // merge sort
        int* mergeSort(int s, int e) {
            if (e > s) {
                // 切一半
                int mid = (s + e) / 2;
                int *left = mergeSort(s, mid);
                int *right = mergeSort(mid+1, e);
                // merge 左邊和右邊
                return merge(left, mid-s+1, right, e-mid);
            }
            // 剩自己
            else {
                // 回傳自己
                int *self = new int[0];
                self[0] = a[s];
                return self;
            }
        };
};

int main() {
    // array with n elements
    int a[] = {6,5,4,3,2,1};
    int n = 6;
    // insertion sort
    /*
    InsertionSort *insert = new InsertionSort(a, n);
    insert->sort();
    */

    // selection sort
    /*
    SelectionSort *select = new SelectionSort(a, n);
    select->sort();
    */

    // bubble sort
    /*
    BubbleSort *bubble = new BubbleSort(a, n);
    bubble->sort();
    */

    // quick sort
    /*
    QuickSort *quick = new QuickSort(a, n);
    quick->sort();
    */

    // merge sort
    MergeSort *merge = new MergeSort(a, n);
    merge->sort();

    return 0;
}
