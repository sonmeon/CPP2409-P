#include <iostream>
using namespace std;

int main() {
    int choice;

    cout << "모임 종류를 선택하세요:\n";
    cout << "1. 가족\n";
    cout << "2. 애인\n";
    cout << "3. 친구\n";
    cout << "선택 (숫자 입력): ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "가족 모임을 위한 추천 코스를 준비 중입니다.\n";
            // 가족 모임에 적합한 코스 추천 기능 추가 가능
            break;
        case 2:
            cout << "애인을 위한 추천 코스를 준비 중입니다.\n";
            // 애인 모임에 적합한 코스 추천 기능 추가 가능
            break;
        case 3:
            cout << "친구들과 함께 할 추천 코스를 준비 중입니다.\n";
            // 친구 모임에 적합한 코스 추천 기능 추가 가능
            break;
        default:
            cout << "올바른 숫자를 입력해 주세요.\n";
            break;
    }

    return 0;
}
