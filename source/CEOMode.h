#ifndef CEO_MODE_H_
#define CEO_MODE_H_

#include <iostream>
#include <vector>

class CEOMode
{
private:
    int cnum; //회사 번호 저장
    int hnum; //공고 번호 저장
    std::string id; //아이디
    std::string pw; //비밀번호
    std::vector<int> hnumL; //공고 번호
    //공고 테이블 컬럼명
    std::string HcolName[17][2]={{"HTITLE","제목"},{"HDATE","마감일"},{"HCARR","경력"},{"HEDU","학력"},{"HSALARY","급여"},
    {"HTYPE","근무형태"},{"HDAY","근무일시"},{"HLEV","직급/직책"},{"HPOS","포지션"},{"HPART","담당업무"},{"HQF","자격요건"},
    {"HPER","우대조건"},{"HHEAL","복리후생"},{"HSTEP","전형절차"},{"HAPP","접수방법"},{"HDOC","제출서류"},{"HNOTIC","유의사항"}};
    std::string CcolName[9][2]={{"CTYPE","업종"},{"CCEO","대표자"},{"CSIZE","기업형태"},{"CNOP","사원수"},{"CPROD","사업내용"},
    {"CSITE","홈페이지"},{"CSTATE","주소"},{"CINC","매출액"},{"CANN","평균연봉"}};
public:
    //메인 프로세스
    void ProgressCEOMode(void);
    //정보 수정
    void ModifyInfo(void);
    //커서에 따른 목록
    void ListforPos(unsigned short);
    //공고 수정 
    void ModifyHireNotice(void);
    //커서에 따른 공고
    void NoticeforPos(unsigned short);
    //기업 정보 수정
    void ModifyCompanyInfo(void);
    //커서에 따른 기업 정보
    void InfoforPos(unsigned short);
    //검색 테이블 갱신
    void UpdateSearchTB(void);
};
#endif