#include <iostream>

#include "CompanyPage.h"
#include "Database.h"
#include "DetailPage.h"
#include "GetCh.h"

void DetailPage::ListforPos(unsigned short pos)
{
    system("clear");
    db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
    if(pos==0)
    {
        std::cout<<"기업 정보 자세히> \n"
                    "\x1b[30m이전으로> \x1b[m\n";
    }
    else if(pos==1)
    {
        std::cout<<"\x1b[30m기업 정보 자세히> \x1b[m\n"
                    "이전으로> \n";
    }
    std::cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
}
void DetailPage::ProcessDetail(int hnum)
{
    db.DataBaseOpen("DB_Hin.db");
    //구성: 공고 상세 정보/ 기업 정보 자세히/ 이전으로
    //공고 번호 전달 받아서 저장 -hnum
    sql="SELECT CNAME AS '',HTITLE AS '',HDATE AS '마감일: ',"
        "HCARR AS '경력 ',HEDU AS '학력 ',HSALARY AS '급여 ',"
        "HTYPE AS '근무형태 ',HDAY AS '근무일시 ',HLEV AS '직급/직책 ',"
        "HPOS AS '포지션 ',HPART AS '담당업무 ',HQF AS '자격요건 ',"
        "HPER AS '우대조건 ',HHEAL AS '복리후생 ',HSTEP AS '전형절차 ',"
        "HAPP AS '접수방법 ',HDOC AS '제출서류 ',HNOTIC AS '유의사항 '"
        "FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";

    unsigned short pos=0;
    bool quit=false;
    int input;
    ListforPos(pos);
    while(!quit)
    {
        input=getch();
        switch(input)
        {
            case 65: //방향키 상
                if(pos!=0) 
                {
                    pos--;
                    ListforPos(pos);
                }
                break;
            case 66: //방향키 하
                if(pos!=1) 
                {
                    pos++;
                    ListforPos(pos);
                }
                break;
            case 10: //엔터
                quit = true;
                break;
            default:
                break;
        }
    }
    if(pos==0)
    {
        //기업 정보 페이지
        CompanyPage company;
        company.ProcessCompany(hnum);
        ProcessDetail(hnum);
    }
    // std::cin.get();
    db.DataBaseClose();
}