#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib> // 랜덤 추천용
#include <ctime>
#include <numeric>  // iota 사용
#include <random>   // std::default_random_engine 사용
#include <algorithm> // std::shuffle 사용

using namespace std;

// 관광지 코스를 나타내는 기본 클래스
class Course {
protected:
    string city;        // 도시
    string theme;       // 테마
    string place;       // 장소
    string activity;    // 활동
    int time;           // 소요 시간
    string address;     // 주소

public:
    // 생성자: Course 객체를 초기화하는 생성자
    Course(string city, string theme, string place, string activity, int time, string address)
        : city(city), theme(theme), place(place), activity(activity), time(time), address(address) {}

    // 접근자 (getter) 메서드들
    string getCity() const { return city; }      // 도시 반환
    string getTheme() const { return theme; }    // 테마 반환
    string getPlace() const { return place; }    // 장소 반환
    string getActivity() const { return activity; } // 활동 반환
    int getTime() const { return time; }         // 소요 시간 반환
    string getAddress() const { return address; } // 주소 반환

    // 코스 정보를 출력하는 함수
    virtual void display() const {
        cout << "장소: " << place << endl;
        cout << "활동: " << activity << endl;
        cout << "소요 시간: " << time << "분" << endl;
        cout << "주소: " << address << endl;
    }
};

// 맛집 코스를 위한 클래스를 Course 클래스에서 상속받아 구현
class Restaurant : public Course {
public:
    // 생성자: Restaurant 객체를 초기화하는 생성자
    Restaurant(string city, string theme, string place, string activity, int time, string address)
        : Course(city, theme, place, activity, time, address) {}

    // 맛집에 특화된 정보를 출력 (기본 코스 정보는 부모 클래스에서 출력)
    void display() const override {
        Course::display();  // 부모 클래스의 display 함수 호출
        cout << "맛집 정보가 포함된 코스입니다!" << endl; // 맛집에 대한 추가 정보 출력
    }
};

// 추천을 위한 정적 멤버 변수
class TouristGuide {
private:
    static int totalCourses;  // 총 코스 수를 추적하는 정적 변수

public:
    // 정적 멤버 함수: 총 코스 수를 증가시키는 함수
    static void incrementCourses() { totalCourses++; }

    // 정적 멤버 함수: 총 코스 수를 반환하는 함수
    static int getTotalCourses() { return totalCourses; }
};

// 정적 멤버 초기화
int TouristGuide::totalCourses = 0;

