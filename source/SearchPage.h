#ifndef SEARCH_PAGE_H_
#define SEARCH_PAGE_H_

class SearchPage
{
private:
    SQLite db;
    std::string keyword; //검색 키워드
    std::vector<int> hnumL; //검색된 공고 번호 목록
public:
    //검색 페이지 메인 프로세스
    void ProcessSearch(void);
    //커서 위치에 따른 목록 출력
    void ListforPos(unsigned short);
    //공고 목록 출력 함수 - 커서 위치 입력받아서 색 변경 적용
    void ShowNotice(unsigned short);
};
#endif