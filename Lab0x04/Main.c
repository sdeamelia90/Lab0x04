#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 

#define LENGTH 3
int list[10000000] = { 0 };
int stringCombo[LENGTH];
int BUSYCOUNT = 0;
int triples[100000000] = { 0 };
int TRIPLECOUNT = 0;

int listTriple[100000000][3] = { 0 };

void doBusyWork() {
    for (int k = 0; k < 300; k++) {
        // Constant N
    }
    BUSYCOUNT++;
}

generateTriSumTestInput(long long int N, int maxValue, int nForcedTriplets) {


    int tripletCount = 0;

    for (int i = 0; i < N; i++) {
        list[i] = rand() % (maxValue * 2) - maxValue;

    }


    //return list of the indices of the pairs of triplets
    //main program can print these for verification
    for (int i = 0; i < nForcedTriplets; i++) {

        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        int sum = 0;

        index1 = rand() % (N);
        triples[tripletCount] = index1;
        tripletCount++;


        do {
            index2 = rand() % (N);
        } while (index2 == index1);
        triples[tripletCount] = index2;
        tripletCount++;


        do {
            index3 = rand() % (N);
        } while ((index3 == index1) | (index3 == index2));
        triples[tripletCount] = index3;
        tripletCount++;


        sum = list[index1] + list[index2];
        list[index3] = (0 - sum);

    }
}

void generate(long long int N) {
    int i;
    for (i = 0; i < N; i++) {
        list[i] = rand() % 100000 - 50000;
    }
}

int bruteForce(long long int N) {
    int listCount = 0;
    int matchesFound = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                doBusyWork();
                if (list[i] + list[j] + list[k] == 0) {
                    listTriple[listCount][0] = list[i];
                    listTriple[listCount][1] = list[j];
                    listTriple[listCount][2] = list[k];
                    listCount++;
                    matchesFound++;
                }
            }
        }
    }
    return matchesFound;
}

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

int bruteForce_Faster(int N) {
    int x;
    int temp;
    int k;

    //Bubble Sort T(N) ~ C * N ^ 2

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    //Iterate through all combinations of first and second values.  Find the Sums. T(N) ~ C * N ^ 2
    //Search for the third number that would sum to zero using Binary Search. T(N) ~ c * Log(N)
    int listCount = 0;
    int matchesFound = 0;
    int found = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            doBusyWork();
            x = list[i] + list[j];
            k = 0 - x;

            found = binarySearch(list, j + 1, N, k);
            if (found != -1) {
                listTriple[listCount][0] = list[i];
                listTriple[listCount][1] = list[j];
                listTriple[listCount][2] = list[found];
                listCount++;
                matchesFound++;
            }
        }
    }
    return matchesFound;
}

int bruteForce_Fastest(long long int N) {

    int matchesFound = 0;
    int listCount = 0;
    //Bubble Sort T(N) ~ C * N ^ 2

    int temp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < N - 2; i++) {
        doBusyWork();
        int j = i + 1;
        long long int k = N - 1;

        int sum;
        while (j < k) {
            sum = list[j] + list[k] + list[i];

            if (sum == 0) {
                listTriple[listCount][0] = list[i];
                listTriple[listCount][1] = list[j];
                listTriple[listCount][2] = list[k];
                listCount++;
                matchesFound++;
                j++;
            }
            else if (sum < 0)
                j++;
            else if (sum > 0)
                k--;
            doBusyWork();
        }
    }

    return matchesFound;
}


void printTable(int timeCount, double TIME[], int busyCountArr[], int sort) {
    printf("%12s %14s %20s %16s %16s %14s %14s \n", "Power of 2", "  N  ", "Measured Time(s)", "Dbling Ratio", "Expected Ratio", "Busy Count", "MT / BC");
    printf("=================================================================================================================\n");
    double n = 2;
    double doubleRatio = 0;
    double theoryRatio = 0;
    double busyTimeZero = TIME[0] / busyCountArr[0];

    printf("%12d %12d %22.8lf %16s %16s %14d %14.8lf\n", 0, 1, TIME[0], "-", "-", busyCountArr[0], busyTimeZero);

    for (int i = 1; i < timeCount; i++) {
        double busyTime = TIME[i] / (double)busyCountArr[i];
        if ((TIME[i - 1] == 0) | (TIME[i - 1] == -0)) {
            doubleRatio = 0;
        }
        else {
            doubleRatio = TIME[i] / TIME[i - 1];
        }
        if (sort == 1) {
            theoryRatio = 8.0;
        }
        else if (sort == 2) {
            theoryRatio = 4 * log2(n) / (log2(n) - log2(2));
        }
        else if (sort == 3) {
            theoryRatio = 4.0;
        }

        printf("%12d %12lld %22.8lf %16.2lf %16.2lf %14d %14.8lf\n", i, (long long int)n, TIME[i], doubleRatio, theoryRatio, busyCountArr[i], busyTime);
        n = n * 2;
    }
}

