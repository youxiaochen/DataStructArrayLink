//
// Created by 77991 on 2018/6/11.
//

class HeapSort {
public:
    /**
     * 堆排序
     * @param arrs
     * @param len
     */
    static void sort(int *arrs, int len) {
        for (int i = (len >> 1) - 1; i >= 0; --i) {
            siftDown(arrs, len, i);
        }
        for (int i = len - 1; i > 0 ; --i) {
            swap(arrs, 0, i);
            siftDown(arrs, i, 0);
        }
    }

    /**
     * 从上至下调整大根堆
     * @param arrs
     * @param len
     * @param index
     */
    static void siftDown(int *arrs, int len, int index) {
        while (index < len >> 1) {
            int maxChildIndex = (index << 1) + 1; //左右孩子中找出最大值的孩子的位置
            int rightChildIndex = maxChildIndex + 1;
            if (rightChildIndex < len && arrs[rightChildIndex] > arrs[maxChildIndex]) {
                maxChildIndex = rightChildIndex;
            }
            if (arrs[maxChildIndex] <= arrs[index]) return;
            swap(arrs, index, maxChildIndex);
            index = maxChildIndex;
        }
    }

    /**
     * 交换
     * @param arrs
     * @param l
     * @param r
     */
    static void swap(int *arrs, int l, int r) {
        int tmp = arrs[l];
        arrs[l] = arrs[r];
        arrs[r] = tmp;
    }
};