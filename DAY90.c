#include <stdio.h>

// Function to check if boards can be painted within maxTime using k painters
int isPossible(int boards[], int n, int k, int maxTime) {
    int painters = 1;
    int currSum = 0;

    for (int i = 0; i < n; i++) {
        if (currSum + boards[i] <= maxTime) {
            currSum += boards[i];
        } else {
            painters++;
            currSum = boards[i];

            if (painters > k) {
                return 0;
            }
        }
    }
    return 1;
}

int findMinTime(int boards[], int n, int k) {
    int low = 0, high = 0;

    // Find max and sum
    for (int i = 0; i < n; i++) {
        if (boards[i] > low)
            low = boards[i];
        high += boards[i];
    }

    int result = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isPossible(boards, n, k, mid)) {
            result = mid;
            high = mid - 1; // try smaller
        } else {
            low = mid + 1; // need more time
        }
    }

    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int boards[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &boards[i]);
    }

    printf("%d\n", findMinTime(boards, n, k));
    return 0;
}