#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

#define umap unordered_map

using namespace std;

void is_closer_to_desired(int desired, int number, int* closest) {
    if (abs(*closest - desired) > abs(number - desired))
        *closest = number;
}

int main() {

    int desired_nr, count_nr;
    vector<int> numbers;
    while(cin >> desired_nr >> count_nr) {
        if (!desired_nr && !count_nr)
            return 0;
        numbers.clear();
        int closest = 0;
        int nr_to_push;
        for (int j = 0; j < count_nr; j++) {
            cin >> nr_to_push;
            numbers.push_back(nr_to_push);
        }
        umap<int, bool> number_obtained;
        // build the count_nr trees
        // queue of ints and list of numbers we havent used so far
        queue<pair<int, vector<int>>> eq;
        for (int i = 0; i < count_nr; i++) {
            vector<int> initial(numbers);

            vector<int>::iterator position = find(initial.begin(), initial.end(), numbers[i]);
            initial.erase(position);

            const pair<int, vector<int>> p(numbers[i], initial);
            
            if (!number_obtained[numbers[i]]) {
                eq.push(p);
                number_obtained[numbers[i]] = true; // adding to map
                is_closer_to_desired(desired_nr, numbers[i], &closest);
            }
            while(!eq.empty()) {
                pair<int, vector<int>> auxPair = eq.front();
                eq.pop();
                if (auxPair.second.empty())
                    continue;
                for (int number : auxPair.second) {
                    vector<int> auxVec(auxPair.second);
                    // delete
                    vector<int>::iterator position = find(auxVec.begin(), auxVec.end(), number);
                    auxVec.erase(position);
                    // push every tipe of operation
                    
                    int result1 = auxPair.first + number;
                    int result2 = auxPair.first - number;
                    int result3 = - auxPair.first + number;
                    int result4 = auxPair.first * number;
                    int result5;
                    if (number)
                        result5 = auxPair.first / number;
                    int result6;
                    if (auxPair.first)
                        result6 = number / auxPair.first;
                    // cout << result1 << " " << result2 << " " << result3 << " " << result4 << " " << result5 << " " << result6 << endl;

                    const pair<int, vector<int>> p1(result1, auxVec);
                    const pair<int, vector<int>> p2(result2, auxVec);
                    const pair<int, vector<int>> p3(result3, auxVec);
                    const pair<int, vector<int>> p4(result4, auxVec);
                    const pair<int, vector<int>> p5;
                    if (number)
                        const pair<int, vector<int>> p5(result5, auxVec);
                    const pair<int, vector<int>> p6;
                    if (auxPair.first)
                        const pair<int, vector<int>> p6(result6, auxVec);

                    if (!number_obtained[result1]) {
                        eq.push(p1);
                        number_obtained[result1] = true;
                        is_closer_to_desired(desired_nr, result1, &closest);
                    }
                    if (!number_obtained[result2]) {
                        eq.push(p2);
                        number_obtained[result2] = true;
                        is_closer_to_desired(desired_nr, result2, &closest);
                    }
                    if (!number_obtained[result3]) {
                        eq.push(p3);
                        number_obtained[result3] = true;
                        is_closer_to_desired(desired_nr, result3, &closest);
                    }
                    if (!number_obtained[result4]) {
                        eq.push(p4);
                        number_obtained[result4] = true;
                        is_closer_to_desired(desired_nr, result4, &closest);
                    }
                    if (!number_obtained[result5] && number) {
                        eq.push(p5);
                        number_obtained[result5] = true;
                        is_closer_to_desired(desired_nr, result5, &closest);
                    }
                    if (!number_obtained[result6] && auxPair.first) {
                        eq.push(p6);
                        number_obtained[result6] = true;
                        is_closer_to_desired(desired_nr, result6, &closest);
                    }
                }
            }
            
        }
        cout << closest << endl;
    }

    return 0;
}