#ifndef DETAIL_PAGE_H_
#define DETAIL_PAGE_H_

class DetailPage
{
private:
    SQLite db;
    std::string sql;
public:
    //공고 상세 정보 페이지 메인 프로세스
    void ProcessDetail(int);
    //커서 위치에 따른 목록 선택 화면
    void ListforPos(unsigned short);
};
#endif