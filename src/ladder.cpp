#include "ladder.h"
#include <iostream>
#include <fstream> 
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
{
    cout << word1 << word2 << msg; 
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int diff = 0;
    if (str1.size() == str2.size())
    {
        for (int i = 0; i < str1.size(); ++i)
        {
            if (str1[i] != str2[i]) 
            {
                ++diff;
            }
        }
    }
    else if (str1.size() + 1 == str2.size() || str1.size() == str2.size() + 1)
    {
        int i = 0;
        int j = 0;
        while (i < str1.size() && j < str2.size())
        {
            if (str1[i] == str2[j])
            {
                ++i;
                ++j;
            }
            else 
            {
                if (str1.size() > str2.size())
                    ++i;
                else 
                    ++j;
                ++diff;
            }
        }
        if (i != str1.size())
            diff += str1.size() - i;
        else if (j != str2.size())
            diff += str2.size() - j;
    }
    return diff == d;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word)
    {
        error(begin_word, end_word, "Same begin and end word");
        return {};
    }

    std::queue<std::vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    std::set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty())
    {
        std::vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (auto word : word_list)
        {
            if (is_adjacent(last_word, word))
            {
                if (visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    std::vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                    {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream in(file_name);
    string word;
    while (in >> word)
    {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder)
{
    for (auto word : ladder)
    {
        cout << word << ' ';
    }
}

void verify_word_ladder() 
{
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}