void printTable2(int timeCount, double TIME[]) {
    int n = 1;
    int rounds = timeCount / 3;
    printf("%12s %14s %13s %16s \n", "       ", "  Brute 3sum  ", "Faster 3sum", "Fastest 3sum");
    printf("======================================================================\n");
    printf("%12s %14s %13s %16s \n", "   N   ", "  Time  ", "Time", "Time");
    printf("======================================================================\n");
    for (int i = 0; i < rounds; i++) {
        printf("%9d %15.8lf %15.8lf %16.8lf \n", n, TIME[i], TIME[i + rounds], TIME[i + (2 * rounds)]);
        n = n * 2;
    }
}


int main(int argc, int argv) {

    double trialsTime_max = .250; // in seconds 

    long long int trialsCount_max = 1000000, // increase as needed to avoid time measurements of zero 
        N_min = 1,
        N_max = 2500, // adjust as needed, keep small for debugging 
        n,
        trial;

    clock_t splitTimeStamp,
        trialSetStart;

    double splitTime,
        trialSetCount,
        trialSetTime,
        dummySetCount,
        dummySetTime,
        averageTrialTime,
        averageDummyTrialTime,
        estimatedTimePerTrial;

    double timeArr[1000] = { 0 };
    int busyCountArr[1000] = { 0 };

    int timeCount = 0,
        sort = 0;


    /***************TESTING********************************
    int maxValue = 10000,
        nForcedTriplets = 1;

    int test = 100;

    generateTriSumTestInput(test, maxValue, nForcedTriplets);


    printf("============================\n");
    printf("Original List:\n");
    printf("============================\n");
    for (int i = 0; i < test; i++) {
        printf("Index %d: %d \n", i, list[i]);
    }
    printf("\n============================\n");
    printf("Data for the forced triplets\n");
    for (int i = 0; i < nForcedTriplets * 3; i++) {
        if (i % 3 == 0) {
            printf("============================\n");
            printf("Set of Triplets:\n");
        }
        printf("Index %d: %d\n", i, list[triples[i]]);
    }
    printf("\n");
    printf("============================\n");
    printf("Data for bruteForceFastest\n");
    int x = bruteForce_Fastest(test);
    int index = 0;
        for (int i = 0; i < x; i++) {
            printf("============================\n");
            printf("Set of Triplets:\n");
            for (int j = 0; j < 3; j++) {
                printf("Index %d: %d\n", index, listTriple[i][j]);
                index++;
            }
    }

    //***********TESTING*****************************************/

//    for (int z = 0; z < 3; z++) {
        for (n = 1; n < N_max; n = n * 2) {

            splitTime = 0.0;
            trialSetStart = clock();

            for (trial = 0; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {

                generate(n);

                /*
                if (z == 0) {
                    int a = bruteForce(n);
                }
                else if (z == 1) {
                    int b = bruteForce_Faster(n);
                }
                else {
                    int c = bruteForce_Fastest(n);
                }
                */

                //int a = bruteForce(n);
                //int b = bruteForce_Faster(n);
                int c = bruteForce_Fastest(n);

                splitTimeStamp = clock(); //  
                splitTime = (splitTimeStamp - (double)trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h  
                busyCountArr[timeCount] = BUSYCOUNT;
                BUSYCOUNT = 0;

            }

            trialSetCount = (double)trial; // value of trial when loop ends is how many we did 

            trialSetTime = splitTime; // total time for trial set is the last split time 

            averageTrialTime = trialSetTime / trialSetCount; // this is the average tiem per trial, including any prep/overhead 



            splitTime = 0.0;

            // get timestamp before set of dummy trials are run: 

            trialSetStart = clock();

            for (trial = 0; trial < trialSetCount && splitTime < trialsTime_max; trial++) {


                generate(n);


                splitTimeStamp = clock(); //  

                // split time is the difference between current split timestamp and the starting time stamp for trial set 

                splitTime = (splitTimeStamp - (double)trialSetStart) / (double)CLOCKS_PER_SEC; // CLOCK_PER_SEC define time.h  

            }

            dummySetCount = (double)trial; // value of trial when loop ends is how many we did, should be same as trialsSetCount 

            dummySetTime = splitTime; // total time for dummy trial set is the last split time 

            averageDummyTrialTime = dummySetTime / dummySetCount; // this is the average tiem per dummy trial, including any prep/overhead 

            estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime; // should be a decent measurement of time taken to run your algorithm 

            timeArr[timeCount] = estimatedTimePerTrial;
            timeCount++;
        }
 //   }

    printTable(timeCount, timeArr, busyCountArr, 3);
//    printTable2(timeCount, timeArr);
  }
