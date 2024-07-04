#include "wordnet/Wordnet.hpp"

#include <charconv>
#include <fstream>
#include <numeric>
#include <queue>
#include <vector>

void Digraph::resize(std::size_t new_size) {
    graph.reserve(new_size);
    vert_id.reserve(new_size);
    map.reserve(new_size);
}

void Digraph::add_edge(unsigned int v, unsigned int w) {
    auto [it, inserted] = map.emplace(v, vert_id.size());
    if (inserted) {
        vert_id.emplace_back(v);
        graph.emplace_back();
    }
    auto [it1, inserted1] = map.emplace(w, vert_id.size());
    if (inserted1) {
        vert_id.emplace_back(w);
        graph.emplace_back();
    }
    graph[it->second].emplace_back(it1->second);
}

std::vector<unsigned> Digraph::get_nghbrs(unsigned int v) const {
    auto res_v                   = map.find(v);
    std::vector<unsigned> nghbrs = {};
    if (res_v != map.end()) {
        nghbrs = graph[res_v->second];
        for (auto& i : nghbrs) {
            i = vert_id[i];
        }
    }
    return nghbrs;
}

std::size_t Digraph::size() const {
    return graph.size();
}
std::ostream& operator<<(std::ostream& out, const Digraph& graph) {
    out << "vertex: its neighbours\n";
    for (std::size_t i = 0; i < graph.size(); ++i) {
        out << graph.vert_id[i] << ": ";
        for (std::size_t j = 0; j < graph.graph[i].size(); ++j) {
            out << graph.vert_id[graph.graph[i][j]] << " ";
        }
        out << '\n';
    }

    return out;
}

WordNet::Nouns::Nouns(const std::unordered_map<std::string_view, std::vector<unsigned>>& mapa_) : mapa_(mapa_){};

WordNet::Nouns::iterator& WordNet::Nouns::iterator::operator++() {
    ++it;
    return *this;
}

WordNet::Nouns::iterator WordNet::Nouns::iterator::operator++(int) {
    auto tmp = *this;
    it++;
    return tmp;
}

bool WordNet::Nouns::iterator::operator==(const iterator& rhs) const {
    return it == rhs.it;
}

bool WordNet::Nouns::iterator::operator!=(const iterator& rhs) const {
    return !(*this == rhs);
}

WordNet::WordNet(std::istream& synsets, std::istream& hypernyms) {
    std::string line;
    while (std::getline(synsets, line)) {
        if (line.empty())
            continue;
        original_file.emplace_back(std::move(line));
    }

    for (const std::string& line_ : original_file) {
        std::string_view id_string(&line_[0], line_.find(','));
        unsigned id;
        std::from_chars(id_string.begin(), id_string.end(), id);
        std::size_t gloss_start = line_.find(',', id_string.size() + 1) + 1;
        std::size_t start_pos   = id_string.size() + 1;
        std::size_t end_pos;
        while ((end_pos = line_.find(' ', start_pos)) < gloss_start) {
            word_id[{&line_[start_pos], end_pos - start_pos}].emplace_back(id);
            start_pos = end_pos + 1;
        }
        word_id[{&line_[start_pos], gloss_start - 1 - start_pos}].emplace_back(id);
        glosses[id] = {&line_[gloss_start], line_.size() - gloss_start};
    }

    graph.resize(original_file.size());
    while (std::getline(hypernyms, line)) {
        if (line.empty()) {
            continue;
        }
        std::string_view from_string(&line[0], line.find(','));
        if (from_string.size() < line.size()) {
            unsigned from;
            std::from_chars(from_string.begin(), from_string.end(), from);
            std::size_t start_pos = from_string.size() + 1;
            std::size_t end_pos;
            while ((end_pos = line.find(',', start_pos)) < line.size()) {
                unsigned j;
                std::from_chars(std::string_view(&line[start_pos], end_pos - start_pos).begin(),
                                std::string_view(&line[start_pos], end_pos - start_pos).end(), j);
                graph.add_edge(from, j);
                start_pos = end_pos + 1;
            }
            unsigned j;
            std::from_chars(std::string_view(&line[start_pos], line.size() - start_pos).begin(),
                            std::string_view(&line[start_pos], line.size() - start_pos).end(), j);
            graph.add_edge(from, j);
        }
    }
}

