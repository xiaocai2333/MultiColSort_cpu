#include <iostream>
#include <algorithm>
#include <stdlib.h>

#define ROW 100
#define COL 5
using namespace std;

void OneColumnSort(int *p[ROW], int begin, int end, int colum){
    for(int i = begin; i < end; i++){
        for(int j = i; j < end; j++){
            if(*(p[i] + colum) > *(p[j] + colum)){
                swap(p[i], p[j]);
            }
        }
    }
}

void Tag(int *row, int *p[ROW], int i){
    int tag = 0;
    for(int j = 0; j < 9; j++){
        row[j] = tag;
        row[j+1] = tag+1;
        if(row[j] < row[j+1]){
            tag++;
        }
        else if(*(p[j] + (i-1)) != *(p[j+1] + i-1)){
            tag++;
        }

    }
    row[ROW-1] = tag;
}
int main() {
    int row_index[ROW];
    int test[ROW][COL];
//    生成随机数组
    for (int k = 0; k < ROW; ++k) {
        for (int m = 0; m < COL; ++m) {
            test[k][m] = rand() % 5;
        }
    }
//    生成指针数组p指向test
    int *p[ROW];
    for (int i = 0; i < ROW; ++i) {
        p[i] = test[i];
        row_index[i] = 0;
    }
//    输出原始数组
//    for(int i = 0; i < ROW; i++){
//        for(int j = 0; j < COL; j++){
//            std::cout<< *(p[i] + j) << "\t";
//        }
//        std::cout<< std::endl;
//    }
//    进行多键值排序
    for(int i = 0; i < ROW; i++){
        int begin = 0;
        int end = ROW;
        if(i != 0){
            Tag(row_index, p, i);
            for(int j = 0; j < ROW; j++){
                if(row_index[j] != row_index[j+1]){
                    end = j+1;
                    OneColumnSort(p, begin, end, i);
                    begin = j+1;
                }
            }
        }
        if(i == 0)
            OneColumnSort(p, begin, end, i);
    }
    std::cout<< "************************************************************************************\n";
//    输出排序后的数组
    for(int i = 0; i < ROW; i++){
        std::cout<< std::endl;
        for(int j = 0; j < COL; j++){
            std::cout<< *(p[i] + j) << "\t";
        }
    }

}