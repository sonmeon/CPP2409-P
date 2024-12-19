#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>  // 랜덤 숫자 생성을 위해 사용
#include <ctime>    // 시간 기반 시드를 설정하기 위해 사용
#include <numeric>  // iota 함수로 연속된 숫자 시퀀스를 생성
#include <random>   // std::shuffle를 위한 random 엔진
#include <algorithm> // std::shuffle 사용

using namespace std;

// 관광지 코스를 나타내는 기본 클래스
class Course {
protected:
    string city;        // 도시 이름 (예: 서울, 부산 등)
    string theme;       // 테마 (예: 힐링, 활동, 문화 등)
    string place;       // 관광지 이름
    string activity;    // 해당 장소에서 할 수 있는 활동 설명
    int time;           // 소요 시간 (분 단위)
    string address;     // 관광지 주소

public:
    // 생성자: Course 객체 초기화
    Course(string city, string theme, string place, string activity, int time, string address)
        : city(city), theme(theme), place(place), activity(activity), time(time), address(address) {}

    // getter 메서드들: 객체의 멤버 변수 값을 반환
    string getCity() const { return city; }
    string getTheme() const { return theme; }
    string getPlace() const { return place; }
    string getActivity() const { return activity; }
    int getTime() const { return time; }
    string getAddress() const { return address; }

    // 코스 정보를 출력하는 함수 (부모 클래스에서 사용)
    virtual void display() const {
        cout << "장소: " << place << endl;         // 관광지 이름
        cout << "활동: " << activity << endl;     // 활동 설명
        cout << "소요 시간: " << time << "분" << endl;  // 소요 시간
        cout << "주소: " << address << endl;     // 주소
    }
};

// 맛집 코스를 위한 클래스 (Course 클래스 상속)
class Restaurant : public Course {
public:
    // 생성자: Restaurant 객체 초기화 (부모 생성자 호출)
    Restaurant(string city, string theme, string place, string activity, int time, string address)
        : Course(city, theme, place, activity, time, address) {}

    // 맛집 정보 출력 함수: 부모 클래스의 display 함수 오버라이딩
    void display() const override {
        Course::display();  // 부모 클래스의 display 호출
        cout << "맛집 정보가 포함된 코스입니다!" << endl;  // 추가 메시지 출력
    }
};

// 추천 코스 총수를 추적하는 클래스
class TouristGuide {
private:
    static int totalCourses;  // 정적 변수: 전체 코스 수 추적

public:
    // 코스 수를 1 증가시키는 함수
    static void incrementCourses() { totalCourses++; }

    // 현재 코스 수를 반환하는 함수
    static int getTotalCourses() { return totalCourses; }
};

// 정적 변수 초기화
int TouristGuide::totalCourses = 0;

