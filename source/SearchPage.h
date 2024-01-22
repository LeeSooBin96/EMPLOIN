#ifndef SEARCH_PAGE_H_
#define SEARCH_PAGE_H_

const unsigned short CHNUM=17;

struct Check
{
    std::string Cname;
    bool Cchk;
    std::string colName;
};
class SearchPage
{
private:
    SQLite db;
    std::string sql; //쿼리문 저장 문자열
    std::string keyword; //검색 키워드
    std::vector<int> hnumL; //검색된 공고 번호 목록
    Check ch[CHNUM]={ //상세 조건
        {"경력무관",false,"SNULLC"},{"경력",false,"SOLDC"},{"신입",false,"SNEWC"},
        {"학력무관",false,"SEDU"},{"고졸이상",false,"SEDU"},{"대졸(2,3년제)이상",false,"SEDU"},{"대졸(4년제)이상",false,"SEDU"},
        {"서울",false,"SEOUL"},{"경기",false,"GYEONGGI"},{"대전",false,"DAEJEON"},{"인천",false,"INCHEON"},{"광주",false,"GWANGJU"},
        {"C",false,"C"},{"C++",false,"CPP"},{"C#",false,"CSP"},{"Python",false,"PYTHON"},{"JAVA",false,"JAVA"}
    };
public:
    //검색 페이지 메인 프로세스
    void ProcessSearch(void);
    //커서 위치에 따른 목록 출력
    void ListforPos(unsigned short);
    //공고 목록 출력 함수 - 커서 위치 입력받아서 색 변경 적용
    void ShowNotice(unsigned short);
    //상세 검색 메인 프로세스
    void ProcessDetail(void);
    //상세 검색 - 카테고리 목록
    void ShowCate(unsigned short);
    //경력 조건 선택
    void SelectCRR(void);
    //경력 조건 목록
    void ShowCRR(unsigned short);
    //학력 조건 선택
    void SelectEDU(void);
    //학력 조건 목록
    void ShowEDU(unsigned short);
    //근무지 조건 선택
    void SelectST(void);
    //근무지 조건 목록
    void ShowST(unsigned short);
    // 요구스킬 조건 선택
    void SelectSK(void);
    // 요구스킬 조건 목록
    void ShowSK(unsigned short);
};
#endif