// 코스를 파일에서 로드하는 함수
vector<Course*> loadCourses(const string& fileName) {
    vector<Course*> courses;  // Course 객체를 저장할 벡터

    ifstream file(fileName);  // 파일 열기
    if (!file) {  // 파일 열기 실패 시 에러 메시지 출력
        cerr << "파일을 열 수 없습니다: " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {  // 파일에서 한 줄씩 읽음
        stringstream ss(line);
        string city, theme, place, activity, timeStr, address;

        getline(ss, city, ',');   // 도시 읽기
        getline(ss, theme, ',');  // 테마 읽기
        getline(ss, place, ',');  // 장소 읽기
        getline(ss, activity, ','); // 활동 읽기
        getline(ss, timeStr, ',');  // 시간 읽기
        getline(ss, address);  // 주소 읽기

        int time = stoi(timeStr);  // 시간을 정수로 변환
        Course* course = new Course(city, theme, place, activity, time, address);  // Course 객체 동적 생성
        courses.push_back(course);  // 벡터에 추가
        TouristGuide::incrementCourses(); // 총 코스 수 증가
    }

    file.close();  // 파일 닫기
    return courses;  // 코스 목록 반환
}

// 코스를 출력하는 함수
void displayCourse(const vector<Course*>& courses) {
    cout << "\n***** 추천 데이트 코스 *****" << endl;
    for (size_t i = 0; i < courses.size(); i++) {  // 코스 리스트 출력
        cout << i + 1 << ". ";  // 코스 번호 출력
        courses[i]->display();  // 각 코스의 display 호출 (다형성)
        cout << "------------------------" << endl;
    }
}

// 특정 코스를 재추천하는 함수
void reRecommend(vector<Course*>& courses, const vector<Course*>& previousCourses) {
    int choice;
    cout << "재추천을 원하는 코스 번호를 입력하세요 (1 ~ " << courses.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(courses.size())) {  // 잘못된 번호 입력 시 오류 메시지
        cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        return;
    }

    vector<Course*> remainingCourses;  // 남은 코스를 저장할 벡터
    for (const auto& course : previousCourses) {  // 이전에 추천된 코스와 비교
        bool isDuplicate = false;  // 중복 여부 확인
        for (const auto& current : courses) {  // 기존 추천 코스와 비교
            if (course->getPlace() == current->getPlace()) {  // 장소가 같으면 중복
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {  // 중복이 아니면 남은 코스에 추가
            remainingCourses.push_back(course);
        }
    }

    if (remainingCourses.empty()) {  // 남은 코스가 없으면
        cout << "더 이상 추천할 코스가 없습니다." << endl;
        return;
    }

    int randomIndex = rand() % remainingCourses.size();  // 남은 코스 중 랜덤으로 선택
    delete courses[choice - 1];  // 기존 코스 메모리 해제
    courses[choice - 1] = remainingCourses[randomIndex];  // 새 코스로 교체
    cout << "선택하신 코스가 재추천되었습니다!" << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0))); // 랜덤 시드 설정
    vector<Course*> courses = loadCourses("courses.txt"); // 코스 로드
    string cities[] = {"서울", "부산", "광주", "순천", "대전"};
    string themes[] = {"힐링", "활동", "문화", "맛집"};

    int cityChoice, themeChoice;
    cout << "도시 목록: 1: 서울, 2: 부산, 3: 광주, 4: 순천, 5: 대전" << endl;
    cout << "도시를 선택하세요 (1~5): ";
    cin >> cityChoice;

    cout << "테마 목록: 1: 힐링, 2: 활동, 3: 문화, 4: 맛집" << endl;
    cout << "테마를 선택하세요 (1~4): ";
    cin >> themeChoice;

    if (cityChoice < 1 || cityChoice > 5 || themeChoice < 1 || themeChoice > 4) {  // 잘못된 입력 체크
        cout << "잘못된 입력입니다. 프로그램을 종료합니다." << endl;
        return 0;
    }

    string selectedCity = cities[cityChoice - 1];  // 선택된 도시
    string selectedTheme = themes[themeChoice - 1];  // 선택된 테마

    // 선택된 코스를 필터링
    vector<Course*> selectedCourses;
    for (const auto& course : courses) {
        if (course->getCity() == selectedCity && course->getTheme() == selectedTheme) {
            selectedCourses.push_back(course);  // 조건에 맞는 코스만 선택
        }
    }

    if (selectedCourses.empty()) {  // 조건에 맞는 코스가 없으면 종료
        cout << "선택하신 도시와 테마에 맞는 코스가 없습니다." << endl;
        return 0;
    }

    // 랜덤으로 4개의 코스 선택
    vector<Course*> recommendedCourses;
    vector<int> indices(selectedCourses.size());
    iota(indices.begin(), indices.end(), 0);  // 0부터 시작하는 인덱스 배열 생성

    // std::shuffle을 사용해 인덱스를 섞어 랜덤화
    random_device rd;
    mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    for (int i = 0; i < 4 && i < selectedCourses.size(); ++i) {
        recommendedCourses.push_back(selectedCourses[indices[i]]);  // 랜덤으로 4개 선택
    }

    displayCourse(recommendedCourses);  // 추천 코스 출력

    char retry;
    do {
        cout << "다시 추천을 받으시겠습니까? (y/n): ";
        cin >> retry;
        if (retry == 'y' || retry == 'Y') {
            reRecommend(recommendedCourses, selectedCourses);  // 재추천
            displayCourse(recommendedCourses);  // 새 추천 리스트 출력
        }
    } while (retry == 'y' || retry == 'Y');  // 재추천을 반복하는 루프

    // 동적 할당된 메모리 해제
    for (auto& course : courses) {
        delete course;
    }
    return 0;  // 프로그램 종료
}
