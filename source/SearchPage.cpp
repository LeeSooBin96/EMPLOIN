#include <iostream>

#include "Database.h"
#include "DetailPage.h"
#include "GetCh.h"
#include "SearchPage.h"

using std::cout;

//커서 위치에 따른 목록 출력
void SearchPage::ListforPos(unsigned short pos)
{
    system("clear");
    //공고 목록 개수
    cout<<"검색 건수: "<<hnumL.size()<<std::endl;
    cout<<"입력된 키워드 : "<<keyword<<std::endl;
    ShowNotice(pos);
    if(pos==hnumL.size())
    {
        cout<<"\x1b[m●  상세 검색 > \n";
        cout<<"\x1b[30m○  홈 화면으로 \x1b[m\n";
    }
    else if(pos==hnumL.size()+1)
    {
        cout<<"○  상세 검색 > \x1b[m\n";
        cout<<"●  홈 화면으로 \n";
    }
    else
    {
        cout<<"○  상세 검색 > \n";
        cout<<"○  홈 화면으로 \x1b[m\n";
    }
    cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
}
//공고 목록 출력 함수 - 커서 위치 입력받아서 색 변경 적용
void SearchPage::ShowNotice(unsigned short pos)
{
    //검색된 공고 목록 출력
    cout<<"검색된 공고 목록 > \n";
    for(int i=0;i<hnumL.size();i++)
    {
        if(pos==i) cout<<"\x1b[m● ";
        else cout<<"\x1b[30m○ ";
        std::string sql="SELECT HTITLE AS '',CNAME AS '',HDATE AS '마감일',HSTATE AS '근무지',HCARR AS '경력',HEDU AS '학력' FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnumL[i])+";";
        db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
        if(pos==i) cout<<"\x1b[30m";
    }
}
void SearchPage::ProcessSearch(void)
{
    //구성: 검색 건수/ 입력된 키워드/ 검색된 공고 목록/ 상세 검색 키워드/ 초기 화면으로

    db.DataBaseOpen("DB_Hin.db");

    //검색 키워드 입력 받기
    cout<<"검색어를 입력하세요> ";
    std::cin>>keyword; std::cin.get();
    //해당하는 공고 목록 받기
    hnumL=db.ProcessCMP_Return("SELECT * FROM HIRE_TB;",keyword);

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
                if(pos!=0) pos--;
                ListforPos(pos);
                break;
            case 66: //방향키 하
                if(pos!=hnumL.size()+1) pos++;
                ListforPos(pos);
                break;
            case 10: //엔터
                quit = true;
                break;
            default:
                break;
        }
    }
    if(pos<hnumL.size())
    {
        //공고 상세 보기
        DetailPage detail;
        detail.ProcessDetail();
    }
    else if(pos==hnumL.size())
    {
        //상세 검색 -- 화면 클리어를 할까..말까..
        system("clear");
        pos=0;
        quit=false;

        //카테고리 : 경력, 학력, 근무지, 요구스킬
        cout<<"▶경력 학력 근무지 요구스킬 검색 \n";
        while(!quit)
        {
            //키입력 방향키 좌(68),우(67)
            input=getch();
            switch(input)
            {
                case 68:
                    if(pos!=0) pos--;
                    break;
                case 67:
                    if(pos!=4) pos++;
                    break;
                case 10:
                    quit=true;
                    break;
                default:
                    break;
            }
        }
        //세부 항목 : 무관/신입/경력, 무관/고졸/대졸(2,3)/대졸(4), 서울/경기/대전/인천/광주, C/C++/C#/Python/JAVA
        cout<<"무관 신입 경력 선택완료 \n";
        cout<<"무관 고졸이상 대졸(2,3년제)이상 대졸(4년제)이상 선택완료 \n";
        cout<<"서울 경기 대전 인천 광주 선택완료 \n";
        cout<<"C C++ C# Python JAVA 선택완료 \n";
        //검색된 공고 목록 번호 배열 이용하면 상세 조건 적용 더 좋지 않을까!! 두근!
    }
    else if(pos==hnumL.size()+1)
    {
        return;
    }    
}