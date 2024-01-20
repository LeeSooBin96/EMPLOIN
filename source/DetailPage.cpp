#include <iostream>

#include "CompanyPage.h"
#include "DetailPage.h"

void DetailPage::ProcessDetail(void)
{
    //공고 번호 전달 받아서 저장
    
    //구성: 공고 상세 정보/ 기업 정보 자세히/ 이전으로
    std::cout<<"공고 상세 정보 \n"
               "기업 정보 자세히> \n"
               "이전으로> \n";
    std::cin.get();
    //기업 정보 페이지
    CompanyPage company;
    company.ProcessCompany();
}