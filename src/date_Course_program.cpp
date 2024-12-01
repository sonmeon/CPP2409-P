#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct DateCourse {
    string city;
    string theme;
    vector<string> places;
    vector<string> activities;
    vector<int> times; // 각 활동에 소요되는 시간 (분 단위)
};

// 함수 선언
void showCityOptions();
void showThemeOptions();
void showCoursePlan(int cityChoice, int themeChoice);
void displayCourse(const DateCourse& course);

int main() {
    int cityChoice, themeChoice;

    // 도시 선택
    showCityOptions();
    cout << "도시를 선택하세요 (1: 서울, 2: 부산, 3: 광주, 4: 순천, 5: 대전): ";
    cin >> cityChoice;

    // 테마 선택
    showThemeOptions();
    cout << "테마를 선택하세요 (1: 힐링, 2: 활동, 3: 문화, 4: 맛집): ";
    cin >> themeChoice;

    // 선택에 맞는 코스 출력
    showCoursePlan(cityChoice, themeChoice);

    return 0;
}

// 도시 선택지 출력
void showCityOptions() {
    cout << "도시 목록: 1: 서울, 2: 부산, 3: 광주, 4: 순천, 5: 대전" << endl;
}

// 테마 선택지 출력
void showThemeOptions() {
    cout << "테마 목록: 1: 힐링, 2: 활동, 3: 문화, 4: 맛집" << endl;
}

// 도시와 테마에 맞는 데이트 코스를 출력하는 함수
void showCoursePlan(int cityChoice, int themeChoice) {
    vector<DateCourse> courses;

    // 서울 도시와 테마에 따른 코스
    if (cityChoice == 1) {
        if (themeChoice == 1) {
            courses.push_back({"서울", "힐링", {"서울숲", "성수동 카페거리", "청계천"}, {"산책", "카페 탐방", "산책"}, {60, 90, 60}});
        } else if (themeChoice == 2) {
            courses.push_back({"서울", "활동", {"잠실 롯데월드", "석촌호수", "야구장"}, {"놀이기구", "호수 산책", "야구 응원"}, {120, 30, 90}});
        } else if (themeChoice == 3) {
            courses.push_back({"서울", "문화", {"국립중앙박물관", "이태원 북카페", "한남동 갤러리"}, {"박물관 관람", "책 읽기", "갤러리 투어"}, {90, 60, 90}});
        } else if (themeChoice == 4) {
            courses.push_back({"서울", "맛집", {"마포 돼지갈비", "홍대 디저트 카페", "경의선 숲길"}, {"돼지갈비", "디저트", "산책"}, {60, 45, 60}});
        }
    }
    // 부산 도시와 테마에 따른 코스
    else if (cityChoice == 2) {
        if (themeChoice == 1) {
            courses.push_back({"부산", "힐링", {"이기대", "오륙도 스카이워크", "해운대 카페"}, {"산책", "스카이워크", "카페"}, {60, 60, 90}});
        } else if (themeChoice == 2) {
            courses.push_back({"부산", "활동", {"송정 서핑", "해운대 요트", "광안리 수변공원"}, {"서핑", "요트", "산책"}, {120, 90, 60}});
        } else if (themeChoice == 3) {
            courses.push_back({"부산", "문화", {"감천문화마을", "영화의 전당", "부산현대미술관"}, {"벽화 감상", "영화 관람", "미술관"}, {60, 120, 90}});
        } else if (themeChoice == 4) {
            courses.push_back({"부산", "맛집", {"자갈치 시장", "국제시장", "부평깡통야시장"}, {"해산물", "간식", "야시장"}, {60, 60, 90}});
        }
    }
    // 광주 도시와 테마에 따른 코스
    else if (cityChoice == 3) {
        if (themeChoice == 1) {
            courses.push_back({"광주", "힐링", {"무등산", "전남대 메타세쿼이아길", "양림동 근대문화마을"}, {"산책", "문화 탐방"}, {120, 60, 90}});
        } else if (themeChoice == 2) {
            courses.push_back({"광주", "활동", {"국립아시아문화전당", "롤러장", "충장로 거리"}, {"전시 관람", "롤러 타기", "쇼핑"}, {90, 120, 90}});
        } else if (themeChoice == 3) {
            courses.push_back({"광주", "문화", {"518 민주화공원", "대인예술시장", "아트시네마"}, {"역사 탐방", "예술 작품 감상", "영화 관람"}, {90, 60, 120}});
        } else if (themeChoice == 4) {
            courses.push_back({"광주", "맛집", {"송정떡갈비", "동명동 카페거리", "국밥 맛집"}, {"떡갈비", "디저트", "국밥"}, {60, 45, 60}});
        }
    }
    // 순천 도시와 테마에 따른 코스
    else if (cityChoice == 4) {
        if (themeChoice == 1) {
            courses.push_back({"순천", "힐링", {"순천만 국가정원", "순천만 습지", "조계산 숲길"}, {"산책", "자연 탐방", "산책"}, {120, 90, 60}});
        } else if (themeChoice == 2) {
            courses.push_back({"순천", "활동", {"드라마 촬영장", "체험 마을", "나이트 사파리"}, {"사진 촬영", "체험", "사파리"}, {90, 120, 90}});
        } else if (themeChoice == 3) {
            courses.push_back({"순천", "문화", {"순천 향교", "낙안읍성", "전통 찻집"}, {"전통 문화 체험", "찻집 탐방"}, {90, 60, 45}});
        } else if (themeChoice == 4) {
            courses.push_back({"순천", "맛집", {"꼬막정식", "야시장", "간식 카페"}, {"꼬막정식", "야시장", "디저트"}, {60, 60, 45}});
        }
    }
    // 대전 도시와 테마에 따른 코스
    else if (cityChoice == 5) {
        if (themeChoice == 1) {
            courses.push_back({"대전", "힐링", {"대청호 오백리길", "한밭수목원", "유성온천"}, {"산책", "자연 탐방", "온천"}, {120, 90, 60}});
        } else if (themeChoice == 2) {
            courses.push_back({"대전", "활동", {"성심당", "카이스트 자연사박물관", "엑스포 다리"}, {"맛집", "박물관 체험", "산책"}, {60, 90, 60}});
        } else if (themeChoice == 3) {
            courses.push_back({"대전", "문화", {"대전 예술의전당", "중앙시장", "갤러리"}, {"공연 관람", "시장 탐방", "미술관"}, {120, 60, 90}});
        } else if (themeChoice == 4) {
            courses.push_back({"대전", "맛집", {"칼국수 맛집", "성심당 디저트", "밤거리 포장마차"}, {"칼국수", "디저트", "포장마차"}, {60, 45, 90}});
        }
    }

    // 선택된 코스가 없을 경우
    if (courses.empty()) {
        cout << "선택하신 도시와 테마에 맞는 코스가 없습니다." << endl;
        return;
    }

    // 코스 출력
    for (const auto& course : courses) {
        displayCourse(course);
    }
}

// 코스 출력 함수
void displayCourse(const DateCourse& course) {
    cout << "\n***** " << course.city << " " << course.theme << " 데이트 코스 *****" << endl;
    for (size_t i = 0; i < course.places.size(); i++) {
        cout << "장소: " << course.places[i] << endl;
        cout << "활동: " << course.activities[i] << endl;
        cout << "소요 시간: " << course.times[i] << "분" << endl;
        cout << "------------------------" << endl;
    }
}