WordNet::Nouns WordNet::nouns() const {
    return Nouns(word_id);
}
bool WordNet::is_noun(const std::string& word) const {
    return (word_id.find(word) != word_id.end());
}
std::string WordNet::sca(const std::string& noun1, const std::string& noun2) const {
    return std::string(
        glosses.at(ShortestCommonAncestor(graph).ancestor_length(word_id.at(noun1), word_id.at(noun2)).first));
}
unsigned WordNet::distance(const std::string& noun1, const std::string& noun2) const {
    return ShortestCommonAncestor(graph).ancestor_length(word_id.at(noun1), word_id.at(noun2)).second;
}
WordNet::Nouns::iterator WordNet::Nouns::begin() const {
    return {mapa_.begin()};
}
WordNet::Nouns::iterator WordNet::Nouns::end() const {
    return {mapa_.end()};
}
std::string Outcast::outcast(const std::set<std::string>& nouns) {
    if (nouns.size() <= 2) {
        return "";
    }
    std::vector<unsigned> distances(nouns.size());
    std::size_t answer_word_number = 0;
    std::set<std::string>::iterator answer_word_iterator;
    bool flag             = false;
    std::size_t first_pos = 0;
    for (auto i = nouns.begin(); i != nouns.end(); i++, first_pos++) {
        std::size_t second_pos = first_pos + 1;
        for (auto j = std::next(i); j != nouns.end(); j++, second_pos++) {
            unsigned distance = wordnet.distance(*i, *j);
            distances[first_pos] += distance;
            distances[second_pos] += distance;
        }
        if (distances[first_pos] > distances[answer_word_number] || first_pos == 0) {
            answer_word_number   = first_pos;
            answer_word_iterator = i;
            flag                 = false;
        } else if (distances[first_pos] == distances[answer_word_number]) {
            flag = true;
        }
    }
    std::string result;
    if (!flag)
        result = *answer_word_iterator;
    return result;
}
std::pair<unsigned, unsigned> ShortestCommonAncestor::ancestor_length(const std::vector<unsigned int>& subset_a,
                                                                      const std::vector<unsigned int>& subset_b) const {
    std::vector<unsigned> distance(graph.size());
    std::vector<char> visited(graph.size());
    std::queue<unsigned> queue;
    for (const unsigned id : subset_a) {
        unsigned vert = graph.map.at(id);
        visited[vert] = 1;
        queue.emplace(vert);
    }
    for (const unsigned id : subset_b) {
        unsigned vert = graph.map.at(id);
        if (visited[vert] == 1) {
            return {id, 0};
        }
        visited[vert] = 2;
        queue.emplace(vert);
    }
    unsigned min_distance          = std::numeric_limits<unsigned>::max();
    unsigned min_distance_ancestor = 0;
    while (!queue.empty()) {
        const unsigned vert = queue.front();
        queue.pop();
        for (const unsigned to : graph.graph[vert]) {
            if (visited[to] == 0) {
                visited[to]  = visited[vert];
                distance[to] = distance[vert] + 1;
                queue.emplace(to);
            } else if (visited[to] != visited[vert]) {
                unsigned current_distance = distance[to] + distance[vert] + 1;
                if (current_distance < min_distance) {
                    min_distance          = current_distance;
                    min_distance_ancestor = to;
                }
            }
        }
    }
    return {graph.vert_id[min_distance_ancestor], min_distance};
}
unsigned ShortestCommonAncestor::length(unsigned int v, unsigned int w) {
    return ancestor_length({v}, {w}).second;
}
unsigned ShortestCommonAncestor::ancestor(unsigned int v, unsigned int w) {
    return ancestor_length({v}, {w}).first;
}
unsigned ShortestCommonAncestor::length_subset(const std::set<unsigned int>& subset_a,
                                               const std::set<unsigned int>& subset_b) {
    return ancestor_length({subset_a.begin(), subset_a.begin()}, {subset_b.begin(), subset_b.end()}).second;
}
unsigned ShortestCommonAncestor::ancestor_subset(const std::set<unsigned int>& subset_a,
                                                 const std::set<unsigned int>& subset_b) {
    return ancestor_length({subset_a.begin(), subset_a.begin()}, {subset_b.begin(), subset_b.end()}).first;
}
