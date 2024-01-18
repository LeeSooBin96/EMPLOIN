#include <iostream>

#include "DetailPage.h"
#include "SearchPage.h"

void SearchPage::ProcessSearch(void)
{
    //구성: 검색 건수/ 입력된 키워드/ 검색된 공고 목록/ 상세 검색 키워드/ 초기 화면으로
    std::cout<<"검색 건수: "<<std::endl;
    std::cout<<"입력된 키워드 : "<<std::endl;
    std::cout<<"검색된 공고 목록 \n";
    std::cout<<"상세 검색 > \n";
    std::cout<<"홈 화면으로 \n";
    std::cin.get();

    DetailPage detail;
    detail.ProcessDetail();
}