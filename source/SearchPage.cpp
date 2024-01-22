#include <iostream>

#include "Database.h"
#include "DetailPage.h"
#include "GetCh.h"
#include "SearchPage.h"

using std::cout;

//상세 검색 - 카테고리 목록
void SearchPage::ShowCate(unsigned short pos)
{
    system("clear");
    //카테고리 : 경력, 학력, 근무지, 요구스킬
    cout<<"선택된 조건> ";
    for(int i=0;i<CHNUM;i++)
    {
        if(ch[i].Cchk) cout<<ch[i].Cname<<", ";
    }cout<<"\b\b \n";
    switch(pos)
    {
        case 0:
            cout<<"▶ 경력 학력 근무지 요구스킬 검색 초기화\n";
            break;
        case 1:
            cout<<"경력 ▶ 학력 근무지 요구스킬 검색 초기화\n";
            break;
        case 2:
            cout<<"경력 학력 ▶ 근무지 요구스킬 검색 초기화\n";
            break;
        case 3:
            cout<<"경력 학력 근무지 ▶ 요구스킬 검색 초기화\n";
            break;
        case 4:
            cout<<"경력 학력 근무지 요구스킬 ▶ 검색 초기화\n";
            break;
        case 5:
            cout<<"경력 학력 근무지 요구스킬 검색 ▶ 초기화\n";
            break;
        default:
            break;
    }
}
//커서 위치에 따른 목록 출력
void SearchPage::ListforPos(unsigned short pos)
{
    system("clear");
    
    //공고 목록 개수
    cout<<"검색 건수: "<<hnumL.size()<<std::endl;
    cout<<"입력된 키워드 : "<<keyword<<", ";
    for (int i=0;i<CHNUM;i++)
    {
        if(ch[i].Cchk) cout<<ch[i].Cname<<", ";
    }cout<<"\b\b \n";
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
        sql="SELECT HTITLE AS '',CNAME AS '',HDATE AS '마감일',HSTATE AS '근무지',HCARR AS '경력',HEDU AS '학력' FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnumL[i])+";";
        db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
        if(pos==i) cout<<"\x1b[30m";
    }
}
//검색 페이지 메인 프로세스
void SearchPage::ProcessSearch(void)
{
    //구성: 검색 건수/ 입력된 키워드/ 검색된 공고 목록/ 상세 검색 키워드/ 초기 화면으로

    db.DataBaseOpen("DB_Hin.db");

    //검색 키워드 입력 받기
    cout<<"검색어를 입력하세요> ";
    std::cin>>keyword; std::cin.get();

    while(true)
    {
        unsigned short pos=0;
        unsigned short cnt=0;
        bool quit=false;
        int input;
        //해당하는 공고 목록 받기
        sql="SELECT * FROM HIRE_TB";
        // SELECT H.HNUM_PK FROM HIRE_TB AS H INNER JOIN SEARCH_TB AS S ON H.HNUM_PK=S.HNUM_PK WHERE S.SOLDC = 'o';
        for(int i=0;i<CHNUM;i++)
        {
            if(ch[i].Cchk&&(i<3||i>6))
            {
                if(cnt==0) sql.append(" AS H INNER JOIN SEARCH_TB AS S ON H.HNUM_PK=S.HNUM_PK WHERE ");
                sql.append(" (S."+ch[i].colName+"='o') OR");
                cnt++;
                cout<<ch[i].colName<<std::endl;
            }
            else if(ch[i].Cchk)
            {
                if(cnt==0) sql.append(" AS H INNER JOIN SEARCH_TB AS S ON H.HNUM_PK=S.HNUM_PK WHERE ");
                sql.append(" (S.SEDU="+std::to_string(i-3)+") OR");
                cnt++;
            }
        }
        if(cnt>0) {sql.pop_back();sql.pop_back();} //마지막 OR 빼기
        sql.append(";");
        hnumL=db.ProcessCMP_Return(sql.c_str(),keyword);
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
                    if(pos!=hnumL.size()+1) 
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
        if(pos<hnumL.size())
        {
            //공고 상세 보기
            DetailPage detail;
            detail.ProcessDetail(hnumL[pos]);
        }
        else if(pos==hnumL.size())
        {
            //상세 검색
            ProcessDetail();
        }
        else if(pos==hnumL.size()+1)
        {
            return;
        }    
    }
}
//상세 검색 메인 프로세스
void SearchPage::ProcessDetail(void)
{
    while(true)
    {
        //상세 검색 -- 화면 클리어를 할까..말까..
        unsigned short pos=0;
        bool quit=false;
        int input;

        ShowCate(pos);
        cout<<"(이동: 방향키 좌/ 우) (선택: 엔터) \n";
        while(!quit)
        {
            //키입력 방향키 좌(68),우(67)
            input=getch();
            switch(input)
            {
                case 68:
                    if(pos!=0) 
                    {
                        pos--;
                        ShowCate(pos);
                        cout<<"(이동: 방향키 좌/ 우) (선택: 엔터) \n";
                    }
                    break;
                case 67:
                    if(pos!=5) 
                    {
                        pos++;
                        ShowCate(pos);
                        cout<<"(이동: 방향키 좌/ 우) (선택: 엔터) \n";
                    }
                    break;
                case 10:
                    quit=true;
                    break;
                default:
                    break;
            }
        }
        //세부 항목 : 무관/신입/경력, 무관/고졸/대졸(2,3)/대졸(4), 서울/경기/대전/인천/광주, C/C++/C#/Python/JAVA
        switch(pos)
        {
            case 0: //경력
                SelectCRR();
                break;
            case 1: //학력
                SelectEDU();
                break;
            case 2: //근무지
                SelectST();
                break;
            case 3: //요구스킬
                SelectSK();
                break;
            case 4: //검색
                break;
            case 5: //조건 초기화
                for(int i=0;i<CHNUM;i++) ch[i].Cchk=false;
                break;
            default:
                break;
        }
        if(pos==4) break; //검색
        //검색된 공고 목록 번호 배열 이용하면 상세 조건 적용 더 좋지 않을까!! 두근!
    }
}
//경력 조건 선택
void SearchPage::SelectCRR(void)
{
    unsigned short pos=0;
    bool quit = false;
    int input;

    ShowCRR(pos);
    while(!quit)
    {
        //키입력 방향키 좌(68),우(67)
        input=getch();
        switch(input)
        {
            case 68:
                if(pos!=0) 
                {
                    pos--;
                    ShowCRR(pos);
                }
                break;
            case 67:
                if(pos!=3) 
                {
                    pos++;
                    ShowCRR(pos);
                }
                break;
            case 10:
                quit=true;
                break;
            default:
                break;
        }
    }
    if(pos==0)
    {
        for(int i=0;i<3;i++) ch[i].Cchk=true;
    }
    else if(pos<4)
    {
        if(ch[pos-1].Cchk) ch[pos-1].Cchk=false;
        else ch[pos-1].Cchk=true;
    }
}
//경력 조건 목록
void SearchPage::ShowCRR(unsigned short pos)
{
    system("clear");
    ShowCate(0);
    switch(pos)
    {
        case 0:
            cout<<"▶ 전체 무관 경력 신입 \n";
            break;
        case 1:
            cout<<"전체 ▶ 무관 경력 신입 \n";
            break;
        case 2:
            cout<<"전체 무관 ▶ 경력 신입 \n";
            break;
        case 3:
            cout<<"전체 무관 경력 ▶ 신입 \n";
            break;
    }
    cout<<"(이동: 방향키 좌/ 우) (선택: 엔터) \n";
}//경력 조건 선택
//학력 조건 선택
void SearchPage::SelectEDU(void)
{
    unsigned short pos=0;
    bool quit = false;
    int input;

    ShowEDU(pos);
    while(!quit)
    {
        //키입력 방향키 좌(68),우(67)
        input=getch();
        switch(input)
        {
            case 68:
                if(pos!=0) 
                {
                    pos--;
                    ShowEDU(pos);
                }
                break;
            case 67:
                if(pos!=4) 
                {
                    pos++;
                    ShowEDU(pos);
                }
                break;
            case 10:
                quit=true;
                break;
            default:
                break;
        }
    }
    if(pos==0)
    {
        for(int i=0;i<4;i++) ch[i+3].Cchk=true;
    }
    else if(pos<5)
    {
        if(ch[pos+2].Cchk) ch[pos+2].Cchk=false;
        else ch[pos+2].Cchk=true;
    }
}
//학력 조건 목록
void SearchPage::ShowEDU(unsigned short pos)
{
    system("clear");
    ShowCate(0);
    switch(pos)
    {
        case 0:
            cout<<"▶ 전체 무관 고졸이상 대졸(2,3년제)이상 대졸(4년제)이상 \n";
            break;
        case 1:
            cout<<"전체 ▶ 무관 고졸이상 대졸(2,3년제)이상 대졸(4년제)이상 \n";
            break;
        case 2:
            cout<<"전체 무관 ▶ 고졸이상 대졸(2,3년제)이상 대졸(4년제)이상 \n";
            break;
        case 3:
            cout<<"전체 무관 고졸이상 ▶ 대졸(2,3년제)이상 대졸(4년제)이상 \n";
            break;
        case 4:
            cout<<"전체 무관 고졸이상 대졸(2,3년제)이상 ▶ 대졸(4년제)이상 \n";
            break;
    }
    cout<<"(이동: 방향키 좌/ 우) (선택: 엔터) \n";
}
//근무지 조건 선택
void SearchPage::SelectST(void)
{
    unsigned short pos=0;
    bool quit = false;
    int input;

    ShowST(pos);
    while(!quit)
    {
        //키입력 방향키 좌(68),우(67)
        input=getch();
        switch(input)
        {
            case 68:
                if(pos!=0) 
                {
                    pos--;
                    ShowST(pos);
                }
                break;
            case 67:
                if(pos!=5) 
                {
                    pos++;
                    ShowST(pos);
                }
                break;
            case 10:
                quit=true;
                break;
            default:
                break;
        }
    }
    if(pos==0)
    {
        for(int i=0;i<5;i++) ch[i+7].Cchk=true;
    }
    else if(pos<6)
    {
        if(ch[pos+6].Cchk) ch[pos+6].Cchk=false;
        else ch[pos+6].Cchk=true;
    }
}
//근무지 조건 목록
void SearchPage::ShowST(unsigned short pos)
{
    system("clear");
    ShowCate(0);
    switch(pos)
    {
        case 0:
            cout<<"▶ 전체 서울 경기 대전 인천 광주 \n";
            break;
        case 1:
            cout<<"전체 ▶ 서울 경기 대전 인천 광주 \n";
            break;
        case 2:
            cout<<"전체 서울 ▶ 경기 대전 인천 광주 \n";
            break;
        case 3:
            cout<<"전체 서울 경기 ▶ 대전 인천 광주 \n";
            break;
        case 4:
            cout<<"전체 서울 경기 대전 ▶ 인천 광주 \n";
            break;
        case 5:
            cout<<"전체 서울 경기 대전 인천 ▶ 광주 \n";
            break;
    }
    cout<<"(이동: 방향키 좌/ 우) (선택: 엔터) \n";
}
//요구스킬 조건 선택
void SearchPage::SelectSK(void)
{
    unsigned short pos=0;
    bool quit = false;
    int input;

    ShowSK(pos);
    while(!quit)
    {
        //키입력 방향키 좌(68),우(67)
        input=getch();
        switch(input)
        {
            case 68:
                if(pos!=0) 
                {
                    pos--;
                    ShowSK(pos);
                }
                break;
            case 67:
                if(pos!=5) 
                {
                    pos++;
                    ShowSK(pos);
                }
                break;
            case 10:
                quit=true;
                break;
            default:
                break;
        }
    }
    if(pos==0)
    {
        for(int i=0;i<5;i++) ch[i+12].Cchk=true;
    }
    else if(pos<6)
    {
        if(ch[pos+11].Cchk) ch[pos+11].Cchk=false;
        else ch[pos+11].Cchk=true;
    }
}
//요구스킬 조건 목록
void SearchPage::ShowSK(unsigned short pos)
{
    system("clear");
    ShowCate(0);
    switch(pos)
    {
        case 0:
            cout<<"▶ 전체 C C++ C# Python JAVA \n";
            break;
        case 1:
            cout<<"전체 ▶ C C++ C# Python JAVA \n";
            break;
        case 2:
            cout<<"전체 C ▶ C++ C# Python JAVA \n";
            break;
        case 3:
            cout<<"전체 C C++ ▶ C# Python JAVA \n";
            break;
        case 4:
            cout<<"전체 C C++ C# ▶ Python JAVA \n";
            break;
        case 5:
            cout<<"전체 C C++ C# Python ▶ JAVA \n";
            break;
    }
    cout<<"(이동: 방향키 좌/ 우) (선택: 엔터) \n";
}