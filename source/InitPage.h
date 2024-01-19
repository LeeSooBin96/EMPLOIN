#ifndef INIT_PAGE_H_
#define INIT_PAGE_H_

class InitPage
{
public:
    //공고 목록 출력 함수 - 커서 위치 입력받아서 색 변경 적용
    void ShowNotice(unsigned short);
    //커서 위치에 따른 목록 출력
    void ListforPos(unsigned short);
    //초기 페이지 메인 프로세스
    void ProcessInit(void);
};
#endif