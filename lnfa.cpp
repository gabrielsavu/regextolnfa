//
// Created by htpzn on 29.03.2019.
//

#include "lnfa.h"

std::istream &operator >> (std::istream &input, LNFA &obj ) {
    input >> (Automata&)obj;
    return input;
}


bool LNFA::checkWord(std::string word) {
    //<position,<state, word>>
    std::queue<std::pair<unsigned, std::pair<std::string, std::string > > > que;
    std::vector<std::string> finals_threads;
    /*
     * <position, state>
     * daca intru in in aceeasi stare cu aceeasi pozitie din cuvant, sigur este un ciclu.
     */
    std::vector<std::pair<unsigned, std::string > > visited;
    que.push(std::make_pair(0 ,std::make_pair(q0, std::string(1, word[0]))));
    while (!que.empty()) {
        if (que.front().first >= word.length()) {
            if (std::find(F.begin(), F.end(), que.front().second.first) != F.end()) {
                return true;
            }
        }
        else {
            if (!Delta.checkBucket(que.front().second.first, que.front().second.second)) {
                for (auto &states : Delta.getBucket(que.front().second.first,
                                                    std::string(1, word[que.front().first]))) {
                    if (que.front().second.second != ".")
                        que.push(std::make_pair(que.front().first + 1,
                                                std::make_pair(states, std::string(1, word[que.front().first + 1]))));
                    else que.push(std::make_pair(que.front().first,
                                                 std::make_pair(states, std::string(1, word[que.front().first]))));
                }

            }
            for (auto &states : lambdaClosure(que.front().second.first)) {
                //verificare cilcu
                auto it = std::find_if(visited.begin(), visited.end(), [&](std::pair<unsigned, std::string> const & ref) {
                    return ref.first == que.front().first && ref.second == states;
                });
                if (it == visited.end()) {
                    que.push(std::make_pair(que.front().first,
                                            std::make_pair(states, std::string(1, word[que.front().first]))));

                    visited.push_back(std::make_pair(que.front().first, states));
                }
            }
        }
        que.pop();
    }
    for (auto& it : finals_threads) {
        if (std::find(F.begin(), F.end(), it) != F.end()) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> LNFA::lambdaClosure (const std::string& state) {
    std::vector<std::string> ret;
    for (auto &states : Delta.getBucket(state, ".")) {
        ret.push_back(states);
    }
    return ret;
}