#include <iostream>

#include "CompanyPage.h"
#include "Database.h"
#include "DetailPage.h"

void DetailPage::ProcessDetail(int hnum)
{
    system("clear");
    SQLite db;
    db.DataBaseOpen("DB_Hin.db");
    //구성: 공고 상세 정보/ 기업 정보 자세히/ 이전으로
    //공고 번호 전달 받아서 저장 -hnum
    std::string sql;
    sql="SELECT CNAME AS '',HTITLE AS '',HDATE AS '마감일: ',"
        "HCARR AS '경력 ',HEDU AS '학력 ',HSALARY AS '급여 ',"
        "HTYPE AS '근무형태 ',HDAY AS '근무일시 ',HLEV AS '직급/직책 ',"
        "HPOS AS '포지션 ',HPART AS '담당업무 ',HQF AS '자격요건 ',"
        "HPER AS '우대조건 ',HHEAL AS '복리후생 ',HSTEP AS '전형절차 ',"
        "HAPP AS '접수방법 ',HDOC AS '제출서류 ',HNOTIC AS '유의사항 '"
        "FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";
    db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
    std::cout<<"기업 정보 자세히> \n"
               "이전으로> \n";
    std::cin.get();
    db.DataBaseClose();
    //기업 정보 페이지
    CompanyPage company;
    company.ProcessCompany(hnum);
}