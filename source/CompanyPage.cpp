#include <iostream>

#include "CompanyPage.h"
#include "Database.h"

void CompanyPage::ProcessCompany(int hnum)
{
    //구성: 기업 상세 정보/ 이전으로
    SQLite db;
    std::string sql;
    db.DataBaseOpen("DB_Hin.db");
    sql="SELECT CNAME AS '',CTYPE AS '업종',CCEO AS '대표자명',CSIZE AS '기업형태',"
        "CNOP AS '사원수',CESD AS '설립일',CPROD AS '사업내용',CSITE AS '홈페이지 주소',"
        "CSTATE AS '주소',CINC AS '매출액',CANN AS '평균연봉' FROM COMPANY_TB "
        "WHERE CNUM_PK=(SELECT CNUM FROM HIRE_TB WHERE HNUM_PK='"+std::to_string(hnum)+"');";
    db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
    std::cout<<"이전으로> \n";
    db.DataBaseClose();
    std::cin.get();
}