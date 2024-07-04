#ifndef WORDNET_WORDNET_HPP
#define WORDNET_WORDNET_HPP

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Digraph {
public:
    Digraph() = default;
    void resize(std::size_t new_size);
    void add_edge(unsigned v, unsigned w);
    std::vector<unsigned> get_nghbrs(unsigned v) const;
    std::size_t size() const;
    friend std::ostream& operator<<(std::ostream& out, const Digraph& graph);

private:
    friend class ShortestCommonAncestor;
    std::vector<std::vector<unsigned>> graph;
    std::unordered_map<unsigned, unsigned> map;
    std::vector<unsigned> vert_id;
};

class WordNet {
public:
    WordNet(std::istream& synsets, std::istream& hypernyms);

    /**
     * Simple proxy class used to enumerate nouns.
     *
     * Usage example:
     *
     * WordNet wordnet{...};
     * ...
     * for (const std::string & noun : wordnet.nouns()) {
     *     // ...
     * }
     */
    class Nouns {
        friend class WordNet;
        const std::unordered_map<std::string_view, std::vector<unsigned>>& mapa_;
        Nouns(const std::unordered_map<std::string_view, std::vector<unsigned>>& mapa_);

    public:
        class iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = std::string_view;
            using pointer           = const value_type*;
            using reference         = const value_type&;
            // To do
            iterator() = default;
            reference operator*() const { return (*it).first; }
            pointer operator->() const { return &it->first; }
            iterator& operator++();
            iterator operator++(int);
            bool operator==(const iterator& rhs) const;

            bool operator!=(const iterator& rhs) const;

        private:
            friend class Nouns;
            std::unordered_map<std::string_view, std::vector<unsigned>>::const_iterator it;
            iterator(std::unordered_map<std::string_view, std::vector<unsigned>>::const_iterator it) : it(it){};
        };

        iterator begin() const;
        iterator end() const;
    };

    // lists all nouns stored in WordNet
    Nouns nouns() const;

    // returns 'true' iff 'word' is stored in WordNet
    bool is_noun(const std::string& word) const;

    // returns gloss of "shortest common ancestor" of noun1 and noun2
    std::string sca(const std::string& noun1, const std::string& noun2) const;

    // calculates distance between noun1 and noun2
    unsigned distance(const std::string& noun1, const std::string& noun2) const;

private:
    std::unordered_map<std::string_view, std::vector<unsigned>> word_id;
    std::vector<std::string> original_file;
    std::unordered_map<unsigned, std::string_view> glosses;
    Digraph graph;
};

class Outcast {
public:
    explicit Outcast(WordNet& wordnet) : wordnet(wordnet){};

    // returns outcast word
    std::string outcast(const std::set<std::string>& nouns);

private:
    WordNet& wordnet;
};

class ShortestCommonAncestor {
    friend class WordNet;
    const Digraph& graph;
    explicit ShortestCommonAncestor(const Digraph& dg) : graph(dg){};

    std::pair<unsigned, unsigned> ancestor_length(const std::vector<unsigned>& subset_a,
                                                  const std::vector<unsigned>& subset_b) const;
    // calculates length of shortest common ancestor path from node with id 'v' to
    // node with id 'w'
    unsigned length(unsigned v, unsigned w);

    // returns node id of shortest common ancestor of nodes v and w
    unsigned ancestor(unsigned v, unsigned w);

    // calculates length of shortest common ancestor path from node subset
    // 'subset_a' to node subset 'subset_b'
    unsigned length_subset(const std::set<unsigned>& subset_a, const std::set<unsigned>& subset_b);

    // returns node id of shortest common ancestor of node subset 'subset_a' and
    // node subset 'subset_b'
    unsigned ancestor_subset(const std::set<unsigned>& subset_a, const std::set<unsigned>& subset_b);
};

#endif  // WORDNET_WORDNET_HPP