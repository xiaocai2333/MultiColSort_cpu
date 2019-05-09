#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <ratio>
#include <ctime>
#include <chrono>

#define ROW 1000000
#define COL 5

using namespace std;

void OneColumnSort(int *Curcol, int *row_index, int begin, int end){
    for (int i = begin; i < end; ++i) {
        for (int j = i; j < end; ++j) {
            if(Curcol[i] > Curcol[j]){
                swap(Curcol[i], Curcol[j]);
                swap(row_index[i], row_index[j]);
            }
        }
    }
}

void Tag(int *group, int *CurrentCol){
    int tag = 0;
    for(int j = 0; j < ROW - 1; j++){
        if(group[j] != group[j+1]){
            group[j] = tag;
            tag++;
        } else{
            group[j] = tag;
            if(CurrentCol[j] != CurrentCol[j+1]){
                tag++;
            }
        }


    }
    group[ROW-1] = tag;
}

int main() {
    int32_t *row_index = (int32_t *) malloc(sizeof(int32_t) * ROW);
    int* group = (int *) malloc(sizeof(int) * ROW);
    int** test = new int*[ROW];
    for (int k = 0; k < ROW; k++) {
        test[k] = new int[COL];
    }
    int* CurCol = (int *) malloc(sizeof(int) * ROW);
    using namespace std::chrono;

//    生成随机数组
    for (int k = 0; k < ROW; k++) {
        for (int m = 0; m < COL; m++) {
            test[k][m] = rand() % 100;
        }
    }
//    生成初始化row_index
    for (int i = 0; i < ROW; ++i) {
        row_index[i] = i;
        group[i] = 0;
    }
//    输出原始数组
//    for(int i = 0; i < ROW; i++){
//        for(int j = 0; j < COL; j++){
//            std::cout<< test[i][j] << "\t";
//        }
//        std::cout<< std::endl;
//    }

//    进行多键值排序
    high_resolution_clock::time_point starttime = high_resolution_clock::now();
    for(int i = 0; i < COL; i++){
        //      取出待排序列
        for (int l = 0; l < ROW; ++l) {
            CurCol[l] = test[row_index[l]][i];
        }
        int begin = 0;
        int end = ROW;
        if(i != 0){
            for(int j = 0; j < ROW; j++){
                if(group[j] != group[j+1]){
                    end = j+1;
                    OneColumnSort(CurCol, row_index, begin, end);
                    begin = j+1;
                }
            }

        }
        if(i == 0){
            OneColumnSort(CurCol, row_index, begin, end);
        }
        Tag(group, CurCol);

//        for (int l = 0; l < ROW; ++l) {
//            std::cout<< group[l] << "\t";
//        }
//        std::cout<< std::endl;
//        std::cout<< "************************************************************************************\n";
        for (int k = 0; k < ROW; ++k) {
            test[k][i] = CurCol[k];
        }
    }
    high_resolution_clock::time_point endtime = high_resolution_clock::now();
    std::cout<< "************************************************************************************\n";
//    输出排序后的数组
//    for(int i = 0; i < ROW; i++){
//        for(int j = 0; j < COL; j++){
//            std::cout<< test[i][j] << "\t";
//        }
//        std::cout<< std::endl;
//    }

//    程序运行时间
    duration<double> time_span = duration_cast<duration<double>>(endtime - starttime);
    std::cout<< "totaltime = " << time_span.count() << "s" << std::endl;
    for (int l = 0; l < ROW; ++l) {
        delete test[l];
    }
    delete[] test;
}