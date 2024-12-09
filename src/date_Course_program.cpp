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

// 구조체 정의
struct Course {
    string city;
    string theme;
    string place;
    string activity;
    int time;
};

// 함수 선언
vector<Course> loadCourses(const string& fileName);
void displayCourse(const vector<Course>& courses);
void reRecommend(vector<Course>& courses, const string& selectedCity, const string& selectedTheme, const vector<Course>& previousCourses);

int main() {
    srand(static_cast<unsigned>(time(0))); // 랜덤 시드 설정
    vector<Course> courses = loadCourses("courses.txt"); // 코스 로드
    string cities[] = {"서울", "부산", "광주", "순천", "대전"};
    string themes[] = {"힐링", "활동", "문화", "맛집"};

    int cityChoice, themeChoice;
    cout << "도시 목록: 1: 서울, 2: 부산, 3: 광주, 4: 순천, 5: 대전" << endl;
    cout << "도시를 선택하세요 (1~5): ";
    cin >> cityChoice;

    cout << "테마 목록: 1: 힐링, 2: 활동, 3: 문화, 4: 맛집" << endl;
    cout << "테마를 선택하세요 (1~4): ";
    cin >> themeChoice;

    if (cityChoice < 1 || cityChoice > 5 || themeChoice < 1 || themeChoice > 4) {
        cout << "잘못된 입력입니다. 프로그램을 종료합니다." << endl;
        return 0;
    }

    string selectedCity = cities[cityChoice - 1];
    string selectedTheme = themes[themeChoice - 1];

    // 선택된 코스 필터링
    vector<Course> selectedCourses;
    for (const auto& course : courses) {
        if (course.city == selectedCity && course.theme == selectedTheme) {
            selectedCourses.push_back(course);
        }
    }

    if (selectedCourses.empty()) {
        cout << "선택하신 도시와 테마에 맞는 코스가 없습니다." << endl;
        return 0;
    }

    // 랜덤으로 4개의 코스 선택
    vector<Course> recommendedCourses;
    vector<int> indices(selectedCourses.size());
    iota(indices.begin(), indices.end(), 0); // 0부터 시작하는 인덱스 배열 생성

    // std::shuffle을 사용해 인덱스 섞기
    random_device rd;
    mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    for (int i = 0; i < 4 && i < selectedCourses.size(); ++i) {
        recommendedCourses.push_back(selectedCourses[indices[i]]);
    }

    displayCourse(recommendedCourses);

    char retry;
    do {
        cout << "마음에 들지 않는 코스가 있나요? (y/n): ";
        cin >> retry;
        if (retry == 'y') {
            reRecommend(recommendedCourses, selectedCity, selectedTheme, selectedCourses);
            displayCourse(recommendedCourses);
        }
    } while (retry == 'y');

    cout << "프로그램을 종료합니다. 즐거운 데이트 되세요!" << endl;
    return 0;
}

// 코스 데이터를 파일에서 로드
vector<Course> loadCourses(const string& fileName) {
    vector<Course> courses;
    ifstream file(fileName);

    if (!file) {
        cerr << "파일을 열 수 없습니다: " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string city, theme, place, activity, timeStr;

        getline(ss, city, ',');
        getline(ss, theme, ',');
        getline(ss, place, ',');
        getline(ss, activity, ',');
        getline(ss, timeStr, ',');

        Course course = {city, theme, place, activity, stoi(timeStr)};
        courses.push_back(course);
    }

    file.close();
    return courses;
}

// 코스 출력
void displayCourse(const vector<Course>& courses) {
    cout << "\n***** 추천 데이트 코스 *****" << endl;
    for (size_t i = 0; i < courses.size(); i++) {
        cout << i + 1 << ". 장소: " << courses[i].place << endl;
        cout << "   활동: " << courses[i].activity << endl;
        cout << "   소요 시간: " << courses[i].time << "분" << endl;
        cout << "------------------------" << endl;
    }
}

// 특정 코스 재추천
void reRecommend(vector<Course>& courses, const string& selectedCity, const string& selectedTheme, const vector<Course>& previousCourses) {
    int choice;
    cout << "재추천을 원하는 코스 번호를 입력하세요 (1 ~ " << courses.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(courses.size())) {
        cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        return;
    }

    vector<Course> remainingCourses;
    for (const auto& course : previousCourses) {
        bool isDuplicate = false;
        for (const auto& current : courses) {
            if (course.place == current.place) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            remainingCourses.push_back(course);
        }
    }

    if (remainingCourses.empty()) {
        cout << "더 이상 추천할 코스가 없습니다." << endl;
        return;
    }

    int randomIndex = rand() % remainingCourses.size();
    courses[choice - 1] = remainingCourses[randomIndex];
    cout << "선택하신 코스가 재추천되었습니다!" << endl;
}
