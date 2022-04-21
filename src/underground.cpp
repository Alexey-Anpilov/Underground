#include"underground.h"
#include<climits>
/*
skip_list<uint, Station*>::Iterator Underground::findStation(std::string name) const{
    uint st_num;
    for(auto line : lines){
        if(st_num == line.onLine(name)){
            return line.find(st_num);
        }
    }
}
*/

std::pair<uint, std::vector<std::string>> Underground::timeMinPath(std::string first_st_name, std::string second_st_name){
    std::map<int, std::string> nums_to_names;
    std::map<std::string, int> names_to_nums;
    
    int i = 0;
    for(Line& l:lines){
        auto it = l.line.begin();
        for(;;){
            nums_to_names[i] = (*it)->getName();
            names_to_nums[(*it)->getName()] = i;
            if(it == l.line.end()){
                break;
            }
            ++it;
            ++i;
        }

    }
    int n = nums_to_names.size();
    int weight[n][n];
    for(i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j){
                weight[i][j] = 0;
            }else{
                weight[i][j] = INT_MAX;
            }
        }
    }

    i = 0;
    for(Line& l:lines){
        auto it = l.line.begin();
        for(;;){
            std::vector<Change> changes = (*it)->getChanges();
            if(!changes.empty()){
                for(const auto& ch:changes){
                    int j = names_to_nums[ch.change()->getName()]; 
                    weight[i][j] = ch.timeToChange();
                    weight[j][i] = ch.timeToChange();
                }
            }
            auto it1 = it + 1;
            if(!it1.empty() && it != l.line.end()){
                weight[i][i + 1] = (*it)->travelForwardTime();
                weight[i + 1][i] = (*it)->travelForwardTime();
            }
            if( it == l.line.end()){
                break;
            }
            ++it; 
            ++i;     
        }
        auto it1 = it + 1;
        if(!it1.empty()){
            int j = names_to_nums[(*it1)->getName()];
            weight[i][j] = (*it)->travelForwardTime();
            weight[j][i] = (*it)->travelForwardTime();
        }
    }


    int st_num = names_to_nums[first_st_name];
    bool visited[n];
    std::vector<std::pair<int, std::string>> paths(n);
    for(int i = 0; i < n; ++i){
        paths[i].first = weight[st_num][i];
        if(weight[st_num][i] != INT_MAX){
            paths[i].second = std::to_string(st_num);
        }
        visited[i] = false;
    }
    int ind = 0, u = 0;
    for(int i = 0; i < n; ++i){
        int min = INT_MAX;
        for(int j = 0; j < n; ++j){
            if(!visited[j] && paths[j].first < min){
                min = paths[j].first;
                ind = j;
            }
        }
        u = ind;
        visited[u] = true;
        for(int j = 0; j < n; ++j){
            if(!visited[j] && weight[u][j] != INT_MAX && paths[u].first != INT_MAX && (paths[u].first + weight[u][j] < paths[j].first))
            {
                paths[j].first = paths[u].first + weight[u][j];
                paths[j].second = paths[u].second + std::to_string(u);
            }
        }
    }
    auto path = paths[names_to_nums[second_st_name]];
    std::vector<std::string> result;
    result.push_back(first_st_name);
    for(const auto& c:path.second){
        result.push_back(nums_to_names[c]);
    }
    result.push_back(second_st_name);
    return {path.first, result};
}



void Underground::addLine(Line new_line) {
    lines.push_back(new_line);
}

