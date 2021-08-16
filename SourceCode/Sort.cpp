#include <bits/stdc++.h>
using namespace std;


void bubblesort(vector<int> &nums)
// 次序不对，交换次序
{
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 1; j < nums.size(); j++)
        {
            if (nums[j - 1] > nums[j])
                swap(nums[j], nums[j - 1]);
        }
    }
}

void selectsort(vector<int> &nums)
// 每一次都选择最小/大的
{
    for (int i = 0; i < nums.size(); i++)
    {
        int minindex = i;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if(nums[minindex] > nums[j])
                minindex = j;
        }
        swap(nums[minindex], nums[i]);
    }
}

void insertsort(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
    {
        int j = i - 1;
        int current = nums[i];
        while (j >= 0 && nums[j] > current)
        {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = current;
    }
}

void merge(vector<int> &nums, int left, int right)
{
    int mid = (right - left) / 2 + left;
    vector<int> l(mid - left + 2, 0), r(right - mid + 1, 0);
    for (int i = 0; i < mid - left + 1; i++)
        l[i] = nums[i + left];
    for (int i = mid + 1; i < right + 1; i++)
        r[i - mid - 1] = nums[i];

    l[l.size() - 1] = INT_MAX;
    r[r.size() - 1] = INT_MAX;
    int i = 0, j = 0;
    for (int k = left; k < right + 1; k++)
    {
        if (l[i] <= r[j])
            nums[k] = l[i++];
        else
            nums[k] = r[j++];
    }
}
void mergesort(vector<int> &nums, int left, int right)
{
    if (left < right)
    {
        int mid = (right - left) / 2 + left;
        mergesort(nums, left, mid);
        mergesort(nums, mid + 1, right);
        merge(nums, left, right);
    }
}

void quicksort(vector<int> &nums, int left, int right)
{
    if (left >= right)
        return;
    int base = nums[left];
    int i = left, j = right, temp = 0;
    while (i < j)
    {
        while (i < j && nums[j] > base)
            j--;
        while (i < j && nums[i] <= base)
            i++;
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
    nums[left] = nums[i];
    nums[i] = base;
    quicksort(nums, left, i - 1);
    quicksort(nums, i + 1, right);
}

void sink(vector<int> &nums, int pos, int end)
{
    int dad = pos, len = end + 1;
    int son = dad * 2 + 1;
    while (son < len)
    {
        if (son + 1 < len && nums[son + 1] > nums[son])
            son++;
        if (nums[son] <= nums[dad])
            return;
        else
        {
            // printf("%d %d\n", nums[son], nums[dad]);
            swap(nums[son], nums[dad]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heapsort(vector<int> &nums)
{
    int len = nums.size();
    for (int i = len / 2 - 1; i >= 0; i--)
        sink(nums, i, len);
    for (int i = len - 1; i > 0; i--)
    {
        swap(nums[0], nums[i]);
        sink(nums, 0, i - 1);
    }
}

void shellsort(vector<int> &nums) {

}

void countingSort(vector<int> &nums) {

}

void bucketsort(vector<int> &nums) {

}

void radixSort(vector<int> &nums) {
    // 基数排序
}