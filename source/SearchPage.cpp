#include <iostream>

#include "Database.h"
#include "DetailPage.h"
#include "SearchPage.h"

void SearchPage::ProcessSearch(void)
{
    SQLite db;
    db.DataBaseOpen("DB_Hin.db");
    std::string keyword;
    std::vector<int> hnumL;
    //검색 키워드 입력 받기
    std::cin>>keyword;
    hnumL=db.ProcessCMP_Return("SELECT * FROM HIRE_TB;",keyword);
    for(int i=0;i<hnumL.size();i++) std::cout<<hnumL[i];
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