// 코스를 파일에서 로드하는 함수
vector<Course*> loadCourses(const string& fileName) {
    vector<Course*> courses;  // Course 객체 포인터를 저장할 벡터

    ifstream file(fileName);  // 파일 열기
    if (!file) {  // 파일 열기에 실패했을 경우
        cerr << "파일을 열 수 없습니다: " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {  // 파일에서 한 줄씩 읽기
        stringstream ss(line);
        string city, theme, place, activity, timeStr, address;

        // 각 열을 쉼표 기준으로 분리
        getline(ss, city, ',');
        getline(ss, theme, ',');
        getline(ss, place, ',');
        getline(ss, activity, ',');
        getline(ss, timeStr, ',');
        getline(ss, address);

        int time = stoi(timeStr);  // 소요 시간을 문자열에서 정수로 변환
        Course* course = new Course(city, theme, place, activity, time, address);
        courses.push_back(course);  // 벡터에 코스 추가
        TouristGuide::incrementCourses();  // 전체 코스 수 업데이트
    }

    file.close();  // 파일 닫기
    return courses;  // 읽어온 코스 벡터 반환
}

// 코스 정보를 출력하는 함수
void displayCourse(const vector<Course*>& courses) {
    cout << "\n***** 추천 데이트 코스 *****" << endl;
    for (size_t i = 0; i < courses.size(); i++) {
        cout << i + 1 << ". ";  // 각 코스 번호
        courses[i]->display();  // 코스 출력 (객체의 display 함수 호출)
        cout << "------------------------" << endl;
    }
}

// 특정 코스를 재추천하는 함수
void reRecommend(vector<Course*>& courses, const vector<Course*>& previousCourses) {
    int choice;
    cout << "재추천을 원하는 코스 번호를 입력하세요 (1 ~ " << courses.size() << "): ";
    cin >> choice;

    // 유효한 입력인지 검증
    if (choice < 1 || choice > static_cast<int>(courses.size())) {
        cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        return;
    }

    // 중복되지 않은 코스만 추출
    vector<Course*> remainingCourses;  
    for (const auto& course : previousCourses) {
        bool isDuplicate = false;
        for (const auto& current : courses) {
            if (course->getPlace() == current->getPlace()) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            remainingCourses.push_back(course);
        }
    }

    // 새로운 코스가 없을 경우
    if (remainingCourses.empty()) {
        cout << "더 이상 추천할 코스가 없습니다." << endl;
        return;
    }

    // 재추천 과정
    int randomIndex = rand() % remainingCourses.size();
    delete courses[choice - 1];  // 이전 코스 삭제
    courses[choice - 1] = remainingCourses[randomIndex];  // 새로운 코스로 교체
    cout << "선택하신 코스가 재추천되었습니다!" << endl;
}

// 메인 함수
int main() {
    srand(static_cast<unsigned>(time(0)));  // 랜덤 시드 설정
    vector<Course*> courses = loadCourses("courses.txt");  // 코스 로드

    string cities[] = {"서울", "부산", "광주", "순천", "대전"};
    string themes[] = {"힐링", "활동", "문화", "맛집"};

    int cityChoice, themeChoice;

    // 도시 선택
    cout << "도시 목록: 1: 서울, 2: 부산, 3: 광주, 4: 순천, 5: 대전" << endl;
    cout << "도시를 선택하세요 (1~5): ";
    cin >> cityChoice;

    // 테마 선택
    cout << "테마 목록: 1: 힐링, 2: 활동, 3: 문화, 4: 맛집" << endl;
    cout << "테마를 선택하세요 (1~4): ";
    cin >> themeChoice;

    // 입력 검증
    if (cityChoice < 1 || cityChoice > 5 || themeChoice < 1 || themeChoice > 4) {
        cout << "잘못된 입력입니다. 프로그램을 종료합니다." << endl;
        return 0;
    }

    string selectedCity = cities[cityChoice - 1];  // 선택된 도시
    string selectedTheme = themes[themeChoice - 1];  // 선택된 테마

    vector<Course*> selectedCourses;
    for (const auto& course : courses) {
        if (course->getCity() == selectedCity && course->getTheme() == selectedTheme) {
            selectedCourses.push_back(course);
        }
    }

    if (selectedCourses.empty()) {
        cout << "선택하신 도시와 테마에 맞는 코스가 없습니다." << endl;
        return 0;
    }

    vector<Course*> recommendedCourses;
    vector<int> indices(selectedCourses.size());
    iota(indices.begin(), indices.end(), 0);  // 0부터 순차적인 인덱스 생성

    // 코스 섞기
    random_device rd;
    mt19937 g(rd());
    shuffle(indices.begin(), indices.end(), g);

    for (int i = 0; i < 4 && i < selectedCourses.size(); ++i) {
        recommendedCourses.push_back(selectedCourses[indices[i]]);
    }

    displayCourse(recommendedCourses);

    char retry;
    do {
        cout << "다시 추천을 받으시겠습니까? (y/n): ";
        cin >> retry;

        while (retry != 'y' && retry != 'Y' && retry != 'n' && retry != 'N') {
            cout << "잘못된 입력입니다. 'y' 또는 'n'을 입력하세요: ";
            cin >> retry;
        }

        if (retry == 'y' || retry == 'Y') {
            reRecommend(recommendedCourses, selectedCourses);
            displayCourse(recommendedCourses);
        }
    } while (retry == 'y' || retry == 'Y');

    for (auto& course : courses) {
        delete course;
    }
    return 0;
}
